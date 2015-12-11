<?php
/**
 * The PGRR portal is a resource for sharing genomic data in a resource community.
 * Copyright (C) 2015  University of Pittsburgh
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

include_once 'common.php';

function _get_search_repository_filters(){

	$selected_filters = array();
	if(isset($_GET["results"])){
		$filters = json_decode( $_GET["results"], true);		
		foreach ($filters as $filter){			
			$selected_filters[$filter["key"]] = $filter["value"];
		}
	}
	
	$output = '<div id="search_repository_filters">';
	
	//store the filters into the session
	if(isset($_SESSION["getFilters_json"]) && strpos($_SESSION["getFilters_json"],'results') !== false){
		$getFilters_json = $_SESSION["getFilters_json"];
	}else{
		$getFilters_json = call_rest_get_web_service("getFilters");
		$_SESSION["getFilters_json"] = $getFilters_json;
	}
	
	if(isset($getFilters_json) && $getFilters_json != false){
		$array = json_decode($getFilters_json, true);
		$results = $array["results"];
		foreach($results as $item){
			$key = $item["key"];
			$id = strtolower($key);
			$id = str_replace(" ", "_", $id);
			$id = str_replace(":", "", $id);
				
			$output .= "<div class=\"sb_wrapper\" id=\"" . $id . "_filter\" key=\"" . $key . "\">";
			$output .= "<strong>By " . $key . "</strong><br / >";
			$output .= "<div class=\"sb_input\"/>";
			if(isset($selected_filters[$key])){			
				$output .= implode("<br /> ", $selected_filters[$key]);
			}											
			$output .= "</div>";
			$output .= "<ul class=\"sb_dropdown\">";
			
			$check = "";
			$all = false;
			if(isset($selected_filters[$key]) && in_array("All", $selected_filters[$key])){
				$check = "checked";
				$all = true;
			}					
			$output .= "<li><input type=\"checkbox\" value=\"All\" $check/>(Toggle all)</li>";
			
			
			foreach ($item["value"] as $value){
				$check = "";
				if(isset($selected_filters[$key]) && (in_array($value, $selected_filters[$key]) || $all)){
					$check = "checked";
				}
				$output .= "<li><input type=\"checkbox\" value=\"$value\" $check />$value</li>";
			}
			
			$output .= "</ul>";
			$output .= "</div>";
		}
	}
	
	//Snapshot By Date filter
	$date = "";
	if(isset($selected_filters["Snapshot By Date"])){
		$date = implode(" ", $selected_filters["Snapshot By Date"]);
	}
	$output .= "<div class=\"sb_wrapper\" id=\"snapshot_by_date_filter\" key=\"Snapshot By Date\">";
	$output .= "<strong>Snapshot By Date</strong><br / >";
	$output .= "<input id=\"date_picker\" disabled value=\"" . $date . "\"/>";
	$output .= "<img id=\"clear-date\" src=\"/sites/all/modules/custom/ipm/images/remove_icon_grey.png\" alt=\"clear date\"/>";
	$output .= "</div>";
	
	$output .= "<input type=\"button\" value=\"Apply\" id=\"search_repository_filters_submit\"> <input type=\"button\" value=\"Reset\" id=\"search_repository_filters_reset\" />";
	$output .= "</div>";
	return $output;
}

function search_repository_page($arg = null){
	$output = "";
	drupal_add_library("system", "ui.datepicker");
	drupal_add_js(drupal_get_path('module', 'ipm') . '/js/search-repository.js');

	$num_per_page = 25;
	
	if(isset($_GET["page"]))$page = $_GET["page"];
	else $page = 1;
	
	if(isset($_GET["results"])) $results =  $_GET["results"];
	else $results = '';
		
	//Generate result total and selected filters
	$query = "";
	$selected_filters = "";
	if($results!= ''){		
		$selected_filters .= "<div>Applied filter(s):</div>";
		$filters = json_decode($results, true);
		foreach ($filters as $filter){
			$selected_filters .= "<span>" .  $filter["key"] . ": </span>";
			$selected_filters .= implode(", ", $filter["value"]) . "<br />";
		}
		$results = str_replace(" ", "%20", $results);
		$query .= "?jsonReq={\"results\":" . $results . "}";
	}
		
	$total = 0; 	
    $total = call_rest_get_web_service("getSearchRepositoryResultTotal" . $query);
    
    if($total != 0){
    	$output .= "<div id=\"search_repository_download\">";

    	$disabled = "";
    	if($total > 50000){
    		$disabled = "disabled";
    	}

    	$output .= "<input id=\"search_repository_download_button\" type=\"button\" value=\"Download File Information\" $disabled />";
    	$output .= "<img id=\"search_repository_download_settings\" src=\"/sites/all/modules/custom/ipm/images/settings-icon.png\" alt=\"settings for download\" />";
    	$output .= "<div id=\"search_repository_download_settings_content\">";
    	$output .= "<input type=\"checkbox\" name=\"metadata\" value=\"extended\"> Include extended metadata <br />";
//     	$output .= "<a href=\"#\" >Help me</a>";
    	$output .= "<strong>Select a table format: </strong><br />";
    	$output .= "<input type=\"radio\" name=\"tableFormat\" value=\"csv\" checked>CSV <br />
    				<input type=\"radio\" name=\"tableFormat\" value=\"tsv\">TSV ";   
    	$output .= "</div>";
    	
    	if($total > 50000){
    		$output .= "<div id=\"search_repository_download_notice\">Note: There are too many records selected to download. Please use the filters on the left limit the number of returned records to less than 50000.</div>";
    	}

    	$output .= "</div>";
    }
    
    if(strpos($total,'An access exception occurred') !== false) {
    	drupal_set_message(t($total), 'error');
    }else{
    	$output .= "<div>Found " . $total . " results</div>";
    }
    
	$output .= "<div id=\"selected_filters\">" . $selected_filters ."</div>";
	
	//Generate results in a table
	$stRecord = ($page -1) *  $num_per_page + 1;
	$endRecord = $page * $num_per_page;
	if($endRecord > $total) $endRecord = $total;
				
	$query = "?stRecord=" . $stRecord . "&endRecord=" . $endRecord;
	if($results!= ''){
		$results = str_replace(" ", "%20", $results);
		$query .= "&jsonReq=" . "{\"results\":" . $results . "}";
	}
	
	$table = "<div id=\"search_results\">";
	$json = call_rest_get_web_service("getSearchRepositoryResults" . $query);
	if(isset($json) && $json != false){
		$arr = json_decode($json, true);
	
		if(isset($arr["head"]["vars"]) && isset($arr["results"]["bindings"])){
			$table .= "<table>"; 
			
			//header
			$ws_head = $arr["head"]["vars"];
			$col = "";
			$col .= "<th>No.</th>";
			foreach($ws_head as $head_col){
				$col .= "<th>" . $head_col . "</th>";
			}
			$table .= "<tr>" . $col . "</tr>";

			//content
			$ws_results = $arr["results"]["bindings"];
			foreach($ws_results as $index => $item){
				$row = "";
				foreach($ws_head as $head_col){					
					if(isset($item[$head_col]['value'])){
						$display_value = $item[$head_col]['value'];
						$row .= "<td>" . $display_value . "</td>";
					}else{
						$row .= "<td></td>";
					}
				}
				$index = $num_per_page * ($page -1) + $index + 1;
				$table  .= "<tr><td>" . $index . "</td>" . $row . "</tr>";					
			}
			$table .= "</table>";
		}
	}
	$table .= "</div>";
	$output .= $table;
	
	//Generate pagers
	$pager = "<div id=\"search-repository-page\">";
	$pager .= print_pager($page, $total, $num_per_page, $results);		
	$pager .= "</div>";		
	$output .= $pager;
	
	return $output;
}

//print out four pages before and afte the active page
function print_pager($page, $total, $num_per_page, $results){
	$pager = '';
	
	if($total != 0){
		$start_page = 1;
		$end_page = floor($total / $num_per_page);
		$last_page = $total % $num_per_page;
		if($last_page != 0)$end_page = $end_page + 1;
		
		$start = "";
		$middle = "";
		$end = "";
		
		if($page - 4 <= $start_page){
			$display_start_page = $start_page;
		}else{
			$display_start_page = $page - 4;
			$start = "<span>...</span>";
		}
		
		if($page + 4 >= $end_page){
			$display_end_page = $end_page;
		}else{
			$display_end_page = $page + 4;
			$end = "<span>...</span>";
		}
		
		if($page != 1) $pager .= print_page($start_page, " << ", $results);
		for($i = $display_start_page; $i <= $display_end_page; $i++){
			if($i == $page){
				$middle .= "<span class=\"active\"> " . $i . " </span>";
			}else{
				$middle .= print_page($i, $i, $results);
			}
		}
		$pager .= $start . $middle . $end;
		if($page != $end_page)$pager .= print_page($end_page, " >> ", $results);
	}
		
	return $pager;
}

function print_page($page, $display_page, $results){
	if($results != ""){
		$output = "<a href='/search-repository?page=$page&results=$results'> $display_page </a>";
	}else{
		$output = "<a href='/search-repository?page=$page'> $display_page </a>";
	}	
	return $output;
}

function search_repository_submit_form($node, &$form_state){

	$output = "";
	$selected = $_GET["selected"];
	$available_data = $_SESSION["available_data"];
	$selected_array = explode(",", $selected);
	foreach($selected_array as $selected_item){
		$item = explode(" ", $selected_item);
		if(isset($available_data[$item[0]][$item[1]][$item[2]][$item[3]])){
			$files = $available_data[$item[0]][$item[1]][$item[2]][$item[3]];
			$output .= "<div class=\"search-repository-result\"><strong>Sample Bar Code: </strong>" . $item[0] . " ";
			$output .= "<strong>Data Type: </strong>" . $item[1] . " ";
			$output .= "<strong>Platform: </strong>" . $item[2] . " ";
			$output .= "<strong>Level: </strong>" . $item[3] . "</div> ";
			$output .= implode("<br />", $files);
		}
	}
	
	$form['result'] = array(
		'#markup' => '<div>' . $output . '</div>',
	);
	
	return $form;
}

function search_repository_download_page(){
	global $user;
	
	$extended = isset($_GET["extended"])? $_GET["extended"] : false;
	$tableFormat = isset($_GET["tableFormat"])? $_GET["tableFormat"]: "csv";
	$results = isset($_GET["results"])? $_GET["results"]:"";
	
	$query = "?extended=" . $extended . "&tableFormat=" . $tableFormat ."&email=" . $user->mail;	
	if($results != ''){
		$results = urldecode($results);
		$results = str_replace(" ", "%20", $results);
		$query .= "&jsonReq={\"results\":" . $results . "}";
	}
		
	$fileName = preg_replace('/[\\\\\'?\[\]\/=\+<>;:,\*\|%\* )($&]/', '_', 'file_information_for_user' . $user->uid);
	$fileName = strtolower($fileName);
	$fileName = $fileName."_".date('m-d-Y').".".$tableFormat;
	
	header("Cache-Control: public");
	header('Content-Type: application/'.$tableFormat);
	header("Content-disposition: attachment; filename=".$fileName);
	
	$url = variable_get('ws_server', 'http://localhost:8080') . "/ipm-ws/data-subscription/";
	$url .= "getDownloadFileInformation" . $query; 

	$stream = fopen($url, "rb");	
	$contents = '';
	while (!feof($stream)) {
		$contents .= fread($stream, 1000);
	}
	fclose($stream);
	print($contents);
}



















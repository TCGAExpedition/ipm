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

function _get_search_repository_diseases(){
	$output = '<ul id="search_repository_diseases">';
	$url = variable_get('ws_server', 'http://localhost:8080') . "/ipm-ws/data-subscription/";
	$datatype_json = file_get_contents($url . "getAllDiseasesForSampleSlection");
	if(isset($datatype_json) && $datatype_json != false){
		$array = json_decode($datatype_json, true);
		foreach($array as $item){
			$output .= "<li><a href=\"/search-repository-old/$item\">" . strtoupper($item) . "</a></li>";
		}
	}
	$output .= "</ul>";
	return $output;
}

function search_repository_old_page($arg = null){
	return drupal_get_form('search_repository_old_form', $arg);
}

function search_repository_old_submit_form($node, &$form_state){

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

function search_repository_old_form($node, &$form_state, $arg){	
	drupal_add_js(drupal_get_path('module', 'ipm') . '/js/search-repository-old.js');
// 	drupal_add_js("http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js");
// 	drupal_add_js("http://cdnjs.cloudflare.com/ajax/libs/jquery-throttle-debounce/1.1/jquery.ba-throttle-debounce.min.js");
// 	drupal_add_js(drupal_get_path('module', 'ipm') . '/js/jquery.stickyheader.js');
// 	drupal_add_css(drupal_get_path('module', 'ipm') . '/css/normalize.css');
// 	drupal_add_css(drupal_get_path('module', 'ipm') . '/css/component.css');
	
	$time_start = microtime(true);
	$url = variable_get('ws_server', 'http://localhost:8080') . "/ipm-ws/data-subscription/";
	$header_json = file_get_contents($url . "getDatatypePlatformLevelByDisease?disease=" . $arg);
	
	$time_end = microtime(true);
	$time_1 = $time_end - $time_start;
	
	//get back datatype/platform.level header
	if(isset($header_json) && $header_json != false){
		$array = json_decode($header_json, true);
		$results = $array['results']['bindings'];
		
		$header = array();
		for($i=0;$i<count($results);$i++){		
			$header[$results[$i]['dataType']['value']][$results[$i]['platform']['value']][$results[$i]['level']['value']] = strtolower($results[$i]['isPublic']['value']);
			$header[$results[$i]['dataType']['value']][$results[$i]['platform']['value']]['centerAbbr'] = $results[$i]['centerAbbr']['value'];
		}
	}
	
	//generate the header
	$table = "<div id=\"search-repository-header\" class=\"search-repository\">";
	$header_datatype = "";
	$header_platform = "";
	$header_level = "";
	$header_col = "";
	$cols = array();
	$i = 0;
	foreach($header as $datatype => $platform_array){		
		$count_platform = 0;	
		$centerAbbr = "";
				
		foreach($platform_array as $platform => $level_array){							
			$count_level = 0;
			
			foreach($level_array as $level => $isPublic){
				if($level == "centerAbbr"){
					if(strtolower($isPublic) != "clin")
						$centerAbbr = $isPublic . "<br />";
				}else{
					$cols[$i]["dataType"] = $datatype;
					$cols[$i]["platform"] = $platform;
					$cols[$i]["level"] = $level;
					$i++;
										
					$header_level .= "<div class=\"level ispublic-$isPublic\"><span class=\"$datatype $platform $level\">";
					
					if($isPublic == "no"){
						$level = $level . "*";
					}
					
					$header_level .= $level . "</span></div>";
					$count_level++;
					$count_platform++;
				}
			}
			$header_platform .= "<div class=\"colspan-$count_level \"><div class=\"platform\"><span class=\"$datatype $platform\">" . $centerAbbr . $platform . "</span></div></div>";		
		}

		$header_datatype .= "<div class=\"colspan-$count_platform \"><div class=\"datatype\"><span class=\"$datatype\">" . str_replace('_', ' ', $datatype) . "</span></div></div>";
		$header_platform = "<div>" . $header_platform . "</div>";
		$header_level = "<div>" . $header_level . "</div>";
		
		$header_col .= "<div class=\"header-col\">" . $header_datatype . $header_platform . $header_level . "</div>";	

		$header_datatype = "";
		$header_platform = "";
		$header_level = "";
	}
	
	$filters = "TSS: <br /><select><option value=\"#\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option></select><br /> 
			    Patient: <br /><select><option value=\"#\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option></select><br /> 
			    Sample Type: <br /><select><option value=\"#\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option></select><br /> 
			    Changes Since: <br /><select><option value=\"#\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option></select>";
	
	
	$table .= "<div class=\"header-col empty-col\" >". $filters. "</div>" .$header_col;
	$table .= "</div>";

	$time_start = microtime(true);
	$allPatients = array();
	$length = 50;
	if(isset($_SESSION[$arg])){
		$allPatients = $_SESSION[$arg];
	}else{
		//All the patients Bar code
		$curl = curl_init();
		curl_setopt_array($curl, array(
		CURLOPT_RETURNTRANSFER => 1,
		CURLOPT_URL => $url . "getPatientsByDisease?disease=" . $arg,
		CURLOPT_USERAGENT => 'Codular Sample cURL Request'));
		$data_json = curl_exec($curl);
		curl_close($curl);
		
		if(isset($data_json) && $data_json != false){			
			$array = json_decode($data_json, true);
			$results = $array['results']['bindings'];
		
			$patientsList = array();
			foreach ($results as $item){
				if(isset($item["patientBarcode"]["value"])){
					$patientsList[] = $item["patientBarcode"]["value"];
				}
			}
				
			//Break the patient list into 100 bar code a piece
			$total = count($patientsList);			
			for($i=0; $i < floor($total/ $length); $i++){
				$begin = $i * $length + 1;
				$allPatients[] = json_encode(array_slice($patientsList, $begin, $length));
			}
			if($total % $length != 0){
				$begin = $i * $length + 1;
				$allPatients[] = json_encode(array_slice($patientsList, $begin, $total % $length));
			}									
			$_SESSION[$arg] = $allPatients;		
		}
	}
	$time_end = microtime(true);
	$time_2 = $time_end - $time_start;
 		
	$time_start = microtime(true);
 	//generate data table
 	if(!empty($allPatients)){
 		 			
 		if(isset($_GET["page"]))$page = $_GET["page"];
 		else $page = 0;
 			
 		//get 50 patients at a time
 		$patients = $allPatients[$page];
 		$curl = curl_init();
 		curl_setopt_array($curl, array(
 		CURLOPT_RETURNTRANSFER => 1,
 		CURLOPT_URL => $url . "getCurrMetadataByDiseaseForPatientList?disease=" . $arg ."&patients=" . $patients,
 		CURLOPT_USERAGENT => 'Codular Sample cURL Request'));
 		$metadata_patient_json = curl_exec($curl);
 		curl_close($curl);
 			
 		if(isset($metadata_patient_json) && $metadata_patient_json != false){
 			$row = array();
 			$table .= "<div id=\"search-repository-data-wrapper\"><table id=\"search-repository-data\" class=\"search-repository\">";
 			$data = "";
 			
 			$array = json_decode($metadata_patient_json, true);
 			$results = $array['results']['bindings'];
 			foreach($results as $item){
 				if(isset($item["sampleBarcode"]["value"])){
 					$row[$item["sampleBarcode"]["value"]][$item["dataType"]["value"]][$item["platform"]["value"]][$item["level"]["value"]][] = $item["pgrrFile"]["value"];
 				}else{
 					$row[0][$item["dataType"]["value"]][$item["platform"]["value"]][$item["level"]["value"]][] = $item["pgrrFile"]["value"];
 				}
 			}
 			
 			foreach($row as $sampleBarcode => $header_array){
 				$data .= "<tr><th class=\"sample-barcode\"><span class=\"$sampleBarcode\">" . $sampleBarcode . "</span></th>";
 			
				foreach($cols as $col){
					$class = $sampleBarcode ." " . $col['dataType'] . " " . $col['platform'] . " " . $col['level'];
					if(isset($header_array[$col['dataType']][$col['platform']][$col['level']])){
						$data .= "<td class=\"data-available yes\"><span class=\"$class\"> Y </span></td>";
					}else{
						$data .= "<td class=\"data-available no\"><span class=\"$class\"> N </span></td>";
					}
				}
 				$data .= "</tr>";
 			}
 			$_SESSION["available_data"] = $row;
 			$table .= '<tbody>' . $data . '</tbody>';
 			$table .= "</table></div>";
 		}
 	}
 	$time_end = microtime(true);
 	$time_3 = $time_end - $time_start;
 				
 	$form['time'] = array(
		'#markup' => 'getAllPatientsList:' . $time_2 . ' total:' .count($allPatients). '<br /> getCurrMetadataByDiseaseForPatientList loop:' . $time_3 . ' total:' . $length
 	);

	$form['disease'] = array(
		'#markup' => "<div class=\"submit_button\"><h2>".strtoupper($arg)."</h2><input id=\"submit_selection\" type=\"button\" value=\"Submit\" /> <input id=\"reset_selection\" type=\"button\" value=\"Reset\" /> </div>",
	);
	
	$form['table'] = array(
		'#markup' => $table,
	);
	
	//generate pager
	if(!empty($allPatients)){
		$pager = "<div id=\"search-repository-page\">";
		
		if($page != 0)
			$pager .= "<a href=\"/search-repository/$arg\"> << </a>";
		
		foreach ($allPatients as $key => $value){
			$key_value = $key + 1;
			if($key == $page){
				$pager .= "<span class=\"active\"> " . $key_value . " </span>";
			}else{
				$pager .= "<a href=\"/search-repository/$arg?page=$key\"> " . $key_value . " </a>";
			}			
		}
		
		if($page != count($allPatients) - 1)
			$pager .= "<a href=\"/search-repository/$arg?page=$key\"> >> </a></div>";
		
		$form['pager'] = array(
			'#markup' => $pager,
		);
	}

	return $form;
}

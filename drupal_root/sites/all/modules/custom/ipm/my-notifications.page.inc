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

function my_notifications_form($node, &$form_state){
	drupal_add_js(drupal_get_path('module', 'ipm') . '/js/my-notifications.js');
	
	global $user;
	$form = array();

	$datatype_array = array();
	$datatype_json = call_rest_get_web_service("getAllDatatypes");
	if(isset($datatype_json) && $datatype_json != false){
		$content = json_decode($datatype_json, true);		
		foreach($content['results']['bindings'] as $dt){
			$datatypeAbbr = str_replace(' ', '-', $dt['dType']['value']); // Replaces all spaces with hyphens.
			$datatypeAbbr = preg_replace('/[^A-Za-z0-9\-]/', '', $datatypeAbbr); // Removes special chars.
			$datatype_array[$datatypeAbbr] =  $dt['dType']['value'];
		}
	}
	//store dataytpe abbreviation and full name in the php session
	$_SESSION['datatype'] = $datatype_array;
	
	$disease_array = array();
	$disease_json = call_rest_get_web_service("getAllDiseases");
	if(isset($disease_json) && $disease_json != false){
		$content = json_decode($disease_json, true);			
		foreach($content['results']['bindings'] as $dis){
			$diseaseAbbr = $dis['dAbbr']['value'];
			$disease_array[$diseaseAbbr] = $dis['dName']['value'];
		}
	}
	//store disease abbreviation and full name in the php session
	$_SESSION['disease'] = $disease_array;
	
	//get current subscription
	$subscribe_array = array();
	$subscribe_json = call_rest_get_web_service("getSubscription?email=" . $user->mail);
	if(isset($subscribe_json) && $subscribe_json != false){
		$content = json_decode($subscribe_json, true);	
		foreach($content['results']['bindings'] as $sub){
			$datatypeAbbr = str_replace(' ', '-', $sub['dataType']['value']); // Replaces all spaces with hyphens.
			$datatypeAbbr = preg_replace('/[^A-Za-z0-9\-]/', '', $datatypeAbbr); // Removes special chars.
			$disAbbr = $sub['disAbbr']['value'];
			array_push($subscribe_array,$disAbbr.'|'.$datatypeAbbr);
		}
	}
	$_SESSION['subscribe'] = $subscribe_array;
	
	$table = '';
	$header = '<th></th>';
	$firstRow = true;
	foreach($disease_array as $disease_key => $disease_value){
		$table .= '<tr>';
		$table .= '<td>' . $disease_value . '</td>';		
		foreach($datatype_array as $datatype_key => $datatype_value){		
			if($firstRow){
				$header .= '<th><div class="rotate nowrap">'.$datatype_value.'</div></th>';
			}
			$active = '';
			if (in_array($disease_key."|".$datatype_key, $subscribe_array)) {
				$active = ' active';
			}
			$table .= '<td class="' . $disease_key . ' ' . $datatype_key . $active .'"></td>';
		}
		$firstRow = false;
		$table .= '</tr>';
	}

	$table = '<table id="notification_matrix"><tr>' . $header . '</tr>' . $table . '</table>';
	$form['content'] = array(
		'#markup' => $table,
	); 
		
	return $form;
}

function my_notifications_unsubscribeall_ajax_form($node, &$form_state){
	$form = array();
	global $user;
	call_rest_web_service('{"email" : '.$user->mail.'}', "unsubscribeAll");

	return $form;
}

function my_notifications_subscribe_ajax_form($node, &$form_state){
	global $user;
	$form = array();

	$datatype = $_SESSION['datatype'];
	$disease = $_SESSION['disease'];
	$existing_subscribe = $_SESSION['subscribe'];

	if(isset($_POST["subscribe"])){
		$JSONArray  = json_decode($_POST["subscribe"], true); //returns null if not decoded

		//new subscription list is empty
		if($JSONArray == null){
			//if the existing subscription list is not empty
			if(!empty($existing_subscribe)){
				call_rest_web_service('{"email" : '.$user->mail.'}', "unsubscribeAll");
				$_SESSION['subscribe'] = null;
			}
		}else{
			$subscribe_disAbbr_array = array();
			$subscribe_datatype_array = array();
			$new_subscribe = array();
			foreach($JSONArray as $item){
				$itemarray = explode("|", $item);
				$disAbbr = $itemarray[0];
				$dis = $disease[$disAbbr];
				$dtAbbr = $itemarray[1];
				$dt = $datatype[$dtAbbr];
				//new subscription list
				array_push($new_subscribe, $disAbbr.'|'.$dtAbbr);

				//if the disease and datatype are already in the subsciption
				if (in_array($disAbbr."|".$dtAbbr, $existing_subscribe)) {
					//Do Nothing
				}else{
					$subscribe_disAbbr_array[] = $disAbbr;
					$subscribe_datatype_array[] = $dt;
				}
			}
			//handle new subscription
			$subscribe_disAbbr_json = json_encode($subscribe_disAbbr_array);
			$subscribe_datatype_json = json_encode($subscribe_datatype_array);
			$result = '{"email" : "' . $user->mail . '", "disAbbr" : '.$subscribe_disAbbr_json .', "datatype" : '.$subscribe_datatype_json.'}';
			call_rest_web_service($result, "subscribe");
				
			//handle unsubscription
			if(!empty($existing_subscribe)){
				$unsubscribe_disAbbr_array = array();
				$unsubscribe_datatype_array = array();

				foreach ($existing_subscribe as $key => $value){
					if (!in_array($value, $new_subscribe)) {
						$itemarray = explode("|", $value);
						$disAbbr = $itemarray[0];
						$dis = $disease[$disAbbr];
						$dtAbbr = $itemarray[1];
						$dt = $datatype[$dtAbbr];
						$unsubscribe_disAbbr_array[] = $disAbbr;
						$unsubscribe_datatype_array[] = $dt;
					}
				}
				$unsubscribe_disAbbr_json = json_encode($unsubscribe_disAbbr_array);
				$unsubscribe_datatype_json = json_encode($unsubscribe_datatype_array);
				$result = '{"email" : "' . $user->mail . '", "disAbbr" : '.$unsubscribe_disAbbr_json .', "datatype" : '.$unsubscribe_datatype_json.'}';
				call_rest_web_service($result, "unsubscribe");
			}
			$_SESSION['subscribe'] = $new_subscribe;
		}
	}
	drupal_set_message(t('You have successful subscribed.'));
	return $form;
}

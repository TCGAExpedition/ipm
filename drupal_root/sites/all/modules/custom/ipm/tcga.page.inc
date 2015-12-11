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

function tcga_details_form($node, &$form_state){
	$form = array();
	$node = node_load(10);
	if(isset($_SESSION['agree-tcga-user-code']) && $_SESSION['agree-tcga-user-code']){
		$form['content'] = array(
			'#markup' => $node->body['und'][0]['value'],
		);		
	}else{
		$form['user_code'] = array(
			'#markup' => "<h2>dbGaP USER CODE OF CONDUCT</h2>" . $node->field_user_code_of_conduct["und"][0]["value"],
		);
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Agree'),
			'#submit' => array('tcga_details_form_submit'),
		);
	}
	
	return $form;
}

function tcga_data_form($node, &$form_state){
	global $user;
	$form = array();
	$node = node_load(10);
	
	//field_access_data
	$links = '';
	foreach($node->field_access_data["und"] as $link){	
		if($link['url'] == "go-index"){
			$link['attributes'] = array("target" => "_target");
		}		
		$links .= '<li>' . l($link['title'], $link['url'], $link) . '</li>';
	}
	$form['access_data'] = array(
		'#markup' => '<div><strong>Access Data</strong><br /><ul>' . $links . '</ul></div>',
	);
	
	//field_my_notifications
	$links = '';
	foreach($node->field_my_notifications["und"] as $link){
		$links .= '<li>' . l($link['title'], $link['url'], $link) . '</li>';
	}
	$form['my_notifications'] = array(
		'#markup' => '<div><strong>My Notifications</strong><br /><ul>' . $links . '</ul></div>',
	);
	
	if(in_array('TCGA PI', $user->roles)){
		//field_requests for PI
		$links = '';
		foreach($node->field_request_addition_removal["und"] as $link){
			$links .= '<li>' . l($link['title'], $link['url'], $link) . '</li>';
		}
		$form['requests_pi'] = array(
			'#markup' => '<div><strong>Requests (for PI)</strong><br /><ul>' . $links . '</ul></div>',
		);
	}
	
	if(in_array('TCGA Project Lead', $user->roles)){
		//field_requests for Project Lead
		$links = '';
		foreach($node->field_requests_for_project_lead_["und"] as $link){
			$links .= '<li>' . l($link['title'], $link['url'], $link) . '</li>';
		}
		$form['requests_pj'] = array(
			'#markup' => '<div><strong>Requests (for Project Lead)</strong><br /><ul>' . $links . '</ul></div>',
		);
	}
	
	//field_publications
	$links = '';
	foreach($node->field_submit_publication_report["und"] as $link){
		$links .= '<li>' . l($link['title'], $link['url'], $link) . '</li>';
	}
	$form['publication'] = array(
			'#markup' => '<div><strong>Publications</strong><br /><ul>' . $links . '</ul></div>',
	);
	
	//field_contact
	$links = '';
	foreach($node->field_documentation["und"] as $link){
		$links .= '<li>' . l($link['title'], $link['url'], $link) . '</li>';
	}
	$form['documentation'] = array(
		'#markup' => '<div><strong>Documentation</strong><br /><ul>' . $links . '</ul></div>',
	);

	//field_contact
	$links = '';
	foreach($node->field_contact["und"] as $link){
		$links .= '<li>' . l($link['title'], $link['url'], $link) . '</li>';
	}
	$form['contact'] = array(
		'#markup' => '<div><strong>Contact</strong><br /><ul>' . $links . '</ul></div>',
	);
	return $form;
}

function tcga_details_form_submit($form, &$form_state){
	$_SESSION['agree-tcga-user-code'] = true;
	$form_state['redirect'] = 'tcga-data';
}
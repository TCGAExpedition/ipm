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

function call_rest_web_service($json_data, $which){
	$url = variable_get('ws_server', 'http://localhost:8080') . "/ipm-ws/data-subscription/";
	$url .= $which;

	$ch = curl_init($url);
	curl_setopt_array($ch,
	array(
	CURLOPT_POST => true,
	CURLOPT_POSTFIELDS => $json_data,
	CURLOPT_HEADER => true,
	CURLOPT_HTTPHEADER => array('Content-Type:application/json', 'Content-Length: ' . strlen($json_data)))
	);
	$result = curl_exec($ch);
	curl_close($ch);
}


function call_rest_get_web_service($which){
	$url = variable_get('ws_server', 'http://localhost:8080') . "/ipm-ws/data-subscription/";
	$url .= $which;

	$ch = curl_init();
	$timeout = 500;
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
	$data = curl_exec($ch);
	curl_close($ch);
	return $data;
}

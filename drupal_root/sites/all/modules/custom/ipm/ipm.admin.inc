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

// $Id: dbmi_utils.admin.inc 16574 2011-04-28 22:53:39Z pitt\sss53 $

/**
 * dbmi_utils_settings_form 
 * Settings form for site settings.
 * 
 * @param mixed $form 
 * @param mixed $form_state 
 * @return
 *   $form array
 */
function ipm_settings_form($form, &$form_state) {
  $form = array();

  $form['ws_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Web Services'),
    '#collapsible' => true,
    '#collapsed' => false,
  );

  $form['ws_container']['ws_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Web Services Server for SPARQL Query'),
    '#description' => t('For example: http://localhost:8080. '),
    '#default_value' => variable_get('ws_server', 'http://localhost:8080'),
  	'#size' => 100,  	
  	'#maxlength' => 300,	
  	'#required' => TRUE,
  );

  
  return system_settings_form($form);
}
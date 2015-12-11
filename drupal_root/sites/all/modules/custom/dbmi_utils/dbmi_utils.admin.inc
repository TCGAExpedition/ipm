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
function dbmi_utils_settings_form($form, &$form_state) {
  $form = array();

  $form['debug_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debug'),
    '#collapsible' => true,
    '#collapsed' => false,
  );

  $form['debug_container']['dbmi_debug_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Debug mode?'),
    '#description' => t('With the debug mode turned on, the email notification will be sent to the current user and the email message is logged in Recent Log Messages. '),
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#default_value' => variable_get('dbmi_debug_mode', 0),
  );

  $form['user_control'] = array(
      '#type' => 'fieldset',
      '#title' => t('User edit control'),
      '#collapsible' => true,
      '#collapsed' => false,
  );
  
  $form['user_control']['allow_delete_user_content'] = array(
      '#type' => 'radios',
      '#title' => t('Enable the option to delete user content when deleting users?'),
      '#description' => t("When this is enabled a user's content can be removed when deleting a user."),
      '#options' => array(0 => t('No'), 1 => t('Yes')),
      '#default_value' => variable_get('allow_delete_user_content', 0),
  );
  

  return system_settings_form($form);
}
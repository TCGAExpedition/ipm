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

function _GO_index_page(){
	return "";
}

function _GO_workflow_examples_page(){
	return "";
}

function _GO_video_tutorials_page(){
	return "";
}

function _GO_text_documentation_page(){
	return "";
}

function _GO_contact_us_page(){
	return "";
}


function _GO_form_submit($arg = null){
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
	{
		if (formthrottle_too_many_submissions($_SERVER["REMOTE_ADDR"]))
		{
			echo '{"MusePHPFormResponse": { "success": false,"error": "Too many recent submissions from this IP"}}';
		}
		else
		{
			emailFormSubmission($arg);
		}
	}
}


function emailFormSubmission($arg = null)
{
	if(arg != null){
		switch ($arg) {
			case "form-u1136":
				$to = 'help@genomoncology.com';
				$subject = 'Home Form Submission';
					
				$message = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8"/><title>' . htmlentities($subject,ENT_COMPAT,'UTF-8') . '</title></head>';
				$message .= '<body style="background-color: #ffffff; color: #000000; font-style: normal; font-variant: normal; font-weight: normal; font-size: 12px; line-height: 18px; font-family: helvetica, arial, verdana, sans-serif;">';
				$message .= '<h2 style="background-color: #eeeeee;">New Form Submission</h2><table cellspacing="0" cellpadding="0" width="100%" style="background-color: #ffffff;">';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Name:</b></td><td>' . htmlentities($_REQUEST["custom_U1160"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Email:</b></td><td>' . htmlentities($_REQUEST["Email"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Explain Data type:</b></td><td>' . htmlentities($_REQUEST["custom_U1137"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Institution:</b></td><td>' . htmlentities($_REQUEST["custom_U1173"],ENT_COMPAT,'UTF-8') . '</td></tr>';
					
				$message .= '</table><br/><br/>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Form submitted from website: ' . htmlentities($_SERVER["SERVER_NAME"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Visitor IP address: ' . htmlentities($_SERVER["REMOTE_ADDR"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '</body></html>';
				$message = cleanupMessage($message);
					
				$formEmail = cleanupEmail($_REQUEST['Email']);
				$headers = 'From:  help@genomoncology.com' . "\r\n" . 'Reply-To: ' . $formEmail .  "\r\n" .'X-Mailer: Adobe Muse 7.2.232 with PHP/' . phpversion() . "\r\n" . 'Content-type: text/html; charset=utf-8' . "\r\n";
						
				break;
					
			case "form-u626":					
				$to = 'help@genomoncology.com';
				$subject = 'Contact Us Form Submission';
					
				$message = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8"/><title>' . htmlentities($subject,ENT_COMPAT,'UTF-8') . '</title></head>';
				$message .= '<body style="background-color: #ffffff; color: #000000; font-style: normal; font-variant: normal; font-weight: normal; font-size: 12px; line-height: 18px; font-family: helvetica, arial, verdana, sans-serif;">';
				$message .= '<h2 style="background-color: #eeeeee;">New Form Submission</h2><table cellspacing="0" cellpadding="0" width="100%" style="background-color: #ffffff;">';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Name:</b></td><td>' . htmlentities($_REQUEST["custom_U650"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Email:</b></td><td>' . htmlentities($_REQUEST["Email"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Message:</b></td><td>' . htmlentities($_REQUEST["custom_U627"],ENT_COMPAT,'UTF-8') . '</td></tr>';
					
				$message .= '</table><br/><br/>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Form submitted from website: ' . htmlentities($_SERVER["SERVER_NAME"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Visitor IP address: ' . htmlentities($_SERVER["REMOTE_ADDR"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '</body></html>';
				$message = cleanupMessage($message);
					
				$formEmail = cleanupEmail($_REQUEST['Email']);
				$headers = 'From:  help@genomoncology.com' . "\r\n" . 'Reply-To: ' . $formEmail .  "\r\n" .'X-Mailer: Adobe Muse 7.2.232 with PHP/' . phpversion() . "\r\n" . 'Content-type: text/html; charset=utf-8' . "\r\n";
										
				break;
			case "form-u761":
				$to = 'help@genomoncology.com';
				$subject = 'Home Form Submission';
				
				$message = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8"/><title>' . htmlentities($subject,ENT_COMPAT,'UTF-8') . '</title></head>';
				$message .= '<body style="background-color: #ffffff; color: #000000; font-style: normal; font-variant: normal; font-weight: normal; font-size: 12px; line-height: 18px; font-family: helvetica, arial, verdana, sans-serif;">';
				$message .= '<h2 style="background-color: #eeeeee;">New Form Submission</h2><table cellspacing="0" cellpadding="0" width="100%" style="background-color: #ffffff;">';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Name:</b></td><td>' . htmlentities($_REQUEST["custom_U788"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Email:</b></td><td>' . htmlentities($_REQUEST["Email"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Feature Explanation:</b></td><td>' . htmlentities($_REQUEST["custom_U783"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Institution:</b></td><td>' . htmlentities($_REQUEST["custom_U829"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				
				$message .= '</table><br/><br/>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Form submitted from website: ' . htmlentities($_SERVER["SERVER_NAME"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Visitor IP address: ' . htmlentities($_SERVER["REMOTE_ADDR"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '</body></html>';
				$message = cleanupMessage($message);
				
				$formEmail = cleanupEmail($_REQUEST['Email']);
				$headers = 'From:  help@genomoncology.com' . "\r\n" . 'Reply-To: ' . $formEmail .  "\r\n" .'X-Mailer: Adobe Muse 7.2.232 with PHP/' . phpversion() . "\r\n" . 'Content-type: text/html; charset=utf-8' . "\r\n";
							
				break;

			case "form-u968":
				$to = 'help@genomoncology.com';
				$subject = 'Home Form Submission';
				
				$message = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><meta http-equiv="Content-Type" content="text/html;charset=UTF-8"/><title>' . htmlentities($subject,ENT_COMPAT,'UTF-8') . '</title></head>';
				$message .= '<body style="background-color: #ffffff; color: #000000; font-style: normal; font-variant: normal; font-weight: normal; font-size: 12px; line-height: 18px; font-family: helvetica, arial, verdana, sans-serif;">';
				$message .= '<h2 style="background-color: #eeeeee;">New Form Submission</h2><table cellspacing="0" cellpadding="0" width="100%" style="background-color: #ffffff;">';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Name:</b></td><td>' . htmlentities($_REQUEST["custom_U992"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Email:</b></td><td>' . htmlentities($_REQUEST["Email"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Describe Defect:</b></td><td>' . htmlentities($_REQUEST["custom_U969"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				$message .= '<tr><td valign="top" style="background-color: #ffffff;"><b>Institution:</b></td><td>' . htmlentities($_REQUEST["custom_U1032"],ENT_COMPAT,'UTF-8') . '</td></tr>';
				
				$message .= '</table><br/><br/>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Form submitted from website: ' . htmlentities($_SERVER["SERVER_NAME"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '<div style="background-color: #eeeeee; font-size: 10px; line-height: 11px;">Visitor IP address: ' . htmlentities($_SERVER["REMOTE_ADDR"],ENT_COMPAT,'UTF-8') . '</div>';
				$message .= '</body></html>';
				$message = cleanupMessage($message);
				
				$formEmail = cleanupEmail($_REQUEST['Email']);
				$headers = 'From:  help@genomoncology.com' . "\r\n" . 'Reply-To: ' . $formEmail .  "\r\n" .'X-Mailer: Adobe Muse 7.2.232 with PHP/' . phpversion() . "\r\n" . 'Content-type: text/html; charset=utf-8' . "\r\n";
								
				break;
		}
		
		//using drupal mail and SMTP
		$module = 'ipm';
		$params = array('subject' => $subject, 'message' => $message);
		$language = language_default();
		$result = drupal_mail($module, 'html-email', $to, $language, $params, '', TRUE);
		
		if ($result['result'] == TRUE){
			echo '{"FormResponse": { "success": true}}';
		} else {
			echo '{"MusePHPFormResponse": { "success": false,"error": "Failed to send email"}}';
		}
	}
}

// form-uXXX.php
function cleanupEmail($email)
{
	$email = htmlentities($email,ENT_COMPAT,'UTF-8');
	$email = preg_replace('=((<CR>|<LF>|0x0A/%0A|0x0D/%0D|\\n|\\r)\S).*=i', null, $email);
	return $email;
}

function cleanupMessage($message)
{
	$message = wordwrap($message, 70, "\r\n");
	return $message;
}

// form_throttle.php

/*
 If you see this text in your browser, PHP is not configured correctly on this hosting provider.
Contact your hosting provider regarding PHP configuration for your site.

PHP file generated by Adobe Muse 7.2.232

*/

function formthrottle_check()
{
	if (!function_exists("sqlite_open"))
	{
		return '1';
	}

	$retCode ='5';
	if ($db = @sqlite_open('muse-throttle-db', 0666, $sqliteerror))
	{
		$res = @sqlite_query($db, "SELECT 1 FROM sqlite_master WHERE type='table' AND name='Submission_History';",  $sqliteerror);
		if ($res == null or @sqlite_num_rows($res) == 0 or @sqlite_fetch_single($res) != 1)
		{
			$created = @sqlite_exec($db, "CREATE TABLE Submission_History (IP VARCHAR(39), Submission_Date TIMESTAMP)",  $sqliteerror);
			if($created)
			{
				@sqlite_exec($db, "INSERT INTO Submission_History (IP,Submission_Date) VALUES ('256.256.256.256', DATETIME('now'))",  $sqliteerror);
			}
			else
			{
				$retCode = '2';
			}
		}
		if($retCode == '5')
		{
			$res = @sqlite_query($db, "SELECT COUNT(1) FROM Submission_History;",  $sqliteerror);
			if ($res != null and @sqlite_num_rows($res) > 0 and @sqlite_fetch_single($res) > 0)
				$retCode = '0';
			else
				$retCode = '3';
		}
		@sqlite_close($db);

	}
	else
		$retCode = '4';

	return $retCode;
}

function formthrottle_too_many_submissions($ip)
{
	$tooManySubmissions = false;
	if (function_exists("sqlite_open") and $db = @sqlite_open('muse-throttle-db', 0666, $sqliteerror))
	{
		$ip = @sqlite_escape_string($ip);
		@sqlite_exec($db, "DELETE FROM Submission_History WHERE Submission_Date < DATETIME('now','-2 hours')",  $sqliteerror);
		@sqlite_exec($db, "INSERT INTO Submission_History (IP,Submission_Date) VALUES ('$ip', DATETIME('now'))",  $sqliteerror);
		$res = @sqlite_query($db, "SELECT COUNT(1) FROM Submission_History WHERE IP = '$ip';",  $sqliteerror);
		if (@sqlite_num_rows($res) > 0 and @sqlite_fetch_single($res) > 25)
			$tooManySubmissions = true;
		@sqlite_close($db);

	}
	return $tooManySubmissions;
}
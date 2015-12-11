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
(function($) {
	
	$(function() {
		
		$("#snapshot_by_date_filter #date_picker").datepicker({
			dateFormat: "yy-mm-dd",
			changeMonth: true,
		    changeYear: true,
		    showOn: "button",
		    buttonImage: "/sites/all/modules/custom/ipm/images/calendar-Icon.png",
		    buttonImageOnly: true
		});	

		
		/**
		* the element
		*/
		var $ui = $('.sb_wrapper');
		var chagned = false;
		
		/**
		* on focus and on click display the dropdown, 
		* and change the arrow image
		*/
		$ui.find('.sb_input').bind('click',function(){
			$(this).siblings('.sb_dropdown')
					.show();
		});
		
		/**
		* on mouse leave hide the dropdown, 
		* and change the arrow image
		*/
		$ui.bind('mouseleave',function(){
			$dropdown = $(this);
			$dropdown.children('.sb_dropdown')
			   .hide();
			
			if(changed){
				var value = "";
				$dropdown.children('.sb_dropdown').find(':checked').each(function(){
					if($(this).val() == "All"){
						value = $(this).val();
						return false;
					} 					
					value += $(this).val() + "<br />";
				});
				$dropdown.children('.sb_input').html(value);	
				changed = false;
			}					
		});
		
		/**
		* selecting one of the checkboxes in the dropdown
		*/
		
		$ui.find('.sb_dropdown').find('input').bind('click',function(){
			var value = $(this).attr("value");
			if(value == "All"){
				//selecting all checkboxes
				$(this).parent().siblings().find(':checkbox').attr('checked',this.checked);		
			}else{
				if(this.checked){
					//if all the options are selected
					var num1 = $(this).parent().siblings().length - 1;
					var num2 =  $(this).parent().siblings().find(':checked').length;
					if(num1 == num2){
						$(this).parent().siblings().find('input[value="All"]').attr('checked', true);
					}
				}else{
					//deselect "All"
					$(this).parent().siblings().find('input[value="All"]').attr('checked', false);
				}						
			}
			changed = true;			
		});
		
		$("#search_repository_filters .sb_wrapper #clear-date").click(function(){
			$("#search_repository_filters .sb_wrapper #date_picker").val("");			
		});
		
		$("input#search_repository_filters_submit").click(function(){
			var results = [];
			
			$(".sb_wrapper").each(function(){
				var $wrapper = $(this);			
				if($wrapper.find(':checked').length > 0){
					var key = $wrapper.attr("key");
					var values = [];	
					
					//if all the options are selected
					var num1 = $wrapper.find(':checkbox').length;
					var num2 = $wrapper.find(':checked').length;
					if(num1 == num2){
						values.push("All");	
					}else{
						$wrapper.find(':checked').each(function(){																
							values.push($(this).attr("value"));					
						});	
					}
					
					var filter = {};
					filter.key = key;
					filter.value = values;
					
					results.push(filter);
				}				
			});
			
			if($("#snapshot_by_date_filter #date_picker").val() != ""){
				var filter = {};
				filter.key = $("#snapshot_by_date_filter").attr("key");
				var values = [];
				values.push($("#snapshot_by_date_filter #date_picker").val());	
				filter.value = values;
				results.push(filter);
			}
			
			if(results.length > 0){
				window.location = "/search-repository?page=1&results=" + JSON.stringify(results);
					
//				$.ajax({
//					type : "POST",
//					url : '/search-repository-ajax',
//					data : {"results" : JSON.stringify(results)},
//					success : function(result){
//					   $("#busy_icon").css("display","none");				  
//					   $("#selected_filters").html('<div class="messages status">Post successfully. </div>' + result);
//					},
//					error:function(){
//					   $("#busy_icon").css("display","none");
//			           $("#selected_filters").html('<div class="messages error">Post failed. </div>');
//			        }
//				});
			}
		});
		
		$("#search_repository_filters_reset").click(function(){			
//			$('#search_repository_filters .sb_input').html("");
//			$("#search_repository_filters input[type='checkbox']").attr("checked", false);	
//			$("#snapshot_by_date_filter #date_picker").val("");
			window.location = "/search-repository";
		});
		
		// download settings	
		$("#search_repository_download_settings").mouseover(function(){
			var content = $("#search_repository_download_settings_content");
			content.show();
			setTimeout(function(){
				if(content.is(":hover")){
					
				}else{
					content.hide();
				}
			}, 1000);
		});
		
		$("#search_repository_download_settings_content")
		.mouseover(function(){
			$(this).show();
		}).mouseout(function(){
			$(this).hide();		
		});	
		
		$("#search_repository_download_button").click(function(){			
			var extended = $("#search_repository_download_settings_content input[value='extended']").is(":checked");
			var tableFormat = $("#search_repository_download_settings_content input[name='tableFormat']:checked").val();			
			var parameters = "?extended=" + extended + "&tableFormat=" + tableFormat;
			
			var results = GetURLParameter('results');
			//filters are selected
			if(results != "" && results != null){				
				parameters += "&results=" + results;
			}
			window.location = "/search-repository-download" + parameters ;
		});
			

	});
	
	function GetURLParameter(sParam){
	    var sPageURL = window.location.search.substring(1);
	    var sURLVariables = sPageURL.split('&');
	    for (var i = 0; i < sURLVariables.length; i++){
	        var sParameterName = sURLVariables[i].split('=');
	        if (sParameterName[0] == sParam){
	            return sParameterName[1];
	        }
	    }
	}
	
})(jQuery);
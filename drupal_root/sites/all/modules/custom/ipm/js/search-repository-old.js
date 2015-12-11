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
			
		$("#reset_selection").bind("click",function(){
			$("table#search-repository-data td.data-available.selected").removeClass("selected");
		});	
			
		$("#submit_selection").bind("click",function(){
			var selection_array = new Array();
			var classes = "";
			$("table#search-repository-data td.data-available.selected").each(function(i, val){
				classes = $(this).find("span").attr("class");
				selection_array[i] = classes;
			})
			
			if(selection_array.length != 0 ){
				window.location.href = "/search-repository-old/search-repository-submit-old?selected=" + selection_array.join();
			}else{
				 $("#messages div.section").html('<div class="messages error">Please select at least one data file. </div>');
			}			
		});
		
		//cell selection
		$("table#search-repository-data td.data-available.yes").bind("click",function(){		
			single_selection($(this));
		});
		
		//datatype selection
		$(".datatype").click(function(){
			var selected = selected_or_not($(this));
			group_selection(selected, $(this), $("table#search-repository-data td.data-available.yes"));
			group_selection(selected, $(this), $(".platform"));
			group_selection(selected, $(this), $(".level"));
			
		});
		
		//platform selection
		$(".platform").click(function(){
			var selected = selected_or_not($(this));
			group_selection(selected, $(this), $("table#search-repository-data td.data-available.yes"));
			group_selection(selected, $(this), $(".level"));
			upward_group_selection(selected, $(this), $(".datatype"));
		});
		
		//level selection
		$(".level").click(function(){
			var selected = selected_or_not($(this));
			group_selection(selected, $(this), $("table#search-repository-data td.data-available.yes"));
			upward_group_selection(selected, $(this), $(".platform"));
			upward_group_selection(selected, $(this), $(".datatype"));
		});
		
		//barcode selection
		$(".sample-barcode").click(function(){
			var selected = selected_or_not($(this));
			group_selection(selected, $(this), $("table#search-repository-data td.data-available.yes"));
		});
				
	});
	
	function single_selection(ele){
		if(ele.hasClass("selected")){
			ele.removeClass("selected");
		}else{
			ele.addClass("selected");
		}
	}
	
	function selected_or_not(ele){		
		var selected = true;
		if(ele.hasClass("selected")){
			ele.removeClass("selected");
			selected = false;
		}else{
			ele.addClass("selected");
			selected = true;
		}
		return selected;
	}
	
	function group_selection(selected, ele, target){		
		var classes = ele.find("span").attr("class");
		target.each(function(){
			if($(this).find("span").hasClass(classes)){
				if(selected == true){
					$(this).addClass("selected");					
				}else{
					$(this).removeClass("selected");
				}
			}
		})	
	}
	
	function upward_group_selection(selected, ele, target){	
		var string = ele.find("span").attr("class");
		var array = string.split(" ");
		
		target.each(function(){
			var obj = $(this);			
			$.each(array, function(index, value){
				if(obj.find("span").hasClass(value)){
					if(selected == true){
						obj.addClass("selected");					
					}else{
						obj.removeClass("selected");
					}
				}
			})			
		})	
	}
	
})(jQuery);
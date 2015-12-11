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
	
	function addOrRemoveActiveClass(ele){
		var i = 0;
		ele.each(function(){
			//check if all the cells in that column/row are active 
			if(!$(this).hasClass('active'))i++;
		});
		if(i == 0){
			//if all the cells are active in a column/row, deactive them.
			ele.removeClass('active');
		}else{
			ele.addClass('active');
		}			
	}
	
	$(function() {
		
		$('#notification_matrix tr td').click(function(){			
			if($(this).is(':first-child')){				
				var row = $(this).siblings('td');
				addOrRemoveActiveClass(row);				
			}else{				
				if($(this).hasClass('active')){
					$(this).removeClass('active');
				}else{
					$(this).addClass('active');
				}				
			}		
		});	
		
		$('#notification_matrix tr th').click(function(){	
			var which = $(this).index() + 1;
			var col = $("#notification_matrix tr td:nth-child(" + which + ")");
			addOrRemoveActiveClass(col);			
		});	
		
		//reset
		$('#reset_notification_button').click(function(){
			location.reload();
		});
		
		//unsubscribe all
		$("#unsubscribe_all_notification_button").click(function(){
			var r = confirm("Are you sure you want to delete all your subscriptions? ");
			if(r == true){
				$('#notification_matrix td.active').removeClass('active');
				$("#busy_icon").height($(document.body).height());
				$("#busy_icon").css("display","block");
				$.ajax({
					type : "POST",
					url : '/my-notifications-unsubscribeall-ajax',										
					success : function(){
					   $("#busy_icon").css("display","none");				  
					   $("#messages div.section").html('<div class="messages status">You have successful unsubscribed.</div>');
					},
					error:function(){
					   $("#busy_icon").css("display","none");
			           $("#messages div.section").html('<div class="messages error">Subscription failed. </div>');
			        }
				});
			}			
		})
		
		//subscribe button
		$('#submit_notification_button').click(function(){
			$("#busy_icon").css("display","block");
			var data = '';
			var classArray = new Array();
			$('#notification_matrix td.active').each(function(i){
				var name = $(this).attr('class');
				name = name.replace(' active','');
				name = name.replace(' ','|');
				classArray[i] = name; 
			})
			data = JSON.stringify(classArray);	
			
			$.ajax({
				type : "POST",
				url : '/my-notifications-subscribe-ajax',				
				data : {"subscribe" : data},				
				success : function(){
				   $("#busy_icon").css("display","none");				  
				   $("#messages div.section").html('<div class="messages status"><h2 class="element-invisible">Status message</h2>You have successful saved your subscription.</div>');							
				},
				error:function(){
				   $("#busy_icon").css("display","none");
		           $("#messages div.section").html('<div class="messages error"><h2 class="element-invisible">Error message</h2>Subscription failed. </div>');
		        }
			});
		});
	});
})(jQuery);
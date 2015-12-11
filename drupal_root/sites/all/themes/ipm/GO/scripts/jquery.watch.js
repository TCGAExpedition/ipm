/*
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
(function(b){b.extend(b.fn,{watch:function(c,a,d){var f=document.createElement("div"),h=function(a,d){var a="on"+a,b=a in d;b||(d.setAttribute(a,"return;"),b=typeof d[a]=="function");"onpropertychange"==a&&jQuery.browser.msie&&jQuery.browser.version>=9&&(b=!1);return b};typeof a=="function"&&(d=a,a={});typeof d!="function"&&(d=function(){});a=b.extend({},{throttle:10},a);return this.each(function(){var i=b(this),g=function(){for(var a=i.data(),d=!1,b,f=0;f<a.props.length;f++)if(b=i.css(a.props[f]),
a.vals[f]!=b){a.vals[f]=b;d=!0;break}d&&a.cb&&a.cb.call(i,a)},j={props:c.split(","),cb:d,vals:[]};b.each(j.props,function(a){j.vals[a]=i.css(j.props[a])});i.data(j);if(h("DOMAttrModified",f))i.on("DOMAttrModified",d);else if(h("propertychange",f))i.on("propertychange",d);else setInterval(g,a.throttle)})}})})(jQuery);

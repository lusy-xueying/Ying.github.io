<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*" %>
<%
	String contextPath = request.getContextPath();
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>菜单主页</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/cdzy.css" type="text/css">
<script type="text/javascript">
	var menuIds = new Set();
	function calculatePrice(thisDom, price, menuId) {
		var menu_count = $('#menu_count').html() * 1;
		var menu_price = $('#menu_price').html() * 1;
		if($(thisDom).prop('checked')) {
			menu_count += 1;
			menu_price += price * 1;
			menuIds.add(menuId);
		} else {
			menu_count = menu_count - 1;
			menu_price -= price * 1;
			menuIds.delete(menuId);
		}
		$('#menu_count').html(menu_count);
		$('#menu_price').html(menu_price);
		$('#menuIds').val(Array.from(menuIds).join());
	}
	
	function form_submit() {
		$('form').submit();
	}
</script>
</head>
<body>
	<div class="box">

	    <div class="sit_nav">
	        <h1 class="animated bounceInLeft fl">食堂菜谱管理系统-菜单主页</h1>
	        <ul class="sit_msg fr">
	            <li>当前用户 : <span><%=session.getAttribute("username") %></span></li>
	            <li>
	                <a href="<%=contextPath %>/login_out">退出</a>
	            </li>
	        </ul>
	    </div>
	
	    <div class="content_box">
	        <ul class="main_box clearfix">
	        	<%
					List<Map<String, String>> menus = (ArrayList)request.getAttribute("menus");
					for(Map<String, String> menu : menus) {
						%>
						<li>
							<a href="<%=contextPath %>/menu_detail?id=<%=menu.get("ID") %>&type=comment" target="_blank">
								<img width="180px" height="230px" src="<%=contextPath + menu.get("PIC")%>" alt="菜单图片">
								<h5><%=menu.get("NAME")%></h5>
							</a>
							<ul class="tags clearfix">
			                    <li><%=(menu.get("TYPE").equals("0") ? "肉菜" : "素菜")%></li>
			                </ul>
			                <ul class="parse clearfix">
			                    <li class="parse_nmb"><%=menu.get("PRICE")%></li>
			                    <li class="parse_check">
			                        <input type="checkbox" onclick="calculatePrice(this, '<%=menu.get("PRICE")%>', '<%=menu.get("ID") %>')">
			                    </li>
			                </ul>
						</li>
						<%
					}
				%>
	        </ul>
	        <div class="get_msg clearfix">
	            <div class="get_box fr">
                		已选择 <span id="menu_count">0</span> 道菜，
	               	 价格共计 <span id="menu_price">0</span> 元
	               	 <button type="button" onclick="form_submit()">加入/查看购物车</button>
	            </div>
	        </div>
	        <form action="<%=contextPath%>/cart" method="post" target="_blank">
	        	<input type="hidden" name="menuIds" id="menuIds">
	        </form>
	    </div>
	
	</div>
</body>
</html>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*" %>
<%
	String contextPath = request.getContextPath();
	// 计算数量和价格
	List<Map<String, String>> menus = (ArrayList)request.getAttribute("menus");
	double price = 0;
	for(Map<String, String> menu : menus) {
		price += Double.parseDouble(menu.get("PRICE"));
	}
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>购物车</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/cdzy.css" type="text/css">
<script type="text/javascript">
	$(function() {
		
	})
</script>
</head>
<body>
	<div class="box">

	    <div class="sit_nav">
	        <h1 class="animated bounceInLeft fl">食堂菜谱管理系统-购物车</h1>
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
					for(Map<String, String> menu : menus) {
						%>
						<li>
							<img width="180px" height="230px" src="<%=contextPath + menu.get("PIC")%>" alt="菜单图片">
							<h5><%=menu.get("NAME")%></h5>
							<ul class="tags clearfix">
			                    <li><%=(menu.get("TYPE").equals("0") ? "肉菜" : "素菜")%></li>
			                </ul>
			                <ul class="parse clearfix">
			                    <li class="parse_nmb"><%=menu.get("PRICE")%></li>
			                    <li class="parse_check">
			                    	<a href="<%=contextPath %>/cart_delete?id=<%=menu.get("ID") %>">删除</a>
			                    	<!-- <button type="button"></button> -->
			                        <%-- <input type="checkbox" onclick="calculatePrice(this, '<%=menu.get("PRICE")%>')"> --%>
			                    </li>
			                </ul>
						</li>
						<%
					}
				%>
	        </ul>
	        <div class="get_msg clearfix">
	            <div class="get_box fr">
                		购物车共<span id="menu_count"><%=menus.size()%></span> 道菜，
	               	 价格共计 <span id="menu_price"><%=price%></span> 元
	               	 <button type="button" onclick="window.close()">关闭</button>
	            </div>
	            
	        </div>
	    </div>
	
	</div>
</body>
</html>
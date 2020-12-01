<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*" %>
<%
	String contextPath = request.getContextPath();
	Map<String, String> menu = (HashMap)request.getAttribute("menu");
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>编辑菜单</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/bjcp.css" type="text/css">
<script>
	function form_submit() {
		var name = $('#name');
		var price = $('#price');
		if(name == '') {
			alert('菜名不能为空！');
			return;
		}
		if(price == '') {
			alert('价格不能为空！');
			return;
		}
		$('form').submit();
	}
</script>
</head>
<body>
	<div class="box">

	    <div class="sit_nav">
	        <h1 class="animated bounceInLeft fl">食堂菜谱管理系统-编辑菜品</h1>
	        <ul class="sit_msg fr">
	            <li>当前用户 : <span><%=session.getAttribute("username") %></span></li>
	            <li>
	                <a href="<%=contextPath %>/login_out">退出</a>
	            </li>
	        </ul>
	    </div>
	
	    <div class="content_box">
	    	<form action="<%=contextPath%>/menu_add" method="post" enctype="multipart/form-data">
	    		<input type="hidden" name="id" value="<%=menu.get("ID")%>">
				<input type="hidden" name="pic" value="<%=menu.get("PIC")%>">
		        <table class="bjcp_table" cellpadding=0; cellspacing=0; border=0;>
		            <tr>
		                <td class="title">菜名</td>
		                <td>
		                    <input type="text" name="name" id="name" value="<%=menu.get("NAME")%>">
		                </td>
		            </tr>
		            <tr>
		                <td class="title">价格</td>
		                <td>
		                    <input type="text" name="price" id="price" value="<%=menu.get("PRICE")%>">
		                </td>
		            </tr>
		            <tr>
		                <td class="title">类别</td>
		                <td>
		                     <input type="radio" name="type" value="0" <% if(menu.get("TYPE").equals("0")) {%>checked<%}%>> 肉菜 &nbsp; 
		                	<input type="radio" name="type" value="1" <% if(menu.get("TYPE").equals("1")) {%>checked<%}%>> 素菜
		                </td>
		            </tr>
		            <tr>
		                <td class="title">原图</td>
		                <td>
		                    <img width="180px" height="200px" src="<%=contextPath + menu.get("PIC")%>" alt="菜单图片">
		                </td>
		            </tr>
		            <tr>
		                <td class="title">新图</td>
		                <td>
		                	 <input id="file" name="file" type="file" style="background: transparent">
		                </td>
		            </tr>
		        </table>
		
		        <div class="bc">
		            <button type="button" onclick="form_submit()">提交</button>
		            <a href="<%=contextPath%>/main">返回列表页面</a>
		        </div>
	        </form>
	
	    </div>
	
	</div>
</body>
</html>
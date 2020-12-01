<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*" %>
<%
	String contextPath = request.getContextPath();
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>后台管理主页</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/htglzy.css" type="text/css">
<style type="text/css">
	.menu_table {width: 100%; border-collapse:collapse;}
	.menu_table th,td {text-align: center; border: solid 1px #ccc}
	.deletebutton {color: red;}
</style>
<script>
	function menu_delete(id) {
		var r = confirm('确认要删除此菜单吗？');
		if(r) {
			window.location.href = '<%=contextPath %>/menu_detail?id=' + id + '&type=delete';
		}
	}
</script>
</head>
<body>
	<div class="box">

	    <div class="sit_nav">
	        <h1 class="animated bounceInLeft fl">食堂菜谱管理系统-后台管理主页</h1>
	        <ul class="sit_msg fr">
	            <li>当前用户 : <span><%=session.getAttribute("username") %></span></li>
	            <li>
	                <a href="<%=contextPath %>/login_out">退出</a>
	            </li>
	        </ul>
	    </div>
	
	    <div class="content_box">
	    	<a href="<%=contextPath%>/menu_add.jsp" style="margin: 20px;"><button type="button">添加菜品</button></a> 
	        <table class="htgl_table" cellpadding=0; cellspacing=0; border=0;>
	            <tr>
	                <td>图片</td>
	                <td>菜名</td>
	                <td>价格</td>
	                <td>类别</td>
	                <td>操作</td>
	            </tr>
	            <%
					List<Map<String, String>> menus = (ArrayList)request.getAttribute("menus");
					for(Map<String, String> menu : menus) {
						%>
						<tr>
							<td><img width="30px" height="30px" src="<%=contextPath + menu.get("PIC")%>" alt="菜单图片"></td>
							<td><%=menu.get("NAME")%></td>
							<td><%=menu.get("PRICE")%></td>
							<td><%=(menu.get("TYPE").equals("0") ? "肉菜" : "素菜")%></td>
							<td>
								<a href="<%=contextPath %>/menu_detail?id=<%=menu.get("ID") %>&type=detail" target="_blank">详情</a> 
								<a href="<%=contextPath %>/menu_detail?id=<%=menu.get("ID") %>&type=edit">编辑</a> 
								<button class="deletebutton" type="button" onclick="menu_delete('<%=menu.get("ID") %>')">删除</button> 
							</td>
						</tr>
						<%
					}
				%>
	        </table>
	
	    </div>
	
	</div>
</body>
</html>
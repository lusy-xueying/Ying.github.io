<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
	String contextPath = request.getContextPath();
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>添加菜品</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/tjcp.css" type="text/css">
<script>
	function form_submit() {
		var name = $('#name').val();
		var price = $('#price').val();
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
	        <h1 class="animated bounceInLeft fl">食堂菜谱管理系统-添加菜品</h1>
	        <ul class="sit_msg fr">
	            <li>当前用户 : <span><%=session.getAttribute("username") %></span></li>
	            <li>
	                <a href="<%=contextPath %>/login_out">退出</a>
	            </li>
	        </ul>
	    </div>
	
	    <div class="content_box">
	    	<form action="<%=contextPath%>/menu_add" method="post" enctype="multipart/form-data">
		        <table class="bjcp_table" cellpadding=0; cellspacing=0; border=0;>
		            <tr>
		                <td class="title">菜名</td>
		                <td>
		                    <input type="text" name="name" id="name" placeholder="请输入菜名">
		                </td>
		            </tr>
		            <tr>
		                <td class="title">价格</td>
		                <td>
		                    <input type="text" name="price" id="price" placeholder="请输入价格">元
		                </td>
		            </tr>
		            <tr>
		                <td class="title">类别</td>
		                <td>
		                    <input type="radio" name="type" value="0" checked> 肉菜 &nbsp; 
		                	<input type="radio" name="type" value="1"> 素菜
		                </td>
		            </tr>
		            <tr>
		                <td class="title">图片</td>
		                <td>
		                	<input id="file" name="file" type="file" style="background: transparent; height: 30px;">
		                </td>
		            </tr>
		        </table>
		
		        <div class="bc">
		            <button type="button" class="btn btn-primary" onclick="form_submit()">添加</button>
		            <a href="<%=contextPath%>/main">返回列表页面</a>
		        </div>
			</form>
	    </div>
	
	</div>
</body>
</html>
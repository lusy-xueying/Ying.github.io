<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
	String contextPath = request.getContextPath();
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>注册页面</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/zc.css" type="text/css">
<script>
	function form_submit() {
		var username = $('#username').val();
		var password = $('#password').val();
		var confirm_password = $('#confirm_password').val();
		if(username == '') {
			alert('用户名不能为空！');
			return;
		}
		if(password == '') {
			alert('密码不能为空！');
			return;
		}
		if(confirm_password == '') {
			alert('确认密码不能为空！');
			return;
		}
		if(password != confirm_password) {
			alert('两次输入的密码不一致，请确认密码！');
			return;
		}
		$('form').submit();
	}
</script>
</head>
<body>
	<!-- 
	<div class="content">
		<h1>食堂菜谱管理系统 - 注册</h1>
		<div class="login blackborder">
			<form action="<%=contextPath%>/regist" method="post">
				用户名 <input type="text" id="username" name="username"> <br><br>
				密&nbsp;&nbsp;&nbsp;码 <input type="password" id="password" name="password"> <br><br>
				确认密码 <input type="password" id="confirm_password"> <br><br>
				<button type="button" onclick="form_submit()">注册</button> <a href="<%=contextPath%>/">返回登录</a>
			</form>
		</div>
	</div>
	 -->
	 
	 <div class="box">

	    <div class="sit_nav">
	        <h1 class="animated bounceInLeft">食堂菜谱管理系统-注册</h1>
	    </div>
	
	    <div class="content_box">
	    	<form action="<%=contextPath%>/regist" method="post">
		        <table class="bjcp_table" cellpadding="0" cellspacing="0" border="0">
		            <tr>
		                <td class="title">账号</td>
		                <td>
		                    <input type="text" id="username" name="username">
		                </td>
		            </tr>
		            <tr>
		                <td class="title">密码</td>
		                <td>
		                    <input type="password" id="password" name="password">
		                </td>
		            </tr>
		            <tr>
		                <td class="title">确认密码</td>
		                <td>
		                    <input type="password" id="confirm_password">
		                </td>
		            </tr>
		        </table>
		
		        <div class="bc">
		            <button type="button" onclick="form_submit()">注 册</button>
		        </div>
	        </form>
	
	    </div>
	
	</div>
	
</body>
</html>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
	String contextPath = request.getContextPath();
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>首页</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/login.css" type="text/css">
<script>
	function form_submit() {
		var username = $('#username').val();
		var password = $('#password').val();
		if(username == '') {
			alert('用户名不能为空！');
			return;
		}
		if(password == '') {
			alert('密码不能为空！');
			return;
		}
		$('form').submit();
	}
</script>
</head>
<body>
    <div class="box">

        <div class="sit_nav">
            <h1 class="animated bounceInLeft">食堂菜谱管理系统</h1>
        </div>

        <div class="login_box animated jackInTheBox">
            <h3>用户登录</h3>
            <form action="<%=contextPath%>/login" method="post">
	            <ul class="ipt_box">
	                <li>
	                    <i class="iconfont icon-xingmingyonghumingnicheng"></i>
	                    <input type="text" class="form-control" name="username" id="username" placeholder="请输入用户名">
	                </li>
	                <li>
	                    <i class="iconfont icon-mima"></i>
	                    <input type="password" class="form-control" name="password" id="password" placeholder="请输入密码">
	                </li>
	                <li class="clearfix">
	                    <div class="check_bix">
	                        <input type="radio" name="type" value="1" checked>
	                        食客登录
	                    </div>
	                    <div class="check_bix" style="text-align: right;">
	                        <input type="radio" name="type" value="0">
	                        管理员登录
	                    </div>
	                </li>
	                <li>
	                    <button type="button" onclick="form_submit()">登 录</button>
	                </li>
	                <li class="get_nmb">
	                    <a href="<%=contextPath%>/regist.jsp">注册</a>
	                </li>
	            </ul>
            </form>
        </div>

    </div>
</body>
</html>
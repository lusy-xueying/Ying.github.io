<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<%
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
	String contextPath = request.getContextPath();
	String flag = request.getAttribute("flag") == null ? "" : request.getAttribute("flag").toString();
%>

<link rel="stylesheet" href="<%=contextPath%>/static/css/style.css" type="text/css">
<link rel="stylesheet" href="<%=contextPath%>/static/public/css/base.css" type="text/css">
<link rel="stylesheet" href="<%=contextPath%>/static/public/css/layout.css" type="text/css">

<!-- 
<link rel="stylesheet" href="<%=contextPath%>/static/css/animate.css" type="text/css">
 -->
<script src="<%=contextPath%>/static/js/jquery.1.12.4.min.js" type="text/javascript"></script>

<script type="text/javascript">
	$(function() {
		var flag = '<%=flag%>';
		if(flag != '') {
			alert(flag);
		}
	});
</script>
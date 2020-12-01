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
<title>菜品详情</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/cpxq.css" type="text/css">
</head>
<body>
	<div class="box">

	    <div class="sit_nav">
	        <h1 class="animated bounceInLeft fl">食堂菜谱管理系统-菜品详情</h1>
	        <ul class="sit_msg fr">
	            <li>当前用户 : <span><%=session.getAttribute("username") %></span></li>
	            <li>
	                <a href="<%=contextPath %>/login_out">退出</a>
	            </li>
	        </ul>
	    </div>
	
	    <div class="content_box">
	        <table class="bjcp_table" cellpadding=0; cellspacing=0; border=0;>
	            <tr>
	                <td class="title">菜名</td>
	                <td><%=menu.get("NAME") %></td>
	            </tr>
	            <tr>
	                <td class="title">价格</td>
	                <td>
	                    <%=menu.get("PRICE") %>元
	                </td>
	            </tr>
	            <tr>
	                <td class="title">类别</td>
	                <td>
	                    <%=(menu.get("TYPE").equals("0") ? "肉菜" : "素菜")%>
	                </td>
	            </tr>
	            <tr>
	                <td class="title">图片</td>
	                <td>
	                    <img width="180px" height="200px" src="<%=contextPath + menu.get("PIC")%>" alt="菜单图片">
	                </td>
	            </tr>
	        </table>
	        
	        <!-- 展示评价 -->
	        <table class="bjcp_table" cellpadding=0; cellspacing=0; border=0;>
	        	<%
	        		List<Map<String, String>> comments = (ArrayList)request.getAttribute("comments");
					for(Map<String, String> comment : comments) {
						%>
						<tr>
							<td class="title"><%=comment.get("USERNAME") %>：</td>
							<td><%=comment.get("COMMENT") %></td>
							<%-- <td style="font-size: smaller;"><%=comment.get("LRSJ") %></td> --%>
						</tr>
						<%
					}
	        	%>
	        </table>
	
	        <div class="bc">
	            <button type="button" onclick="window.close()">关闭</button>
	        </div>
	
	    </div>
	
	</div>
</body>
</html>
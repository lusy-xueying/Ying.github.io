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
<title>菜品评价</title>
<jsp:include page="head.jsp"></jsp:include>
<link rel="stylesheet" href="<%=contextPath%>/static/css/cpxq.css" type="text/css">
<script type="text/javascript">
	function form_submit() {
		var comment = $('#comment').val();
		if(comment == '') {
			alert('评价不能为空！');
			return;
		}
		$('form').submit();
	}
</script>
</head>
<body>
	<div class="box">

	    <div class="sit_nav">
	        <h1 class="animated bounceInLeft fl">食堂菜谱管理系统-菜品评价</h1>
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
	        
	        <form action="<%=contextPath%>/menu_comment_add" method="post">
	        	<input type="hidden" name="menuId" value="<%=menu.get("ID")%>">
	        	<table class="bjcp_table" cellpadding=0; cellspacing=0; border=0;>
	        		<tr>
	        			<td class="title">评价</td>
	        			<td>
		                    <textarea rows="5" id="comment" name="comment" style="width: 950px;"></textarea>
		                </td>
	        		</tr>
	        	</table>
	        </form>
	
	        <div class="bc">
	            <button type="button" onclick="form_submit()">提交</button>
	            <a href="javascript:;" onclick="window.close()">关闭</a>
	        </div>
	        
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
	
	    </div>
	
	</div>
</body>
</html>
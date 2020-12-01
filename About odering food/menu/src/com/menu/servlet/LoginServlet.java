package com.menu.servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.menu.dao.UserDao;
import com.menu.util.MD5Util;

public class LoginServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    public LoginServlet() {
        super();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		UserDao userDao = new UserDao();
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		String type = request.getParameter("type");
		String userId = userDao.queryId(username, MD5Util.md5(password), type);
		if(!userId.equals("")) {
			request.getSession().setAttribute("username", username);
			request.getSession().setAttribute("userId", userId);
			request.setAttribute("flag", "登录成功，欢迎回来。");
//			request.getRequestDispatcher(type.equals("0") ? "/main.jsp" : "menu.jsp").forward(request, response);
			response.sendRedirect(type.equals("0") ? "main" : "menu");
		} else {
			request.setAttribute("flag", "登录失败，请检查用户名和密码。");
			request.getRequestDispatcher("/index.jsp").forward(request, response);
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}

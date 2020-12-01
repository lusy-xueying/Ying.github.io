package com.menu.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.menu.dao.UserDao;
import com.menu.util.MD5Util;

/**
 * Servlet implementation class RegistServlet
 */
public class RegistServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public RegistServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		UserDao userDao = new UserDao();
		String username = request.getParameter("username");
		if(!userDao.checkUsername(username)) {
			request.setAttribute("flag", "用户名被占用，请重新注册。");
			request.getRequestDispatcher("/regist.jsp").forward(request, response);
		}
		String password = request.getParameter("password");
		if(userDao.regist(username, MD5Util.md5(password)) == 1) {
			// 注册成功
			request.setAttribute("flag", "注册成功，请登录。");
		} else {
			// 注册失败
			request.setAttribute("flag", "注册失败，请联系系统管理员。");
		}
		request.getRequestDispatcher("/index.jsp").forward(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

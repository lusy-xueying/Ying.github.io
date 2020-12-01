package com.menu.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.menu.dao.CommentDao;
import com.menu.dao.MenuDao;

/**
 * Servlet implementation class MenuDetail
 */
public class MenuDetailServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public MenuDetailServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		MenuDao menuDao = new MenuDao();
		String id = request.getParameter("id");
		String type = request.getParameter("type");
		if(type.equals("delete")) {
			menuDao.delete(id);
//			response.sendRedirect("main");
			request.getRequestDispatcher("main").forward(request, response);
		}
		request.setAttribute("menu", menuDao.queryById(id));
		// ∂¡»°∆¿º€
		CommentDao commentDao = new CommentDao();
		request.setAttribute("comments", commentDao.queryByMenuId(id));
		if(type.equals("edit")) {
			request.getRequestDispatcher("/menu_edit.jsp").forward(request, response);
		} else if(type.equals("comment")) {
			request.getRequestDispatcher("/menu_comment.jsp").forward(request, response);
		} else {
			request.getRequestDispatcher("/menu_detail.jsp").forward(request, response);
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

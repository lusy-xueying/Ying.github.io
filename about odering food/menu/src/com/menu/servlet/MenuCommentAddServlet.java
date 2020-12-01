package com.menu.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.menu.dao.CommentDao;

/**
 * Servlet implementation class MenuCommentPage
 */
public class MenuCommentAddServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public MenuCommentAddServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String menuId = request.getParameter("menuId");
		String comment = request.getParameter("comment");
		String userId = request.getSession().getAttribute("userId").toString();
		CommentDao commentDao = new CommentDao();
		commentDao.insert(userId, menuId, comment);
		response.sendRedirect("/menu/menu_detail?id=" + menuId + "&type=comment");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}

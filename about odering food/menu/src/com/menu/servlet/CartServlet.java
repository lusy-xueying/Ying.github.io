package com.menu.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.menu.dao.CartDao;

/**
 * Servlet implementation class CartServlet
 */
public class CartServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public CartServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String userId = request.getSession().getAttribute("userId").toString();
		String menuIds = request.getParameter("menuIds") == null ? "" : request.getParameter("menuIds");
		CartDao cartDao = new CartDao();
		for (String menuId : menuIds.split(",")) {
			// 逐个加入购物车
			if (!cartDao.isExist(userId, menuId))
				cartDao.insert(userId, menuId);
		}
		// 查询购物查的菜单
		request.setAttribute("menus", cartDao.queryByUserId(userId));
		request.getRequestDispatcher("/menu_cart.jsp").forward(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

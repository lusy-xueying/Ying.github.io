package com.menu.filter;

import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

/**
 * Servlet Filter implementation class SessionFilter
 */
public class SessionFilter implements Filter {

    /**
     * Default constructor. 
     */
    public SessionFilter() {
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		HttpServletRequest req = (HttpServletRequest) request;
        String url = req.getRequestURI();
        String contextPath = req.getContextPath();
        if(
    		url.equals(contextPath + "/") 
    		|| url.equals(contextPath + "/regist.jsp") 
    		|| url.equals(contextPath + "/login") 
    		|| url.equals(contextPath + "/regist") 
    		|| url.endsWith(".js") 
    		|| url.endsWith(".css") 
    		|| url.endsWith(".ico") 
    		|| url.endsWith(".woff2")
    		|| url.endsWith(".woff")
    		|| url.endsWith(".ttf")
    		|| url.endsWith(".map")
    		|| url.endsWith(".png")
    		|| url.endsWith(".jpg")
        ) {
        	chain.doFilter(request, response);
        } else {
        	HttpSession session = req.getSession();
        	if(session.getAttribute("username") == null) {
        		// 没有session信息，返回首页
        		request.setAttribute("flag", "请先登录！");
        		request.getRequestDispatcher("/").forward(request, response);
        	} else {
        		chain.doFilter(request, response);
        	}
        }
	}

	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException {
		// TODO Auto-generated method stub
	}

}

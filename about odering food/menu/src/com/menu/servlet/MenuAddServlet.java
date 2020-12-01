package com.menu.servlet;

import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileItemFactory;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import com.menu.dao.MenuDao;
import com.menu.util.UUIDUtil;

/**
 * Servlet implementation class MenuAddServlet
 */
public class MenuAddServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public MenuAddServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		FileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        // ��ʼ����������Ϣ
        List items = null;
        try {
            items = upload.parseRequest(request);
        }
        catch (FileUploadException e) {
            e.printStackTrace();
        }

        // ������������Ϣ�����ж�
        Iterator iter = items.iterator();
        String fileName = "";
        while (iter.hasNext()) {
            FileItem item = (FileItem) iter.next();
            // ��ϢΪ��ͨ�ĸ�ʽ
            if (item.isFormField()) {
                String fieldName = item.getFieldName();
                String value = new String(item.getString().getBytes("ISO-8859-1"), "UTF-8");
                request.setAttribute(fieldName, value);
            }
            // ��ϢΪ�ļ���ʽ
            else {
                fileName = item.getName();
                if(!fileName.equals("")) {
                	int index = fileName.lastIndexOf("\\");
                	fileName = fileName.substring(index + 1);
                	request.setAttribute("realFileName", fileName);
                	
                	String suffix = fileName.indexOf(".") > 0 ? fileName.substring(fileName.lastIndexOf(".")) : "";
                	
                	String basePath = request.getRealPath("/images");
                	fileName = UUIDUtil.randomUUID() + suffix;
                	File file = new File(basePath, fileName);
                	try {
                		item.write(file);
                	}
                	catch (Exception e) {
                		e.printStackTrace();
                	}
                }
            }
            request.setAttribute("msg","�ļ��ϴ��ɹ�!");
        }
		MenuDao menuDao = new MenuDao();
		String id = request.getAttribute("id") == null ? "" : request.getAttribute("id").toString();
		String name = request.getAttribute("name").toString();
		String price = request.getAttribute("price").toString();
		String type = request.getAttribute("type").toString();
		String pic = request.getAttribute("pic") == null ? "" : request.getAttribute("pic").toString();
		
		if(id.equals("")) {
			// ���
			if(menuDao.insert(name, price, "/images/" + fileName, type) == 1) {
				request.setAttribute("flag", "��ӳɹ���");
				response.sendRedirect("main");
			} else {
				request.setAttribute("flag", "���ʧ�ܣ���������ӻ���ϵϵͳ����Ա��");
				request.getRequestDispatcher("/menu_add.jsp").forward(request, response);
			}
		} else {
			// �༭
			if(menuDao.update(id, name, price, fileName.equals("") ? pic : "/images/" + fileName, type) == 1) {
				request.setAttribute("flag", "�༭�ɹ���");
				response.sendRedirect("main");
			} else {
				request.setAttribute("flag", "�༭ʧ�ܣ������±༭����ϵϵͳ����Ա��");
				response.sendRedirect("/menu/menu_detail?id=" + id + "&type=edit");
			}
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

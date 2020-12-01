package com.menu.dao;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.menu.util.DBUtil;
import com.menu.util.DateUtil;
import com.menu.util.UUIDUtil;

public class CartDao {

	public int insert(String userId, String menuId) {
		int result = 0;
		
		try {
			result = DBUtil.update("INSERT INTO T_CART(ID, USER_ID, MENU_ID, LRSJ) VALUES (?, ?, ?, ?)", 
					UUIDUtil.randomUUID(), userId, menuId, DateUtil.current());
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return result;
	}
	
	public List<Map<String, String>> queryByUserId(String userId) {
		List<Map<String, String>> result = new ArrayList<Map<String,String>>();
		final StringBuffer sql = new StringBuffer();
		sql.append("SELECT ");
		sql.append("  A.ID, B.NAME, B.TYPE, B.PIC, B.PRICE ");
		sql.append("FROM ");
		sql.append("  T_CART A ");
		sql.append("  JOIN T_MENU B ON A.MENU_ID = B.ID ");
		sql.append("WHERE ");
		sql.append("  A.USER_ID = ? ");
		sql.append("  AND B.ISDELETE = 0");
		try {
			result = DBUtil.selectList(sql.toString(), userId);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public int delete(String id) {
		int result = 0;
		try {
			result = DBUtil.update("DELETE FROM T_CART WHERE ID = ?", id);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public boolean isExist(String userId, String menuId) {
		boolean result = false;
		try {
			result = DBUtil.selectOne("SELECT ID FROM T_CART WHERE USER_ID = ? AND MENU_ID = ?", userId, menuId) != null;
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return result;
	}
	
}

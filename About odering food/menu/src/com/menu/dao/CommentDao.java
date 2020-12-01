package com.menu.dao;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.menu.util.DBUtil;
import com.menu.util.DateUtil;
import com.menu.util.UUIDUtil;

public class CommentDao {
	
	public int insert(String userId, String menuId, String comment) {
		int result = 0;
		try {
			result = DBUtil.update("INSERT INTO T_COMMENT(ID, USER_ID, MENU_ID, COMMENT, LRSJ, ISDELETE) VALUES(?, ?, ?, ?, ?, 0)", 
					UUIDUtil.randomUUID(), userId, menuId, comment, DateUtil.current());
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public List<Map<String, String>> queryByMenuId(String menuId) {
		List<Map<String, String>> result = new ArrayList<Map<String,String>>();
		StringBuffer sql = new StringBuffer();
		sql.append("SELECT ");
		sql.append("  A.COMMENT, B.USERNAME, A.LRSJ ");
		sql.append("FROM ");
		sql.append("  T_COMMENT A ");
		sql.append("  JOIN T_USER B ON A.USER_ID = B.ID ");
		sql.append("WHERE ");
		sql.append("  A.MENU_ID = ? ");
		sql.append("  AND A.ISDELETE = 0 ");
		sql.append("ORDER BY ");
		sql.append("  A.LRSJ DESC ");
		try {
			result = DBUtil.selectList(sql.toString(), menuId);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}

}

package com.menu.dao;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.menu.util.DBUtil;
import com.menu.util.UUIDUtil;

public class MenuDao {
	
	public int insert(String name, String price, String pic, String type) {
		int result = -1;
		String sql = "INSERT INTO T_MENU(ID, NAME, PRICE, PIC, TYPE, ISDELETE) VALUES(?, ?, ?, ?, ?, 0)";
		try {
			result = DBUtil.update(sql, UUIDUtil.randomUUID(), name, price, pic, type);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public int update(String id, String name, String price, String pic, String type) {
		int result = -1;
		String sql = "UPDATE T_MENU SET NAME = ?, PRICE = ?, PIC = ?, TYPE = ? WHERE ID = ?";
		try {
			result = DBUtil.update(sql, name, price, pic, type, id);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public int delete(String id) {
		int result = -1;
		String sql = "UPDATE T_MENU SET ISDELETE = 1 WHERE ID = ?";
		try {
			result = DBUtil.update(sql, id);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public List<Map<String, String>> queryAll() {
		List<Map<String, String>> result = new ArrayList<Map<String,String>>();
		try {
			result = DBUtil.selectList("SELECT ID, NAME, PRICE, PIC, TYPE FROM T_MENU WHERE ISDELETE = 0");
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public Map<String, String> queryById(String id) {
		Map<String, String> result = new HashMap<String,String>();
		try {
			result = DBUtil.selectOne("SELECT ID, NAME, PRICE, PIC, TYPE FROM T_MENU WHERE ISDELETE = 0 AND ID = ?", id);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}

}

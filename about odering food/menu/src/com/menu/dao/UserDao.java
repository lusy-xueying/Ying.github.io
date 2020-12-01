package com.menu.dao;

import java.sql.SQLException;

import com.menu.util.DBUtil;
import com.menu.util.UUIDUtil;

public class UserDao {

	public int regist(String username, String password) {
		int result = 0;
		String sql = "INSERT INTO T_USER(ID, USERNAME, PASSWORD, TYPE, ISDELETE) VALUES(?, ?, ?, 1, 0)";
		try {
			result = DBUtil.update(sql, UUIDUtil.randomUUID(), username, password);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public boolean checkUsername(String username) {
		boolean result = false;
		try {
			result = DBUtil.selectOne("SELECT ID FROM T_USER WHERE USERNAME = ?", username) == null ? true : false;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public boolean login(String username, String password, String type) {
		boolean result = false;
		try {
			result = DBUtil.selectOne("SELECT ID FROM T_USER WHERE USERNAME = ? AND PASSWORD = ? AND TYPE = ? AND ISDELETE = 0", username, password, type) == null ? false : true;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	public String queryId(String username, String password, String type) {
		String result = "";
		try {
			result = DBUtil.selectOne("SELECT ID FROM T_USER WHERE USERNAME = ? AND PASSWORD = ? AND TYPE = ? AND ISDELETE = 0", username, password, type).get("ID");
		} catch (Exception e) {
			e.printStackTrace();
		}
		return result;
	}
	
}

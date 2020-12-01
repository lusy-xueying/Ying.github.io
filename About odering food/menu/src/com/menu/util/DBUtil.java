package com.menu.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DBUtil {
	
	private static String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";
	private static String dbURL = "jdbc:sqlserver://localhost:1433;DatabaseName=menu";
	private static String userName = "sa";
	private static String userPwd = "741852";
	
	public static void main(String[] args) {
		Connection dbConn = null;
		try {
			Class.forName(driverName);
			dbConn = DriverManager.getConnection(dbURL, userName, userPwd);
			System.out.println("success!");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.print("fail!");
		} finally {
			if(dbConn != null) {
				try {
					dbConn.close();
				} catch (SQLException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	public static Connection getConnection() {
		Connection dbConn = null;
		try {
			Class.forName(driverName);
			dbConn = DriverManager.getConnection(dbURL, userName, userPwd);
		} catch (Exception e) {
			e.printStackTrace();
			System.out.print("connection sqlServer fail!");
		}
		
		return dbConn;
	}
	
	public static List<Map<String, String>> selectList(String sql, String...param) throws SQLException {
		List<Map<String, String>> result = new ArrayList<Map<String, String>>();
		
		Connection conn = null;
		ResultSet rs = null;
		PreparedStatement pstm = null;
		try {
			conn = getConnection();
			pstm = conn.prepareStatement(sql);
			
			if(param != null && param.length > 0)
				for(int i = 1; i <= param.length; i++)
					pstm.setString(i, param[i - 1]);
			
			rs = pstm.executeQuery();
			while( rs.next() ) {
				Map< String, String > tempMap = new HashMap< String, String >() ;
				ResultSetMetaData md = rs.getMetaData() ;
				
				for( int i = 1; i <= md.getColumnCount(); i++ ) {
					String cloumnName = md.getColumnLabel( i ) ;
					tempMap.put( cloumnName.toUpperCase(), rs.getString( cloumnName ) == null ? "" : rs.getString( cloumnName )) ;
				}
				
				result.add( tempMap ) ;
			}
		} finally {
			close(conn, pstm, rs);
		}
		
		return result;
	}
	
	public static Map<String, String> selectOne(String sql, String...param) throws SQLException {
		List<Map<String, String>> list = selectList(sql, param);
		
		if(list == null || list.size() == 0)
			return null;
		
		return list.get(0);
	}
	
	public static int update(String sql, String...param) throws SQLException {
		int result = -1;
		Connection conn = null;
		PreparedStatement pstm = null;
		try {
			conn = getConnection();
			pstm = conn.prepareStatement(sql);
			if(param != null && param.length > 0)
				for(int i = 1; i <= param.length; i++)
					pstm.setString(i, param[i - 1]);
			result = pstm.executeUpdate();
		} finally {
			close(conn, pstm);
		}
		
		return result;
	}
	
	public static void close(Connection conn, PreparedStatement pstm, ResultSet rs) {
		if(rs != null) {
			try {
				rs.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		if(pstm != null) {
			try {
				pstm.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		if(conn != null) {
			try {
				conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void close(Connection conn, PreparedStatement pstm) {
		close(conn, pstm, null);
	}

}

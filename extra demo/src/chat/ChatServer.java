package chat;

import java.rmi.RemoteException;

import chatserver.MessageBean;

// ����������ӿ�
public interface ChatServer extends java.rmi.Remote {
	/**
	 * ע���µ������û�
	 */
	public void login(String name, Chatter chatter) throws RemoteException;
	
	/**
	 * �û��˳�
	 */
	public void logout(String name) throws RemoteException;
	
	/**
	 * �û����ô˺�������Ϣ���������û�
	 */
	public void chat(String name, MessageBean message) throws RemoteException;
}

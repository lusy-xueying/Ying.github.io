package chat;

import java.rmi.RemoteException;

import chatserver.MessageBean;

public interface Chatter extends java.rmi.Remote {
	/**
	 * ֪ͨ�û�����
	 */
	public void receiveEnter(String name, Chatter chatter, boolean hasEntered) throws RemoteException;
	
	/**
	 * ֪ͨ�û��뿪������
	 */
	public void receiveExit(String name) throws RemoteException;
	
	/**
	 * �û�����
	 */
	public void receiveChat(String name, MessageBean message) throws RemoteException;
	
	/**
	 * ˽��
	 */
	public void receiveWhisper(String name, MessageBean message) throws RemoteException;
	
	/**
	 * ֪ͨ������ֹͣ
	 */
	public void serverStop() throws RemoteException;
}

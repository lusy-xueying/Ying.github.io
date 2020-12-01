package chatserver;

import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import chat.ChatServer;
import chat.Chatter;

// �������ӿ�
public class ChatServerImpl extends java.rmi.server.UnicastRemoteObject implements ChatServer {
	static ChatServerImpl server = null;
	private final static String BINDNAME = "ChatServer";
	private final static String[] STATEMSG = new String[] { "����������", "������ֹͣ" };
	List chatters = new ArrayList();
	List listeners = new ArrayList();
	
	protected ChatServerImpl() throws java.rmi.RemoteException {
		
	}
	
	public static ChatServerImpl getInstance() {
		try {
			if (server == null) {
				server = new ChatServerImpl();
			}
		} catch (RemoteException e) {
			e.printStackTrace();
			return null;
		}
		return server;
	}
	
	public void start() throws RemoteException, MalformedURLException {
		java.rmi.Naming.rebind(BINDNAME, server);
		MessageBean state=new MessageBean(STATEMSG[0]);
		notifyListener(state);
	}
	
	public void stop() throws RemoteException, NotBoundException, MalformedURLException {
		MessageBean state=new MessageBean(STATEMSG[1]);
		notifyListener(state);
		Iterator itr = chatters.iterator();
		while (itr.hasNext()) {
			UserInfo u = (UserInfo) itr.next();
			u.getChatter().serverStop();
		}
		java.rmi.Naming.unbind(BINDNAME);
	}
	
	public void addListener(ChatServerListener listener) {
		listeners.add(listener);
	}
	
	public void removeListense(ChatServerListener listener) {
		listeners.remove(listener);
	}
	
	void notifyListener(MessageBean msg) {
		Iterator itr = listeners.iterator();
		ChatServerEvent evt = new ChatServerEvent(this, msg);
		while (itr.hasNext()) {
			((ChatServerListener) itr.next()).serverEvent(evt);
		}
	}
	
	public void login(String name, Chatter c) throws java.rmi.RemoteException {
		if (c != null && name != null) {
			UserInfo u = new UserInfo(name, c);
			MessageBean enter=new MessageBean(u.getName() + " ����������");
			notifyListener(enter);
			Iterator itr = chatters.iterator();
			while (itr.hasNext()) {
				UserInfo u2 = (UserInfo) itr.next();
				u2.getChatter().receiveEnter(name, c, false);
				c.receiveEnter(u2.getName(), u2.getChatter(), true);
			}
			chatters.add(u);
		}
	}
	
	public void logout(String name) throws java.rmi.RemoteException {
		if (name == null) {
			System.out.println("null name on logout: cannot remove chatter");
			return;
		}
		UserInfo u_gone = null;
		Iterator itr = null;
		
		synchronized (chatters) {
			for (int i = 0; i < chatters.size(); i++) {
				UserInfo u = (UserInfo) chatters.get(i);
				if (u.getName().equals(name)) {
					MessageBean leave=new MessageBean(name + " �뿪������");
					notifyListener(leave);
					u_gone = u;
					chatters.remove(i);
					itr = chatters.iterator();
					break;
				}
			}
		}
		
		if (u_gone == null || itr == null) {
			System.out.println("no user by name of " + name + " found: not removing chatter");
			return;
		}
		
		while (itr.hasNext()) {
			UserInfo u = (UserInfo) itr.next();
			u.getChatter().receiveExit(name);
		}
	}
	
	public void chat(String name, MessageBean message) throws java.rmi.RemoteException {
		Iterator itr = chatters.iterator();
		
		while (itr.hasNext()) {
			UserInfo u = (UserInfo) itr.next();
			if (!name.equals(u.getName())) {
				u.getChatter().receiveChat(name, message);
			}
		}
		MessageBean chat=new MessageBean(name + ":" + message.getContent());
		notifyListener(chat);
	}
}

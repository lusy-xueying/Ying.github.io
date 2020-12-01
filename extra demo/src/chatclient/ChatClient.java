package chatclient;


import java.awt.Color;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;
import java.rmi.RemoteException;
import java.util.Hashtable;

import javax.imageio.ImageIO;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.KeyStroke;
import javax.swing.SwingWorker;
import javax.swing.text.JTextComponent;
import javax.swing.text.Keymap;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

import chat.ChatServer;
import chat.Chatter;
import chatserver.MessageBean;


public class ChatClient extends JFrame{
	// 存储已有聊天用户，key：用户名，value：对应的Chatter对象
	Hashtable hash = new Hashtable();
	// 自己的用户名
	String my_name = "chatter";
	// 服务器地址
	String serverAddr;
	// 代表客户端到远程对象
	Chatter chatter;
	// 服务器端到远程对象
	ChatServer server;
	JTextPane displayBox;//既有图片又有文字，但是不能复制粘贴
	JTextArea inputBox;
	JTextArea picName;
	JComboBox usersBox;
	JButton sendButton,sendPicButton,uploadPicButton, sendEmojiButton;
	JLabel statusLabel;
	ConnectionAction connectAction = new ConnectionAction();
	File usersFile = null;
	
	// 让用户输入用户名和服务器地址到对话框
	ConnectDlg dlg = new ConnectDlg(this);
	
	public static void main(String[] args) {
		new ChatClient();
	}
	
	public ChatClient() {
		super("聊天客户端");
		layoutComponent();
		setupMenu();
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				exit();
			}
		});
		show();
	}
	
	private void setupMenu() {
		JMenuBar menuBar = new JMenuBar();
		JMenuItem conn = new JMenuItem(connectAction);
		JMenuItem exit = new JMenuItem("退出");
		exit.addActionListener(new AbstractAction() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				exit();
			}
		});
		JMenu file = new JMenu("文件");
		file.add(conn);
		menuBar.add(file);
		setJMenuBar(menuBar);
	}
	
	private void exit() {
		destroy();
		System.exit(0);
	}
	
	// 编辑页面控件元素
	public void layoutComponent() {
		setSize(400, 400);
		JPanel contentPane = new JPanel();
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		contentPane.setLayout(gridbag);
		c.fill = GridBagConstraints.BOTH;
		c.gridwidth = GridBagConstraints.REMAINDER;
		c.gridheight = 6;
		c.weightx = 100;
		c.weighty = 100;
		c.insets.top = 5;
		displayBox = new JTextPane();
		//createTextPane();
		//displayBox.setLineWrap(true);
		displayBox.setEditable(false);
		displayBox.setMargin(new Insets(5, 5, 5, 5));
		JScrollPane scrollPane = new JScrollPane(displayBox);
		//scrollPane.setVerticalScrollBarPolicy(
	    //                 JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
	    //scrollPane.setPreferredSize(new Dimension(250, 155));
	    //scrollPane.setMinimumSize(new Dimension(10, 10));
		contentPane.add(scrollPane, c);
		
		c.gridheight = 1;
		c.weightx = 0;
		c.weighty = 0;
		c.insets.top = 10;

		JLabel msgLabel = new JLabel("消息:");
		contentPane.add(msgLabel, c);
		c.gridheight = 6;
		c.insets.top = 0;
		c.gridwidth = 4;//GridBagConstraints.RELATIVE;
		c.weightx = 100;
		inputBox = new JTextArea();
		addKeymapBindings();
		inputBox.setLineWrap(true);
		inputBox.setWrapStyleWord(true);
		JScrollPane inputScrollPane = new JScrollPane(inputBox);
		inputScrollPane.setPreferredSize(new Dimension(250, 50));
		inputScrollPane.setMinimumSize(new Dimension(250, 50));
		contentPane.add(inputScrollPane, c);

		//发送表情功能
		c.weightx = 0;
		//c.gridwidth = GridBagConstraints.RELATIVE;
		sendEmojiButton = new JButton("发送表情");
		sendEmojiButton.setToolTipText("发送表情");
		sendEmojiButton.setPreferredSize(new Dimension(100, 50));
		sendEmojiButton.setMinimumSize(new Dimension(100, 50));
		sendEmojiButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				//sendEmojiMessage();
			}
		});
		contentPane.add(sendEmojiButton, c);
		
		picName= new JTextArea();
		createJTextArea();
		//picName.setEditable(false);
		//contentPane.add(picName, c);
		c.weightx = 0;
		c.gridwidth = GridBagConstraints.RELATIVE;
		uploadPicButton = new JButton("发送文件");
		uploadPicButton.setToolTipText("发送文件");
		uploadPicButton.setPreferredSize(new Dimension(100, 50));
		uploadPicButton.setMinimumSize(new Dimension(100, 50));
		uploadPicButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				sendPicMessage();
			}
		});
		contentPane.add(uploadPicButton, c);
		//
		
		c.weightx = 0;
		c.gridwidth = GridBagConstraints.REMAINDER;
		sendButton = new JButton("发送");
		sendButton.setToolTipText("发送");
		sendButton.setPreferredSize(new Dimension(100, 50));
		sendButton.setMinimumSize(new Dimension(100, 50));
		sendButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				MessageBean m=new MessageBean(inputBox.getText());
				sendMessage(m);
			}
		});
		contentPane.add(sendButton, c);
		
		c.weightx = 0;
		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridheight = 1;
		JLabel sendtoLabel = new JLabel("发送给:");
		contentPane.add(sendtoLabel, c);
		usersBox = new JComboBox();
		usersBox.setBackground(Color.WHITE);
		usersBox.addItem("所有用户");
		contentPane.add(usersBox, c);
		JPanel statusPane = new JPanel(new GridLayout(1, 1));
		statusLabel = new JLabel("未连接");
		statusPane.add(statusLabel);
		contentPane.add(statusPane, c);
		setContentPane(contentPane);
		try {
			chatter = new ChatterImpl(this);
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
	}
	
	private void createJTextArea() {
		displayBox.setText(null);
		StyledDocument doc = displayBox.getStyledDocument();
		//  Define a keyword attribute
		SimpleAttributeSet keyWord = new SimpleAttributeSet();
		StyleConstants.setForeground(keyWord, Color.RED);
		StyleConstants.setBackground(keyWord, Color.YELLOW);
		StyleConstants.setBold(keyWord, true);
	}

	public void destroy() {
		try {
			disconnect();
		} catch (java.rmi.RemoteException ex) {
			ex.printStackTrace();
		}
	}
	
	public void connect() throws java.rmi.RemoteException, java.net.MalformedURLException, java.rmi.NotBoundException{
		server = (ChatServer) java.rmi.Naming.lookup("//" + serverAddr + "/ChatServer");
		server.login(my_name, chatter);
	}
	
	protected void disconnect() throws java.rmi.RemoteException {
		if (server != null)
			server.logout(my_name);
	}
	
	public void receiveEnter(String name, Chatter chatter, boolean hasEntered) {
		if (name != null && chatter != null) {
			hash.put(name, chatter);
			if (!name.equals(my_name)) {
				// 对新加入聊天的用户，在displayBox给出提示
				if (!hasEntered)
					displayText(name + " 进入聊天室");
				usersBox.addItem(name);
			}
		}
	}
	
	public void receiveExit(String name) {
		if (name != null && chatter != null)
			hash.remove(name);
		for (int i = 0; i < usersBox.getItemCount(); i++) {
			if (name.equals((String) usersBox.getItemAt(i))) {
				usersBox.remove(i);
				break;
			}
		}
		displayText(name + " 离开聊天室");
	}
	
	public void receiveChat(String name, MessageBean message) {
		display(name,message);
	}
	
	public void receiveWhisper(String name, MessageBean message) {
		display(name,message);
	}
	
	// 绑定键盘事件
	protected void addKeymapBindings() {
		Keymap keymap = JTextComponent.addKeymap("MyBindings", inputBox.getKeymap());
		Action action = null;
		KeyStroke key = null;
		// 用户在消息框中按回车发送消息
		action = new AbstractAction() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				MessageBean m=new MessageBean(inputBox.getText());
				sendMessage(m);
			}
		};
		key = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0);
		keymap.addActionForKeyStroke(key, action);
		
		// Ctrl+Enter实现换行
		action = new AbstractAction() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				inputBox.append("\n");
			}
		};
		key = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, Event.CTRL_MASK);
		keymap.addActionForKeyStroke(key, action);
		
		inputBox.setKeymap(keymap);
	}
	//显示文字
	private void display(String name,MessageBean message) {
		int type = message.getChatType();
		switch(type) {
		  case 1:
			displayText(name+":"+message.getContent());
		    break;
		  case 2:
		    displayPic(message.getChatFile().getFile());
		    break;
		  case 3:
		    displayFile(message.getChatFile().getFile());
		    break;
		  default:
		    // code block
		}
	}
	private void displayText(String s) {
		if (!s.endsWith("\n")) {
			StyledDocument doc = displayBox.getStyledDocument();
			try{doc.insertString(doc.getLength(), s + "\n", null);}
			catch(Exception e) { System.out.println(e); }
		} else {
			StyledDocument doc = displayBox.getStyledDocument();
			try{doc.insertString(doc.getLength(), s, null);}
			catch(Exception e) { System.out.println(e); }
		}
		int length = displayBox.getText().length() - 1;
		displayBox.select(length, length);
	}
	//显示图片
	private void displayPic(File f) {
		if(f != null) {
			StyledDocument doc = displayBox.getStyledDocument();
			try{
				Image image = ImageIO.read(f);
				Style style = doc.addStyle("StyleName", null);
				StyleConstants.setIcon(style, new ImageIcon(image));
				doc.insertString(doc.getLength(), "invisible text", style);
			}
			catch(Exception e) { System.out.println(e); }
			int length = displayBox.getText().length() - 1;
			displayBox.select(length, length);
		}
		else {
			System.out.print("error");
		}
	}
	//显示文件 目前还不行
	private void displayFile(File f) {
		
		if (f!=null) {
			StyledDocument doc = displayBox.getStyledDocument();
			try{doc.insertString(doc.getLength(), f + "\n", null);}
			catch(Exception e) { System.out.println(e); }
			try{
				displayBox.insertIcon (new ImageIcon(getClass().getResource("../images/happy.jpeg")));}
			catch(Exception e) { System.out.println(e); }
		
		int length = displayBox.getText().length() - 1;
		displayBox.select(length, length);}
		else {
			System.out.print("error");
		}
		
	}
	//发送消息
	private void sendMessage(MessageBean message) {
		if (message != null) {
			inputBox.setText(null);
			inputBox.setCaretPosition(0);
			display(my_name,message);
			if (server != null) {
				if ("所有用户".equals(usersBox.getSelectedItem())) {// 发送给所有用户
					try {
						server.chat(my_name, message);
					} catch (java.rmi.RemoteException ex) {
						ex.printStackTrace();
					}
				} else {// 私聊，发给所选用户
					String destUserName = (String) usersBox.getSelectedItem();
					Chatter destChatter = (Chatter) hash.get(destUserName);
					try {
						destChatter.receiveWhisper(my_name, message);
					} catch (RemoteException e) {
						e.printStackTrace();
					}
				}
			}
		}
		inputBox.requestFocus();
	}
	//发送图片消息  
	private void sendPicMessage() {
		uploadPicMessage();
		MessageBean message=new MessageBean(usersFile);
		sendMessage(message);
	}
	private ImageIcon ii;
	private void uploadPicMessage() { //上传
	    JFileChooser chooser = new JFileChooser();
	    chooser.showOpenDialog(null);
	    final File f = chooser.getSelectedFile();
	    if (f == null) {
	        return;
	    }
	    String filename = f.getName();
	    picName.setText(filename);
	    usersFile=f;
	    SwingWorker sw = new SwingWorker() {
	        @Override
	        protected Object doInBackground() throws Exception {//怕图片太大
	            Thread.sleep(5000);//simulate large image takes long to load
	            //暂时没有完成的功能
	            //ii = new ImageIcon(scaleImage(120, 120, ImageIO.read(new File(f.getAbsolutePath()))));
	            return null;
	        }
	        @Override
	        protected void done() { 
	            super.done();
	            //jLabel1.setIcon(ii);
	        }
	    };
	    sw.execute();
	    return;
	}



	
	
	
	
	
	
	
	
	
	
	
	public void serverStop() {
		displayText("服务器停止");
		server = null;
		hash.clear();
		connectAction.setEnabled(true);
	}
	
	class ConnectionAction extends AbstractAction {
		public ConnectionAction() {
			super("连接");
			putValue(Action.SHORT_DESCRIPTION, "连接到服务器");
			putValue(Action.ACCELERATOR_KEY, KeyStroke.getKeyStroke("control C"));
		}
		
		public void actionPerformed(ActionEvent evt) {
			dlg.pack();
			dlg.setLocationRelativeTo(ChatClient.this);
			dlg.setVisible(true);
			if (dlg.getValue() == JOptionPane.OK_OPTION) {
				try {
					my_name = dlg.getUserName();
					serverAddr = dlg.getServerAddr();
					connect();
					inputBox.setEditable(true);
					displayBox.setText("");
					statusLabel.setText(my_name + " 已连接");
					this.setEnabled(false);
				} catch (Exception e) {
					e.printStackTrace();
					statusLabel.setText("不能连接到服务器");
					return;
				}
			}
		}
	}
}

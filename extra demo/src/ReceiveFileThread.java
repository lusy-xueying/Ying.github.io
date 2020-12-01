
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.ServerSocket;
import java.net.Socket;
 
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
 
 
public class ReceiveFileThread extends Thread{
	
	private ServerSocket connectSocket=null;
	private Socket socket=null;
	private JFrame frame;
	private Container contentPanel;
	private JProgressBar progressbar;
	private DataInputStream dis;
	private DataOutputStream dos;
	private RandomAccessFile rad;
	private JLabel label;
	
	public ReceiveFileThread(){
		frame=new JFrame("�����ļ�");
		try {
			connectSocket=new ServerSocket(8080);
			socket=connectSocket.accept();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void run(){
		try {
			dis=new DataInputStream(socket.getInputStream());
			dos=new DataOutputStream(socket.getOutputStream());
			dis.readUTF();
			
			int permit=JOptionPane.showConfirmDialog(frame, "�Ƿ�����ļ�","�ļ���������", JOptionPane.YES_NO_OPTION);
			if (permit==JOptionPane.YES_OPTION) {
				String filename=dis.readUTF();
				dos.writeUTF("ok");
				dos.flush();
				File file=new File(filename+".temp");
 
				rad=new RandomAccessFile(filename+".temp", "rw");
				
				//����ļ���С
				long size=0;
				if(file.exists()&&file.isFile()){
					size=file.length();
				}
				
				dos.writeLong(size);//�����ѽ��յĴ�С
				dos.flush();
				long allSize=dis.readLong();
				String rsp=dis.readUTF();
				
				int barSize=(int)(allSize/1024);
				int barOffset=(int)(size/1024);							
				
				//�������
				frame.setSize(300,120);
				contentPanel =frame.getContentPane();
				contentPanel.setLayout(new BoxLayout(contentPanel, BoxLayout.Y_AXIS));
				progressbar = new JProgressBar();//������
				
				label=new JLabel(filename+" ������");
				contentPanel.add(label);
				
				progressbar.setOrientation(JProgressBar.HORIZONTAL);
				progressbar.setMinimum(0);
				progressbar.setMaximum(barSize);
				progressbar.setValue(barOffset);
			    progressbar.setStringPainted(true);
			    progressbar.setPreferredSize(new Dimension(150, 20));
			    progressbar.setBorderPainted(true);
			    progressbar.setBackground(Color.pink);
				
			    JButton cancel=new JButton("ȡ��");
			    
			    JPanel barPanel=new JPanel();
			    barPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
			    
			    barPanel.add(progressbar);
			    barPanel.add(cancel);
			    
			    contentPanel.add(barPanel);
			    
			    cancel.addActionListener(new cancelActionListener());
			    
			    frame.setDefaultCloseOperation(
			    		JFrame.EXIT_ON_CLOSE);
			    frame.setVisible(true);
			    
			    //�����ļ�
				if (rsp.equals("ok")) {
					rad.seek(size);
					int length;
					byte[] buf=new byte[1024];
					while((length=dis.read(buf, 0, buf.length))!=-1){
						rad.write(buf,0,length);
						progressbar.setValue(++barOffset);
					}
					System.out.println("end");
				}
				
				label.setText(filename+" ��������");
				
				
				dis.close();
				dos.close();
				rad.close();
				frame.dispose();
				//�ļ�������
				if (barOffset>=barSize) {
					file.renameTo(new File(filename));
				}
				
			}else{
				dis.close();
				dos.close();
				frame.dispose();
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			label.setText(" ��ȡ�����գ����ӹرգ�");		
		}finally {
			frame.dispose();
		}
	}
	
	class cancelActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			try {
				dis.close();
				dos.close();
				rad.close();
				JOptionPane.showMessageDialog(frame, "��ȡ�����գ����ӹرգ�", "��ʾ��", JOptionPane.INFORMATION_MESSAGE);	
				label.setText(" ȡ������,���ӹر�");
			} catch (IOException e1) {
				
			}
		}
	}
	
}

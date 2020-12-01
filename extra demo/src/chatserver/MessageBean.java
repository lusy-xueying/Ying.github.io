package chatserver;

import java.io.File;
import java.io.Serializable;

public class MessageBean implements Serializable {
private static final long serialVersionUID = 1L;
private long messageId;// ��Ϣid
private long groupId;// Ⱥid
private boolean isGoup;// �Ƿ���Ⱥ��Ϣ
private int chatType=1;// ��Ϣ����;1,�ı���2��ͼƬ��3��С��Ƶ��4���ļ���5������λ�ã�6��������7����Ƶͨ��
private String content;// �ı���Ϣ����
private String errorMsg;// ������Ϣ
private int errorCode;// �������
private int userId;//�û�id
private int friendId;//Ŀ�����id
private MessageFileBean chatFile;// ��Ϣ����
public MessageBean(String s) {
	this.content=s;
	this.chatType=1;
}
public MessageBean(File f) {
	this.content="�ļ�";
	this.chatFile=new MessageFileBean(f);
	this.chatType=2;
}
public long getMessageId() {
	return messageId;
}
public void setMessageId(long messageId) {
	this.messageId = messageId;
}
public long getGroupId() {
	return groupId;
}
public void setGroupId(long groupId) {
	this.groupId = groupId;
}
public boolean isGoup() {
	return isGoup;
}
public void setGoup(boolean isGoup) {
	this.isGoup = isGoup;
}
public int getChatType() {
	return chatType;
}
public void setChatType(int chatType) {
	this.chatType = chatType;
}
public String getContent() {
	return content;
}
public void setContent(String content) {
	this.content = content;
}
public String getErrorMsg() {
	return errorMsg;
}
public void setErrorMsg(String errorMsg) {
	this.errorMsg = errorMsg;
}
public int getErrorCode() {
	return errorCode;
}
public void setErrorCode(int errorCode) {
	this.errorCode = errorCode;
}
public int getUserId() {
	return userId;
}
public void setUserId(int userId) {
	this.userId = userId;
}
public int getFriendId() {
	return friendId;
}
public void setFriendId(int friendId) {
	this.friendId = friendId;
}
public MessageFileBean getChatFile() {
	return chatFile;
}
public void setChatFile(MessageFileBean chatFile) {
	this.chatFile = chatFile;
}
}
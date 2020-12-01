package chatserver;

import java.io.File;
import java.io.Serializable;

public class MessageFileBean implements Serializable {
private static final long serialVersionUID = 3L;
private int fileId;//�ļ�id
private String fileName;//�ļ�����
private long fileLength;//�ļ�����
//private Byte[] fileByte;//�ļ�����
private File file;//�ļ�����
private String fileType;//�ļ�����
private String fileTitle;//�ļ�ͷ����
public MessageFileBean(File f) {
	this.file=f;
}
public int getFileId() {
	return fileId;
}
public void setFileId(int fileId) {
	this.fileId = fileId;
}
public String getFileName() {
	return fileName;
}
public void setFileName(String fileName) {
	this.fileName = fileName;
}
public long getFileLength() {
	return fileLength;
}
public void setFileLength(long fileLength) {
	this.fileLength = fileLength;
}
public String getFileType() {
	return fileType;
}
public void setFileType(String fileType) {
	this.fileType = fileType;
}
public String getFileTitle() {
	return fileTitle;
}
public void setFileTitle(String fileTitle) {
	this.fileTitle = fileTitle;
}
public File getFile() {
	return file;
}
public void setFile(File file) {
	this.file = file;
}
}

package chatserver;

import java.util.EventObject;

// 服务器事件
public class ChatServerEvent extends EventObject {
	MessageBean message;
	
	public ChatServerEvent(Object src, MessageBean message) {
		super(src);
		setMessage(message);
	}

	public String getMessage() {
		return message.getContent();
	}

	public void setMessage(MessageBean message) {
		this.message = message;
	}

}

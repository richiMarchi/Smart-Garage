package sg.serial_monitor;

public interface CommChannel {

    void sendMsg(String msg);
    String receiveMsg() throws InterruptedException;
    boolean isMsgAvailable();

}

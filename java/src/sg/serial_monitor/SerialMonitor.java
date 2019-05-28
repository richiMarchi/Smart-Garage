package sg.serial_monitor;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

public class SerialMonitor implements SerialPortEventListener, CommChannel {

    private static final int TIME_OUT = 2000;

    private SerialPort serialPort;
    private BufferedReader input;
    private OutputStream output;
    private BlockingQueue<String> queue;

    public void start(String portName, int dataRate) {
        queue = new ArrayBlockingQueue<String>(100);
        CommPortIdentifier portId = null;

        try {
            portId = CommPortIdentifier.getPortIdentifier(portName);
            // open serial port, and use class name for the appName.
            serialPort = (SerialPort) portId.open(this.getClass().getName(),
                            TIME_OUT);

            // set port parameters
            serialPort.setSerialPortParams(dataRate,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
            input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
            output = serialPort.getOutputStream();

            serialPort.addEventListener(this);
            serialPort.notifyOnDataAvailable(true);
        } catch (Exception e) {
            System.err.println(e.toString());
        }
    }

    public synchronized void close() {
        if (serialPort != null) {
            serialPort.removeEventListener();
            serialPort.close();
        }
    }

    @Override
    public void serialEvent(SerialPortEvent oEvent) {
        if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
            try {
                    String msg=input.readLine();
                    queue.put(msg);
            } catch (Exception e) {
                    System.err.println(e.toString());
            }
        }
    }

    @Override
    public void sendMsg(String msg) {
        char[] array = (msg+"\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++){
                bytes[i] = (byte) array[i];
        }
        try {
                output.write(bytes);
                output.flush();
        } catch(Exception ex){
                ex.printStackTrace();
        }
    }

    @Override
    public String receiveMsg() throws InterruptedException {
        return queue.take();
    }

    @Override
    public boolean isMsgAvailable() {
        return !queue.isEmpty();
    }

    public BlockingQueue<String> getQueue(){
        return this.queue;
    }
}
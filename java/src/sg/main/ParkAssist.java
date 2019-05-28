package sg.main;

import javax.swing.JTextArea;

import sg.serial_monitor.SerialMonitor;

public class ParkAssist implements Runnable{

    private SerialMonitor monitor;
    private JTextArea txt;
    private boolean cycle;

    public ParkAssist(SerialMonitor monitor, JTextArea txt) {
        this.monitor = monitor;
        this.txt = txt;
    }

    @Override
    public void run() {
        String mess = null;
        cycle = true;
        while (cycle) {
            System.out.println("Parking");
            try {
                mess = monitor.receiveMsg();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (mess.equals("OK")) {
                this.cycle = false;
            }
            this.txt.setText(mess);
        }
    }   
}

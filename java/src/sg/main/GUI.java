package sg.main;

import java.awt.BorderLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import sg.serial_monitor.SerialMonitor;

public class GUI {

    private JFrame frame;
    private JPanel panel;
    private JTextArea txt;
    private JButton arrive;
    private JButton stop;
    private SerialMonitor monitor;
    private Thread parking;
    
    public GUI(SerialMonitor monitor) {
        this.monitor = monitor;
        this.monitor.start("COM3", 9600);
        this.frame = new JFrame();
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.frame.setTitle(".::Car OnBoard PC::.");
        this.frame.setLocationRelativeTo(null);
        this.panel = new JPanel();
        this.panel.setLayout(new BorderLayout());
        this.txt = new JTextArea();
        this.txt.setSize(50, 100);
        this.arrive = new JButton("ARRIVING!");
        this.arrive.setSize(50, 50);
        this.arrive.addActionListener(e -> {
            this.monitor.getQueue().clear();
            this.monitor.sendMsg("a");
            String received = null;
            try {
                received = monitor.receiveMsg();
                System.out.println(received);
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            }
            this.txt.setText(received);
            if (received.equals("Welcome Home.")) {
                parking = new Thread(new ParkAssist(this.monitor, this.txt));
                parking.start();
                this.arrive.setEnabled(false);
                this.stop.setEnabled(true);
            }
        });
        this.stop = new JButton("STOP!");
        this.stop.setEnabled(false);
        this.stop.setSize(50,50);
        this.stop.addActionListener(l -> {
            this.monitor.sendMsg("s");
            String s = null;
            while (!((s = this.txt.getText()).equals("OK") || (s = this.txt.getText()).equals("TOO FAR"))) {}
            if (s.equals("OK")) {
                this.txt.setText(".::Car OnBoard PC::.");
                this.stop.setEnabled(false);
                this.arrive.setEnabled(true);
                if (!parking.isAlive()) {
                    System.out.println("M'agg fermato!");
                }
            }
        });
        this.txt.setText(".::Car OnBoard PC::.");
        this.txt.setEditable(false);

        this.frame.setContentPane(this.panel);
        this.panel.add(this.arrive, BorderLayout.WEST);
        this.panel.add(this.stop, BorderLayout.EAST);
        this.panel.add(this.txt, BorderLayout.SOUTH);
        this.frame.pack();
        this.frame.setResizable(false);
        this.frame.setVisible(true);
    }

    public JTextArea getTxtArea() {
        return this.txt;
    }
}

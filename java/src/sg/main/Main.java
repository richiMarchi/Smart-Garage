package sg.main;

import sg.serial_monitor.SerialMonitor;

public class Main {

    public static void main(String[] args) {
        new GUI(new SerialMonitor());
    }
}

# WLED-Controller
Simple project that takes care of LED strips and connect them using esp32 to home assistant interface.

![image](https://github.com/user-attachments/assets/ace5ed26-4013-484a-8079-e882eb7c22a7)

# DO NOT ORDER PCB NOW BOARDS HAS COUPLE ISSUES!!


1) R7 EN pin of xl1509-5.0v need going to GND not input
2) Pin 9 is needed to be pulled on to boot esp32-c3 chip
3) DS18b20 pin needed to be pulled to 3.3V (fixed on rev 1.6)
4) more space for C1,C3,C9


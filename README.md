# Voting-Machine

Hardwares used Webcam, Arduino Uno, Finger Print Sensor FPM10A, 2 LEDs, push buttons for number of candidates, resistors for push buttons and LEDs, jumper wires, bread board.

For finger print sensor we used [Adafruit-Fingerprint-Sensor-Library](https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library).
For passing data through serial connection [PySerial](https://pypi.org/project/pyserial/) is used.

### How to build

Connect finger print sensor to pin 2 and pin 3 of Arduino, Red LED to pin 6 and Green to pin 8. it is made for two candidates s0 there are two push buttton, one is connected to pin 5 and one to pin 10.

Upload the code to Arduino and keep connected the USB cable with PC. Now connect the webcam with PC. Edit webcam.py file to change the COM port accordingly. Finally run the webcam.py (Terminal/CMD is recommanded)

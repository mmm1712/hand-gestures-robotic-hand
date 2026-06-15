# Software Setup

*Note: This repository is a fork of Marina's original project. I am contributing these docs to make her build easier to follow.*

The code runs in two places: C++ on the ESP32, and Python on your computer.

## 1. Flashing the ESP32
1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Add ESP32 boards to the Boards Manager.
3. Install the Adafruit PWM Servo Driver Library from the Library Manager.
4. Open the `.ino` file in the `esp32/` folder.
5. Plug in your ESP32, pick the right COM port, and hit upload.

## 2. Running the Python tracker
The Python script grabs your webcam feed, processes the hand landmarks with MediaPipe, and sends the open/close commands to the ESP32 over serial.

You need Python 3.9 or newer.

Open a terminal in the `Python/` directory and set up your environment:

```bash
python -m venv venv
source venv/bin/activate  # On Windows, use: venv\Scripts\activate
pip install opencv-python mediapipe pyserial
```

Plug in the ESP32 and turn on the external power supply for the servos. You might need to edit the Python script to match the serial port your ESP32 is connected to (like `COM3` on Windows or `/dev/cu.usbserial-0001` on a Mac).

Run the tracker:
```bash
python hand_test.py
```
Hold your hand in front of the webcam. The robotic hand should mirror what you do.

---
**Previous Step: [Hardware Assembly & Wiring](ASSEMBLY.md)** | **Back to Home: [README](../README.md)**

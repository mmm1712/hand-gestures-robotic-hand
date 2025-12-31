# 🤖 Hand Gesture Controlled Humanoid Robotic Hand

This project demonstrates a **humanoid robotic hand controlled in real time by human hand gestures** using computer vision and embedded systems.

A webcam tracks my hand movements, Python interprets the gestures, and an ESP32 drives multiple servos to mirror those motions on a 3D-printed robotic hand.

Less than a year ago, I didn’t know how to build systems like this — finishing this project felt like a small dream come true. 
There’s still a lot of room for improvement, and I’m excited to keep building.

## ✨ Demo

📹 **YouTube demo:** *link will be added soon*  
🖼️ **Media:** GIFs and images will be added here soon.


## 🧠 How It Works (High Level)

### Pipeline
1. Webcam captures live video  
2. MediaPipe detects hand landmarks in real time  
3. Python determines finger states (open / closed)  
4. Serial communication sends commands to the ESP32  
5. ESP32 + PCA9685 drives servos to match gestures  

Python sends **high-level intent** (finger positions),  
while the ESP32 handles **precise motor control**.


## 🧩 Hardware

- ESP32 (Arduino framework)
- PCA9685 16-channel servo driver (I2C)
- 4× servo motors:
  - Middle finger  
  - Thumb  
  - Index finger  
  - Ring + pinky (shared servo for this version)
- External 5–6V power supply for servos
- 3D-printed humanoid hand
- Webcam (built-in or external)

*Ring and pinky currently share one servo to simplify mechanics.  
I plan to separate them in a future revision.*


## 💻 Software

### Python (runs on computer)
- Python 3.9+
- OpenCV — camera input
- MediaPipe — real-time hand tracking
- pySerial — communication with ESP32

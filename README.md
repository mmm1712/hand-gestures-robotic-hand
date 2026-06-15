# Hand Gesture Controlled Humanoid Robotic Hand

[![YouTube Demo](https://img.youtube.com/vi/_GSqwtdkvcs/hqdefault.jpg)](https://www.youtube.com/watch?v=_GSqwtdkvcs)
> *Watch the YouTube Demo*

This project demonstrates a **humanoid robotic hand controlled in real time by human
hand gestures** using computer vision and embedded systems.

A webcam tracks my hand movements, Python interprets the gestures, and an ESP32 drives
multiple servos to mirror those motions on a 3D-printed robotic hand.

## How It Works

### Pipeline
1. Webcam captures live video
2. MediaPipe detects hand landmarks in real time
3. Python determines finger states (open / closed)
4. Serial communication sends commands to the ESP32
5. ESP32 + PCA9685 drives servos to match gestures

Python sends **high-level intent** (finger positions), while the ESP32 handles
**precise motor control**.

## Repository Structure

```text
hand-gestures-robotic-hand/
├── docs/
│   ├── BOM.md               # Parts you need to buy and print
│   ├── ASSEMBLY.md          # Hardware wiring and physical build
│   └── SOFTWARE.md          # Flashing the ESP32 and running the Python tracker
├── Python/
│   └── ...                  # MediaPipe and PySerial scripts
├── esp32/
│   └── ...                  # C++ code for the microcontroller
└── README.md                # You are here
```

## Quick Start

If you want to build this, check the `docs/` folder.
1. **Get the parts:** The [Bill of Materials (BOM)](docs/BOM.md) lists the electronics and links to the 3D printable files.
2. **Build the hardware:** The [Assembly Guide](docs/ASSEMBLY.md) covers how to put it together and wire the servos.
3. **Run the code:** The [Software Guide](docs/SOFTWARE.md) explains how to set up Python and flash the ESP32.

## Hardware

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

*Ring and pinky currently share one servo to simplify mechanics. I plan to separate
them in a future revision.*

## Software

Full setup is in [docs/SOFTWARE.md](docs/SOFTWARE.md).

### Python (runs on computer)
- Python 3.9+
- OpenCV — camera input
- MediaPipe — real-time hand tracking
- pySerial — communication with ESP32

---

*Documentation structure and the [project landing page](https://maxsikorski.github.io/hand-gestures-robotic-hand/)
were contributed by [Max Sikorski](https://github.com/MaxSikorski). All project code and design by Marina ([@mmm1712](https://github.com/mmm1712)).*

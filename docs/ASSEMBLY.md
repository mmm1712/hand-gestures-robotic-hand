# Assembly Guide

*Note: This repository is a fork of Marina's original project. I am contributing these docs to make her build easier to follow.*

## 1. The physical build
Before touching the electronics, put the 3D-printed hand together. 

Watch the [original YouTube assembly video](https://www.youtube.com/watch?v=L2ddw3MQl9g). It shows exactly how to string the tendons and place the servos. Run your fishing line from the fingertips down to the servo horns, and glue the elastic cord to the back of the fingers so they pull open automatically.

## 2. Wiring

### ESP32 to PCA9685
The PCA9685 talks to the ESP32 over I2C. Connect them like this:

| PCA9685 Pin | ESP32 Pin |
|-------------|-----------|
| VCC         | 3.3V      |
| GND         | GND       |
| SDA         | GPIO 21   |
| SCL         | GPIO 22   |

### Servos
Plug the four servos into the PCA9685. The code expects them on these specific channels (this matches the `#define` lines at the top of `esp32/humanoid_hand/humanoid_hand.ino`):
- Channel 0: Middle finger
- Channel 1: Thumb
- Channel 2: Ring and pinky (shared)
- Channel 3: Index finger

### Power
Do not power the servos directly from the ESP32's 5V pin. You will fry the board or cause constant brownouts. 

Connect your external 5V/6V power supply to the V+ and GND screw terminals on the PCA9685. Make sure you tie the ESP32's GND to the PCA9685's GND so they share a common ground.

---
**Previous Step: [Bill of Materials](BOM.md)** | **Next Step: [Software Setup](SOFTWARE.md)**

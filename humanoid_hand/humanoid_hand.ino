#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// servo
// Channel mapping 
#define SERVO_MIDDLE 0
#define SERVO_THUMB  1
#define SERVO_RING   2   
#define SERVO_INDEX  3

// Safe motion limits 
#define ANGLE_MIN 25
#define ANGLE_MAX 155

// calibration
int angleToPulse(int angle) {
  angle = constrain(angle, 0, 180);
  return map(angle, 0, 180, 130, 630); 
}


int maybeInvert(uint8_t ch, int angle) {
  if (ch == SERVO_THUMB || ch == SERVO_MIDDLE) {
    return 180 - angle;
  }
  return angle;
}

// servo control
void setServoAngle(uint8_t ch, int angle) {
  angle = constrain(angle, ANGLE_MIN, ANGLE_MAX);
  angle = maybeInvert(ch, angle);

  int pulse = angleToPulse(angle);
  pwm.setPWM(ch, 0, pulse);
}

void setAll(int angle) {
  setServoAngle(SERVO_MIDDLE, angle);
  setServoAngle(SERVO_THUMB,  angle);
  setServoAngle(SERVO_RING,   angle);
  setServoAngle(SERVO_INDEX,  angle);
}

// serial passer
static String inputLine;

void handleCommand(String cmd) {
  cmd.trim();

  String parts[6];
  int count = 0;
  int last = 0;

  for (int i = 0; i < cmd.length(); i++) {
    if (cmd[i] == ',') {
      parts[count++] = cmd.substring(last, i);
      last = i + 1;
    }
  }
  parts[count++] = cmd.substring(last);

  parts[0].toUpperCase();

  // A,90 
  if (parts[0] == "A" && count >= 2) {
    int angle = parts[1].toInt();
    setAll(angle);
    Serial.printf("OK A %d\n", angle);
    return;
  }

  // S,channel,angle 
  if (parts[0] == "S" && count >= 3) {
    int ch = parts[1].toInt();
    int angle = parts[2].toInt();
    if (ch >= 0 && ch <= 15) {
      setServoAngle(ch, angle);
      Serial.printf("OK S %d %d\n", ch, angle);
    } else {
      Serial.println("ERR bad channel");
    }
    return;
  }

  // M,a0,a1,a2,a3 
  if (parts[0] == "M" && count >= 5) {
    setServoAngle(SERVO_MIDDLE, parts[1].toInt());
    setServoAngle(SERVO_THUMB,  parts[2].toInt());
    setServoAngle(SERVO_RING,   parts[3].toInt());
    setServoAngle(SERVO_INDEX,  parts[4].toInt());
    Serial.println("OK M");
    return;
  }

  Serial.println("ERR unknown command");
}


void setup() {
  Serial.begin(115200);

  // I2C for ESP32
  Wire.begin(21, 22);  // SDA, SCL
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(10);


  setAll(90);

  Serial.println("READY");
  Serial.println("Commands:");
  Serial.println("A,<angle>");
  Serial.println("S,<ch>,<angle>");
  Serial.println("M,<middle>,<thumb>,<ring>,<index>");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      handleCommand(inputLine);
      inputLine = "";
    } else {
      inputLine += c;
    }
  }
}



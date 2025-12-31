#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// servo
int servoAngle = 90;

// encoder
const int ENCODER_CLK = 32;
const int ENCODER_DT  = 33;
const int ENCODER_SW  = 25;

int lastCLK;

// Convert angle 
int angleToPulse(int angle) {
  return map(angle, 0, 180, 130, 630);
}

void moveServos(int angle) {
  int pulse = angleToPulse(angle);
  pwm.setPWM(0, 0, pulse); // middle finger
  pwm.setPWM(1, 0, pulse); // thumb
  pwm.setPWM(2, 0, pulse); // pinky and ring
  pwm.setPWM(3, 0, pulse); // index
}

void setup() {
  Serial.begin(115200);

  // i2c
  Wire.begin(21, 22); // SDA, SCL
  pwm.begin();
  pwm.setPWMFreq(50);

  delay(10);

  // centered
  moveServos(servoAngle);

  // encoder
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  lastCLK = digitalRead(ENCODER_CLK);
}

void loop() {
  int currentCLK = digitalRead(ENCODER_CLK);

  if (currentCLK != lastCLK) {
    if (digitalRead(ENCODER_DT) != currentCLK) {
      servoAngle += 2;
    } else {
      servoAngle -= 2;
    }

    // Range of motion
    servoAngle = constrain(servoAngle, 25, 155);

    moveServos(servoAngle);
    Serial.println(servoAngle);
  }

  lastCLK = currentCLK;

  // button reset to center
  if (digitalRead(ENCODER_SW) == LOW) {
    servoAngle = 90;
    moveServos(servoAngle);
    delay(300);
  }
}



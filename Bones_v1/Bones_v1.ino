#include <Servo.h>

// Shoulder
Servo s1;
const int pin1 = 9;

// Elbow
Servo s2;
const int pin2 = 10;

// Gripper
Servo s3;
const int pin3 = 11;

// Live angles
int angle_s1 = 90;
int angle_s2 = 90;
int angle_s3 = 90;

// Memory arrays
int recorded1[40];
int recorded2[40];
int recorded3[40];
int frameIndex = 0;

void setup() {
  Serial.begin(115200);

  s1.attach(pin1);
  s1.write(angle_s1);

  s2.attach(pin2);
  s2.write(angle_s2);

  s3.attach(pin3);
  s3.write(angle_s3);

  Serial.println("READY");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.startsWith("s1 ")) {
      angle_s1 = constrain(cmd.substring(3).toInt(), 0, 180);
      smoothMove(s1, angle_s1);
    }
    else if (cmd.startsWith("s2 ")) {
      angle_s2 = constrain(cmd.substring(3).toInt(), 0, 180);
      smoothMove(s2, angle_s2);
    }
    else if (cmd.startsWith("s3 ")) {
      angle_s3 = constrain(cmd.substring(3).toInt(), 0, 180);
      smoothMove(s3, angle_s3);
    }
    else if (cmd.equals("STORE")) {
      storePosition();
    }
    else if (cmd.equals("REPLAYSEQ")) {
      replaySequence();
    }
    else if (cmd.equals("RESET")) {
      resetAllServos();
    }
  }
}

void smoothMove(Servo &servoObj, int target) {
  int current = servoObj.read();
  int step = (target > current) ? 1 : -1;

  for (int pos = current; pos != target; pos += step) {
    servoObj.write(pos);
    delay(5); // smoother motion
  }
}

void storePosition() {
  if (frameIndex < 40) {
    recorded1[frameIndex] = angle_s1;
    recorded2[frameIndex] = angle_s2;
    recorded3[frameIndex] = angle_s3;
    frameIndex++;
    Serial.println("STORED");
  } else {
    Serial.println("FULL");
  }
}

void replaySequence() {
  if (frameIndex == 0) {
    Serial.println("EMPTY");
    return;
  }

  for (int i = 0; i < frameIndex; i++) {
    smoothMove(s1, recorded1[i]);
    smoothMove(s2, recorded2[i]);
    smoothMove(s3, recorded3[i]);
    smoothMove(s3, recorded3[i]);
    delay(150);
  }
}

void resetAllServos() {
  smoothMove(s1, 90);
  smoothMove(s2, 90);
  smoothMove(s3, 90);

  angle_s1 = angle_s2 = angle_s3 = 90;
  Serial.println("RESET_DONE");
}

#include <Wire.h>
#include <Servo.h>

// ---------------- SERVOS ----------------
Servo servoMPU;      // pin 9
Servo servoJoyX;     // pin 10
Servo servoJoyY;     // pin 11
Servo servoGrip;     // pin 6

// ---------------- INPUT PINS ----------------
const int joyX = A2;
const int joyY = A1;

const int btnX = 5;        
const int btnY = 3;        
const int btnMPU = 4;      
const int btnGrip = 7;     

// ---------------- MPU VARIABLES ----------------
int16_t ax, ay, az;
int16_t gx, gy, gz;

float smoothAX = 0;

// ---------------- LAST POSITIONS ----------------
int lastJoyX = 90;
int lastJoyY = 90;
int lastMPUAngle = 90;

// raw joystick previous values
int lastRawJoyX = 512;
int lastRawJoyY = 512;

// deadband to prevent tiny noise
const int deadband = 20;

// ---------------- SMOOTH SERVO FUNC ----------------
void smoothMove(Servo &servoObj, int target)
{
  int current = servoObj.read();
  int step = (target > current) ? 1 : -1;

  for (int pos = current; pos != target; pos += step)
  {
    servoObj.write(pos);
    delay(4);
  }
}

// ---------------- RAW MPU READ ----------------
void readMPU()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14);

  ax = (Wire.read() << 8) | Wire.read();
  ay = (Wire.read() << 8) | Wire.read();
  az = (Wire.read() << 8) | Wire.read();

  Wire.read(); Wire.read(); // temp skip

  gx = (Wire.read() << 8) | Wire.read();
  gy = (Wire.read() << 8) | Wire.read();
  gz = (Wire.read() << 8) | Wire.read();
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // MPU wake
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // ACC sensitivity
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x00);
  Wire.endTransmission();

  // GYRO sensitivity
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x00);
  Wire.endTransmission();

  // Servos
  servoMPU.attach(9);
  servoJoyX.attach(10);
  servoJoyY.attach(11);
  servoGrip.attach(6);

  // Buttons
  pinMode(btnX, INPUT_PULLUP);
  pinMode(btnY, INPUT_PULLUP);
  pinMode(btnMPU, INPUT_PULLUP);
  pinMode(btnGrip, INPUT_PULLUP);
}

void loop() {

  // ---------------- MPU CONTROL ----------------
  if (digitalRead(btnMPU) == LOW)
  {
    readMPU();

    float boostedAX = ax / 150.0;
    smoothAX = smoothAX * 0.7 + boostedAX * 0.3;

    int mpuAngle = map(smoothAX, -150, 150, 0, 180);
    mpuAngle = constrain(mpuAngle, 0, 180);

    servoMPU.write(mpuAngle);
    lastMPUAngle = mpuAngle;
  }
  else
  {
    servoMPU.write(lastMPUAngle);
  }

// ---------------- JOYSTICK X (continuous rotation logic) ----------------
if (digitalRead(btnX) == LOW)
{
  int jx = analogRead(joyX);
  int center = 512;
  int deadband = 10; // small noise filter

  if (abs(jx - center) > deadband)
  {
    int targetSpeed = map(jx, 0, 1023, 40, 140);
    // 60..120 gives slow rotation both ways
    // 90 = stop

    if (lastJoyX < targetSpeed) lastJoyX++;
    else if (lastJoyX > targetSpeed) lastJoyX--;

    servoJoyX.write(lastJoyX);
    delay(5);     // tune speed of change
  }
  else
  {
    if (lastJoyX < 90) lastJoyX++;
    else if (lastJoyX > 90) lastJoyX--;

    servoJoyX.write(lastJoyX);
    delay(5);
  }
}
else
{
  if (lastJoyX < 90) lastJoyX++;
  else if (lastJoyX > 90) lastJoyX--;

  servoJoyX.write(lastJoyX);
  delay(5);
}


  // ---------------- JOYSTICK Y (only move on real input) ----------------
  if (digitalRead(btnY) == LOW)
  {
    int jy = analogRead(joyY);

    if (abs(jy - lastRawJoyY) > deadband)
    {
      int mappedY = map(jy, 0, 1023, 0, 180);
      mappedY = constrain(mappedY, 0, 180);

      smoothMove(servoJoyY, mappedY);

      lastJoyY = mappedY;
      lastRawJoyY = jy;
    }
  }
  else
  {
    servoJoyY.write(lastJoyY);
  }

  // ---------------- GRIPPER ----------------
  if (digitalRead(btnGrip) == LOW)
  {
    smoothMove(servoGrip, 180);
  }
  else
  {
    smoothMove(servoGrip, 90);
  }

  delay(5);
}

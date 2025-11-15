<p align="center">
  <img src="Bones.gif" width="500">
</p>

This is an Arduino-controlled robotic arm designed for simple, precise movement using commands sent through the serial port. A Python slider interface is used to send these commands, making it easy to control each joint in real time.

#Overview

This robotic arm is a 3-DOF (Degrees of Freedom) build.
The structure is made using cardboard and ice sticks, keeping the design lightweight and cost-effective.
The project name BONES is inspired by names from Iron Man comics.

#Features

Real-time manual control using Python sliders

Smooth servo movement using Arduino

Lightweight handcrafted structure

Adjustable joint angles through serial communication

Beginner-friendly and easy to replicate

#Components Used

MG995 Servo Motor (Shoulder)

MG90S Servo Motor (Elbow)

SG90 Servo Motor (Gripper)

Arduino Uno

Breadboard & Jumper Wires

SMPS 12V 2A, bucked down to 5.1V

Cardboard + Ice Sticks for the arm structure

#Software

Arduino IDE for servo control

Python for serial communication and slider control

#How It Works

The Python script sends joint angle values through the serial port.

The Arduino reads these values and adjusts servo positions.

The arm responds instantly to slider movements, enabling precise manual control.

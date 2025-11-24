<p align="center">
  <a href="https://youtube.com/shorts/jO0Q1HlnmCU">
    <img src="https://img.youtube.com/vi/jO0Q1HlnmCU/maxresdefault.jpg" width="350">
  </a>
</p>


# **Bones v2 – Arduino + Joystick + MPU Controlled Robotic Arm**

This is the upgraded version of the Bones robotic arm project. The arm now supports joystick control, button-based mode switching, and MPU6050-based motion tracking. The movement is smoother, more responsive, and far more intuitive than the earlier Python-slider control version.The Bones V1 worked by giving commands by a python slider which communicates to arduino via the serial port.(I have provided both V1 and V2 codes in the repo)

## **Overview**
Bones v2 is a multi-DOF robotic arm designed for precise and fluid movement.  
The mechanical structure still follows a lightweight, low-cost approach, but the control system is now significantly more advanced.

The project name **BONES** inspired by Iron Man comics.

## **New Features in Bones v2**
- **Joystick-based servo control** for intuitive manual manipulation  
- **MPU6050 motion sensor control** for gesture-based operation  
- **Push-button mode switching** between joystick control and MPU control  
- **Ultra-smooth servo movements** with filtering and speed control  
- **Fine near-center sensitivity** for delicate robotic arm adjustments  
- **Improved power stability** using capacitors to smooth servo loads  
- **Supports both continuous and 180-degree servos**  

## **Existing Features**
- Manual control via Arduino (formerly Python sliders)  
- Adjustable joint angles through real-time inputs  
- Beginner-friendly and easy to expand  

## **Components Used**
- MG996 Servo motor (Base)
- MG995 Servo Motor (Shoulder)  
- MG90S Servo Motor (Elbow)  
- SG90 Servo Motor (Gripper)  
- Joystick Module  
- MPU6050 Sensor  
- Arduino Uno  
- Breadboard & Jumper Wires  
- SMPS 12V 2A bucked down to 5.1V  
- Lightweight cardboard + wooden stick structure (temporary prototype)

## **Control Modes**
### **1. Joystick Mode**
- X and Y axes control different servos  
- High sensitivity near the center for precise micro-movements  
- Slow-step servo increments for stable lifting

### **2. MPU Mode**
- Arm follows the user’s hand tilt and rotation  
- Smooth filtered sensor data  
- Activated via push-button  

## **How It Works**
Joystick or MPU values are read by the Arduino.  
The Arduino processes the inputs, applies smoothing, and updates servo angles gradually to avoid sudden jumps.  
This enables realistic robotic motion and improved lifting capability.

## **Future Updates**
- Stronger physical structure with a proper base  
- More DOF for advanced movement  
- Automated motion sequences and presets  
- Gesture control refinements  
- Swapping cardboard components for high-durability materials  

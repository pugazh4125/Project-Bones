import sys
import serial
import time
from PyQt5.QtWidgets import QApplication, QWidget, QSlider, QLabel, QVBoxLayout, QPushButton
from PyQt5.QtCore import Qt

# Change COM port here
ser = serial.Serial("COM3", 115200, timeout=1)
time.sleep(2)

positions = []  # to store frames

class SliderApp(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("SNAP Controller")
        self.resize(300, 300)

        layout = QVBoxLayout()

        # S1 slider
        self.slider1 = QSlider(Qt.Horizontal)
        self.slider1.setRange(0, 180)
        self.slider1.setValue(90)
        self.slider1.valueChanged.connect(self.send_s1)
        layout.addWidget(QLabel("Shoulder"))
        layout.addWidget(self.slider1)

        # S2 slider
        self.slider2 = QSlider(Qt.Horizontal)
        self.slider2.setRange(0, 180)
        self.slider2.setValue(90)
        self.slider2.valueChanged.connect(self.send_s2)
        layout.addWidget(QLabel("Elbow"))
        layout.addWidget(self.slider2)

        # S3 slider
        self.slider3 = QSlider(Qt.Horizontal)
        self.slider3.setRange(0, 180)
        self.slider3.setValue(90)
        self.slider3.valueChanged.connect(self.send_s3)
        layout.addWidget(QLabel("Gripper"))
        layout.addWidget(self.slider3)

        # STORE BUTTON
        self.store_btn = QPushButton("Store")
        self.store_btn.clicked.connect(self.store_position)
        layout.addWidget(self.store_btn)

        # REPLAY BUTTON
        self.replay_btn = QPushButton("Replay")
        self.replay_btn.clicked.connect(self.replay_motion)
        layout.addWidget(self.replay_btn)

        # RESET BUTTON
        self.reset_btn = QPushButton("Reset")
        self.reset_btn.clicked.connect(self.reset_positions)
        layout.addWidget(self.reset_btn)

        self.setLayout(layout)

    def send_s1(self):
        ang = self.slider1.value()
        ser.write(f"s1 {ang}\n".encode())

    def send_s2(self):
        ang = self.slider2.value()
        ser.write(f"s2 {ang}\n".encode())

    def send_s3(self):
        ang = self.slider3.value()
        ser.write(f"s3 {ang}\n".encode())

    def store_position(self):
        pos = (self.slider1.value(), self.slider2.value(), self.slider3.value())
        positions.append(pos)
        print("Stored:", pos)

    def replay_motion(self):
        for pos in positions:
            s1, s2, s3 = pos
            ser.write(f"s1 {s1}\n".encode())
            ser.write(f"s2 {s2}\n".encode())
            ser.write(f"s3 {s3}\n".encode())
            time.sleep(1)

    def reset_positions(self):
        positions.clear()
        print("Positions cleared.")


app = QApplication(sys.argv)
window = SliderApp()
window.show()
sys.exit(app.exec_())

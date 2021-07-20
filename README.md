# Popcorn Counting Microwave with TensorFlow Lite for Microcontrollers

Steps to reproduce the project:
- Hardware requirements:
    - Arduino Nano 33 BLE Sense
    - 4x32 LED Matrix
    - Micro Servo motor
- Recording the data: DataGatherer.ino (microcontroller)
- Receiving and saving the data: data_saver.py (desktop), requires the numpy and pySerial packages
- Training the model: train_model.ipynb (Google Colab or desktop)
- Testing the model: PopcornCounter.ino (microcontroller), requires the ArduinoTensorFlowLite library

Quick videos showing the complete, working project: https://youtu.be/rVzMAEQ_YXo
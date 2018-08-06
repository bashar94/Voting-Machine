import cv2      #need to download
import serial   #need to download
import time

ser = serial.Serial('COM5', 9600) #change COM value accordingly

while True:
    value = ser.readline().strip().decode("utf-8")
    if(len(value) > 3):
        print(value)

    if(len(value) < 3):
        cam = cv2.VideoCapture(-1)
        ret, frame = cam.read()
        img_name = "voter_{}.png".format(value)
        cv2.imwrite(img_name, frame)
        cam.release()











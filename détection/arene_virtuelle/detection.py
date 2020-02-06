from imageai.Detection.Custom import CustomObjectDetection
import cv2

import tensorflow 
from tensorflow import keras

detector = CustomObjectDetection()
detector.setModelTypeAsYOLOv3()
detector.setModelPath("1.h5") 
detector.setJsonPath("detection_config.json")
detector.loadModel()

detections = detector.detectObjectsFromImage(input_image="2.jpg", output_image_path="holo3-detected.jpg")
for detection in detections:
    print(detection["name"], " : ", detection["percentage_probability"], " : ", detection["box_points"])

# -*- coding: utf-8 -*-
"""
Created on Tue Jan 28 15:55:58 2020

@author: Zineb
"""

from imageai.Detection.Custom import CustomObjectDetection
import cv2

import tensorflow 
from tensorflow import keras

detector = CustomObjectDetection()
detector.setModelTypeAsYOLOv3()
detector.setModelPath("arene_reelle_7classes.902.h5") 
detector.setJsonPath("detection_config.json")
detector.loadModel()
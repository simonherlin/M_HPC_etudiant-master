import cv2 as cv
import numpy as np
import tensorflow.keras as kr

WIDTH, HEIGHT = 280, 280
WINDOW_NAME = "mnist_gui"
BRUSH_RADIUS = 20
BRUSH_COLOR = (255, 255, 255)
BACKGROUND_COLOR = 0

model = kr.models.load_model('mnist_model.h5')


def predict(img):
    ml_img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    ml_img = cv.resize(ml_img, (28, 28))
    ml_img = ml_img.astype('float32')
    ml_img /= 255
    ml_img = ml_img.reshape(1, 28, 28, 1)
    prediction = model.predict_classes(ml_img)
    print(prediction[0])


image = cv.imread('test.jpg')
predict(image)


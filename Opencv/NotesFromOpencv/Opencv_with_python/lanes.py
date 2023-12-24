import cv2
import numpy as np
import matplotlib.pyplot as plt


# traces an outline of the edges that correspond to the most sharp changes in intensity
# gradients that exceed the high threshold are traced as bright pixels
# we use canny to outline the strongest gradients in our image
def canny(image):
    gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    blur = cv2.GaussianBlur(gray, (5, 5), 0)
    canny  = cv2.Canny(blur, 50,150)
    # plt.imshow(canny)
    # plt.show()
    return canny

def region_of_interest(image):
    height = image.shape[0] # the length of y axis
    polygons = np.array([
    [(200, height), (1100, height), (550, 250)]
    ])
    mask = np.zeros_like(image)
    cv2.fillPoly(mask, polygons, 255)
    masked_image = cv2.bitwise_and(image, mask)
    return masked_image

# &and  when encounter with 0, there is always going to be 0
# | or  when encounter with 1, there is always going to be 1

def display_lines(image, lines):
    line_image = np.zeros_like(image)
    if lines is not None:
        for line in lines:
            x1,y1,x2,y2 = line.reshape(4)
            cv2.line(line_image,(x1,y1),(x2,y2),(255,0,0),10)
    return line_image

def make_coordinates(image,line_parameters):
    slope,intercept = line_parameters
    y1 = image.shape[0]
    y2 = int(y1*(3/5))
    x1 = int((y1 - intercept)/slope)
    x2 = int((y2-intercept)/slope)
    return np.array([x1,y1,x2,y2])

def averaged_slope_intercept(image, lines):
    left_fit=[]
    right_fit=[]
    for line in lines:
        x1,y1,x2,y2 = line.reshape(4)
        parameters = np.polyfit((x1,x2),(y1,y2),1)
        slope = parameters[0]
        intercept = parameters[1]
        if slope<0:
            left_fit.append((slope,intercept))
        else:
            right_fit.append((slope,intercept))
    left_fit_average = np.average(left_fit,axis=0)
    right_fit_average = np.average(right_fit, axis=0)
    left_line = make_coordinates(image,left_fit_average)
    right_line = make_coordinates(image, right_fit_average)
    return np.array([left_line,right_line])


image = cv2.imread('test_image.jpg')
lane_image = np.copy(image)
canny_image = canny(lane_image)
cropped_image = region_of_interest(canny_image)
lines = cv2.HoughLinesP(cropped_image,2,np.pi/180,100,np.array([]),minLineLength=40, maxLineGap=5)
averaged_lines = averaged_slope_intercept(lane_image,lines)
line_image = display_lines(lane_image,averaged_lines)
combo_image = cv2.addWeighted(lane_image,0.8,line_image,1, 1)

cv2.imshow('result',combo_image)
cv2.waitKey(0)


# 1 convert images to garyscale(one channel ranging from 0 to 255)
# processing one channel is faster and less computational intensive
# edge rapid changes in brightness

# cap = cv2.VideoCapture("test2.mp4")
# while(cap.isOpened()):
#     _, frame = cap.read()
#     canny_image = canny(frame)
#     cropped_image = region_of_interest(canny_image)
#     lines = cv2.HoughLinesP(cropped_image,2,np.pi/180,100,np.array([]),minLineLength=40, maxLineGap=5)
#     averaged_lines = averaged_slope_intercept(frame,lines)
#     line_image = display_lines(frame,averaged_lines)
#     combo_image = cv2.addWeighted(frame,0.8,line_image,1, 1)
#     cv2.imshow('result', combo_image)
#     if cv2.waitKey(1) == ord('q'):
#         break
# cap.release()
# cv2.destroyAllWindows()




# Canny is going to trace our strongest gradients as a series of white pixels
# low_threshold and high_threshold those twe argument
# the gradient is stronger than high_threshold it is a edge pixel
# the gradient is below the low_threshold it is rejected
# the gradient is between lowthreshold and high_threshold will be only accepted
# if that gradient is connected to a strong edge
# document recommends use ratio of one to two or one to three as low_threshold and high_threshold

# derivative on the function in both x and y directions
# small derivative is a small change whereas a big derivative is a big change

# an edge corresponds to a region in an image
# where there is a sharp change in intensity or
# a sharp change in color between adjacent pixels in the image
# the change in brightness over a series of pixels is the gradients
# a strong gradient indicates a steep change whereas a small gradient a shallow change
# Hough transform
# y = kx + b
# Hough Space(霝夫空间) is about k and b, it represents a line with a point
# a point can represents an entire line of k and b value pairs in Hough space

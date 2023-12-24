import cv2
import math

import deal_vex

cap = cv2.VideoCapture(0)

fps = cap.get(cv2.CAP_PROP_FPS)
width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)

h_max = 93
h_min = 0

s_max = 255
s_min = 0

v_max = 255
v_min = 244


def a_(val, *args):
    global h_max
    h_max = val


def b_(val, *args):
    global h_min
    h_min = val


def c_(val, *args):
    global s_max
    s_max = val


def d_(val, *args):
    global s_min
    s_min = val


def e_(val, *args):
    global v_max
    v_max = val


def f_(val, *args):
    global v_min
    v_min = val


cv2.namedWindow("the")

cv2.createTrackbar("h,max", "the", h_max, 180, a_)
cv2.createTrackbar("h min", "the", h_min, 180, b_)

cv2.createTrackbar("s max", "the", s_max, 255, c_)
cv2.createTrackbar("s min", "the", s_min, 255, d_)

cv2.createTrackbar("v,max", "the", v_max, 255, e_)
cv2.createTrackbar("v min", "the", v_min, 255, f_)

while 1:
    # rat, frame = cap.read()
    frame = cv2.imread("out.png")
    # cv2.imshow("cap", frame)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    gray = cv2.GaussianBlur(hsv, (5, 5), 0)
    thr = cv2.inRange(gray, (h_min, s_min, v_min), (h_max, s_max, v_max))

    thr = thr
    cv2.imshow("www", thr)

    # cv2.imwrite("out.png", frame)

    # 开始寻找矩形
    contours, hierarchy = cv2.findContours(thr, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    cv2.drawContours(frame, contours, -1, (200, 20, 200))
    val_ss = deal_vex.find_roi(contours)

    if val_ss:
        ROI_left = min(val_ss)
        left_box = cv2.minAreaRect(contours[0])
        print(left_box)
        sin = math.sin(left_box[3])
        cos = math.sin(left_box[4])
        x, y = left_box[0]
        w, h = left_box[1]

        cv2.line(frame, left_box[0], left_box[1], (100, 100, 100), 1)
        cv2.line(frame, left_box[0], left_box[1], (100, 100, 100), 1)
        cv2.line(frame, left_box[0], left_box[1], (100, 100, 100), 1)
        cv2.line(frame, left_box[0], left_box[1], (100, 100, 100), 1)

        #        cv2.drawContours(frame, left_box, -1, (255, 255, 255))
        ROI_right = max(val_ss)

        center = (int(round((ROI_left[2] + ROI_right[0]) / 2)), int(round((ROI_left[3] + ROI_right[3]) / 2)))
        cv2.line(frame, (ROI_left[2], ROI_left[3]), (ROI_right[0], ROI_right[3]), (100, 100, 100), 1)
        cv2.line(frame, center, center, (255, 255, 255), 50)
    cv2.imshow("ss", frame)

    cv2.waitKey()

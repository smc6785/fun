#include "stdafx.h"
#include <opencv2/opencv.hpp>	
#include <highgui/highgui.hpp>
#include <vector>
#include <thread>


int main()
{
	using namespace std;
	using namespace cv;
	vector<Mat> temp;
	Mat img, dst, dst1, dst2, dst3, canR, canG, canB, canT;
	vector<vector<Point>> contours;
	vector<RotatedRect> rect;
	img = imread("3.jpg");
	split(img, temp);
	canB = temp[0].clone();
	canG = temp[1].clone();
	canR = temp[2].clone();
	canT = canG.clone() - canB.clone();
	dst1 = canT.clone();	//different bwteen B and G;
	canT = canR.clone() - canB.clone();
	dst2 = canT.clone();	//different bwteen R and B;
	canT = (abs(canR.clone() - canG.clone()) + abs(canG.clone() - canR.clone()))/2;
	dst3 = canT.clone();	//different bwteen G and R;
	dst = dst1 + dst2 - dst3;
	//imshow("Blue", temp[0]);
	//imshow("Green", temp[1]);
	//imshow("Red", temp[2]);
	threshold(dst, dst, 0, 255, THRESH_OTSU);
	dilate(dst, dst, getStructuringElement(MORPH_RECT, Size(21, 21)));
	erode(dst, dst, getStructuringElement(MORPH_RECT, Size(21, 21)));
	medianBlur(dst, dst, 5);
	findContours(dst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	drawContours(img, contours, -1, (Scalar)(0, 0, 255), 10);
	imshow("test", dst);
	imshow("shower", img);
	waitKey();
}
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgproc.hpp"

#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;
 
int main()
{
	Mat img = imread("3.jpg");

	if (img.empty())
	{
		cout << "打开图像失败！" << endl;
		return -1;
	}
	
	vector<Mat> channels;
	Mat dst, channelR,channelG,channelB;
	split(img,channels);
	channelR = channels[2].clone();
	channelG = channels[1].clone();
	channelB = channels[0].clone();
	dst =  channelR - channelB-channelG;
	//dst3 = dst1+dst2- yellow - purple;
	imshow("image", dst);	
	waitKey();
	
	threshold(dst, dst, 0, 255, THRESH_OTSU);
	dilate(dst, dst, getStructuringElement(MORPH_RECT, Size(25, 25)));
	erode(dst, dst, getStructuringElement(MORPH_RECT, Size(25, 25)));
	medianBlur(dst, dst, 7);
	vector<vector<Point> > contours;
	findContours(dst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	vector<Rect>target;

	for(int i = 0;i <contours.size();i++){
		Point one;
		Point two;
		Point three;
		Point four;
		Point five;
		Point six;

		one = contours[i][0];
		two = contours[i][1];	
		if (one.x>two.x){
			one  = contours[i][1];
			two =  contours[i][0];
		}
		for(int j = 2;j <contours[i].size();j++){
		Point temp = contours[i][j];
		if (temp.x>two.x){
			two  = temp;
		}else if(temp.x <one.x){
			one = temp;
		}

		three = contours[i][0];
		four = contours[i][1];	
		if (three.x>four.x){
			three  = contours[i][1];
			four =  contours[i][0];
		}
		for(int j = 2;j <contours[i].size();j++){
		Point temp = contours[i][j];
		if (temp.y>three.y){
			three  = temp;
		}else if(temp.y <four.y){
			four = temp;
		}
		}
		}
		
		five.x = one.x;
		five.y = three.y;
		six.x = two.x;
		six.y = four.y;
		
		target.push_back(Rect(five,six));
		//rectangle(img,five,six,(Scalar)(255),10);
		cout<<five.x<<"edgX"<<endl;
		//cout<<edgeY<<"edgeY"<<endl;
		cout<<six.x<<"edgeTwoX"<<endl;
		//cout<<edgeTwoY<<"edgeTwoY"<<endl;
	}

	if(target.size()>0){
		Rect targetFrame = target[0];
		for(int i = 0 ;i<target.size();i++){
			targetFrame = targetFrame|target[i+1];
			// targetFame&taget[i+1] 
			rectangle(img,targetFrame,(Scalar)(255),10);
			}
	}
	
	// for(int i = 0;i <contours.size();i++){
	//  cout<<contours[i].size()<<" size"<<endl;
	// }
	//drawContours(img, contours, -1, (Scalar)(0, 0, 255), 10);
	imshow("image", img);	
	waitKey();
	//channels[0] = Mat(channels[2].size(),channels[2].type(),Scalar(0));
	//channels[1] = Mat(channels[2].size(),channels[2].type(),Scalar(0));
	//channels[0] is blue; channels[1]is green; channels[2] is red
	//merge(channels,dst);


	// Mat gray;
	// cvtColor(img,gray,COLOR_RGB2GRAY);
	// Mat blur;
	// Size size = Size(5,5);
	// GaussianBlur(gray,blur,size,0);
	
	// Mat canny;
	// Canny(gray,canny,50,150);
	
	// for (int i = 0 ; i<100; i++){
	// 	for (int j = 0 ; j<100; j++){
	// img	.at<Vec3b>(i,j)[0] = 0; 
	// img	.at<Vec3b>(i,j)[1] = 0; 
	// img	.at<Vec3b>(i,j)[2] = 0; 
	// 	}
	// }

	// cout<<img.cols<<"cols"<<endl;
	// cout<<img.rows<<"rows"<<endl;
	// cout<<img.total()<<" total"<<endl;
	// cout<<img.type()<<"type"<<endl;
	// cout<<img.channels()<<"channels"<<endl;
	// cout<<img.depth()<<"depth"<<endl;
	// cout<<img.elemSize()<<"size"<<endl;
	// cout<<img.elemSize1()<<"szie1"<<endl;

	// int a  = img.at<Vec3b>(0,0)[0];
	// cout<<a<<"at"<<endl;
	// int b  = gray.at<uchar>(100,100);
	// cout<<b<<"gray at"<<endl;

	return 0;

}

/*
you have to LINK the opencv libraries to your program, like:

g++ -std=c++11 -o out main.cpp -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui
for opencv4, you also need to correct the INCLUDE path:

g++ -std=c++11 -I/usr/local/include/opencv4 -o out main.cpp -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui*/


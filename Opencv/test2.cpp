
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"



#include <iostream>

int main(){

    //cv::Mat img = cv::imread("desktop/2.jpg");
    cv::VideoCapture cap(0); 
    cv::Mat frame;
    while(1){
       
            cap.read(frame);
            cv::cvtColor(frame,frame,cv::COLOR_RGB2GRAY);
           // std::cout<<"helloworld"<<std::endl;
            int skip = 20;
                for(int i = 0; i<frame.rows;i+=skip){
                    for(int j = 0; j<frame.cols;j+=skip){
                        //std::cout<<i<<"cols"<<std::endl;
	                    //std::cout<<j<<"rows"<<std::endl;
                        //std::cout<<(int)(frame.at<uchar>(i,j))<<std::endl;
                        cv::rectangle(frame, cv::Rect(j,i,skip,skip),(cv::Scalar)((int)(frame.at<uchar>(i,j))),cv::FILLED);

            //cv::point is using the normal coordiante system,
            //however, opencv mat is using top-left and positive values to fo to bottom
                        }
                }
        cv::waitKey(1000); // lower frame per sceond
    
        cv::imshow("test",frame);
        if (cv::waitKey(30) >0)  
        {  
            break;  
            // waitKey(int delay = 0)
            // delay millsecond 
            // when delay <0,keep waitting
            //when delay >0 wait delay millsecond
            // ASCII ESC= 27
        }  

    }
  
    // std::cout<<frame.cols<<"cols"<<std::endl;
	// std::cout<<frame.rows<<"rows"<<std::endl;
    // cv::imshow("test",frame);
    // cv::waitKey();
    return 0;
}
#include "interactive.h"
#include <iostream>


std::vector<checkpoint> points;
int line1=100, line2=300;
bool draggingLine1=false, draggingLine2=false;

void onMouseLines(int event, int x,int y,int flags,void* userdata){ //mouse function for setting scale
    int radius = 10;
    switch(event){
        case cv::EVENT_LBUTTONDOWN: //if clicked near a line, start dragging it
            if(std::abs(x-line1)<radius){
                draggingLine1 = true;
            }else if(std::abs(x-line2)<radius){
                draggingLine2 = true;
            }
            break;

        case cv::EVENT_MOUSEMOVE: //if dragging, move the line
            if(draggingLine1){
                line1 = x;
            }
            if(draggingLine2){
                line2 = x;
            }
            break;
        case cv::EVENT_LBUTTONUP: //stop dragging
            draggingLine1 =false;
            draggingLine2 = false;
            break;
    }
}

void onMouse(int event,int x,int y,int flags,void* userdata){ //mouse function for getting points
    const std::string mapWindow = "Rogaine Map";
    std::cout<<"For the starting location, use 0 as the label."<<std::endl;
    if(event==cv::EVENT_LBUTTONDOWN){ //if left clicked, add a point
        cv::Mat* img = static_cast<cv::Mat*>(userdata);
        cv::imshow(mapWindow, *img);

        //Get the label for the point
        int label; 
        std::cout<<"Clicked at ("<<x<<", "<<y<<"). Enter the two digit number: ";
        std::cin>>label;
        while((label!=0&&label<10)||label>99){
            std::cout<<"Please enter a valid number: ";
            std::cin>>label;
        }

        //Append the point
        points.push_back(checkpoint(label,x,y));

        //Draw the point and label
        cv::circle(*img,cv::Point(x, y),4,cv::Scalar(0, 0, 255),cv::FILLED);
        cv::putText(*img, std::to_string(label), cv::Point(x + 8, y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,0,0),2);
        cv::imshow(mapWindow, *img);
    }
}

int getScale(cv::Mat image){//function to get the scale of the map
    const std::string lineWindow = "Position Lines at 1km";
    cv::namedWindow(lineWindow);
    cv::setMouseCallback(lineWindow, onMouseLines);
    while(true){
        //draw lines
        cv::Mat frame = image.clone();
        cv::line(frame, cv::Point(line1,0), cv::Point(line1,frame.rows), cv::Scalar(0,0,255), 2);
        cv::line(frame, cv::Point(line2,0), cv::Point(line2,frame.rows), cv::Scalar(0,255,0), 2);
        
        //add instructions and live count
        cv::putText(frame, "Position the line 1km apart, then press ENTER", cv::Point(frame.cols/2,frame.rows/3), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,0,0),2);
        cv::putText(frame, "Difference: "+std::to_string(std::abs(line2-line1))+" px", cv::Point(frame.cols/2,frame.rows/2), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,0,0),2);

        cv::imshow(lineWindow, frame);
        if(cv::waitKey(20)==13){break;}//ENTER
    }

    cv::destroyWindow(lineWindow);
    return std::abs(line2-line1);
}

std::vector<checkpoint> getPoints(cv::Mat image){//function to get the points
    const std::string mapWindow = "Rogaine Map";
    cv::namedWindow(mapWindow);
    cv::setMouseCallback(mapWindow, onMouse, &image);
    imshow(mapWindow, image);
    std::cout<<"Click on the map to mark the control points. Press ESC to exit."<<std::endl;
    while(true){if(cv::waitKey(20)==27){break;}}//ESC
    cv::destroyWindow(mapWindow);

    //prints points
    std::cout<<"\nStored points:\n";
    for(auto& p:points){
        std::cout<<p.getID()<<" ("<<p.getX()<<","<< p.getY()<< ") "<<p.getValue()<<std::endl;;
    }
    return points;
}

double pixToKilometres(double pixels,int scale){
    return pixels/scale;
}

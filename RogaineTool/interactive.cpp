#include "interactive.h"
#include <iostream>


std::vector<checkpoint> points;
int line1=100, line2=300;
bool draggingLine1=false, draggingLine2=false;
bool firstpoint=false;

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
    if(event==cv::EVENT_LBUTTONDOWN){ //if left clicked, add a point
        cv::Mat* img = static_cast<cv::Mat*>(userdata);
        cv::imshow(mapWindow, *img);

        //Get the label for the point
        int label; 
        if(!firstpoint){
            label=0;
            firstpoint=true;
            std::cout<<"Label 0 assigned to start point"<<std::endl;
        }else{
            std::cout<<"Clicked at ("<<x<<", "<<y<<"). Enter the two digit number: ";
            std::cin>>label;
            while((label!=0&&label<10)||label>99){
                std::cout<<"Please enter a valid number: ";
                std::cin>>label;
            }
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
        cv::putText(frame, "Position the lines 1km apart, then press ENTER", cv::Point(frame.cols/2,frame.rows/3), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,0,0),2);
        cv::putText(frame, "Difference: "+std::to_string(std::abs(line2-line1))+" px", cv::Point(frame.cols/2,frame.rows/2), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,0,0),2);

        cv::imshow(lineWindow, frame);
        if(cv::waitKey(20)==13){break;}//ENTER
    }

    cv::destroyWindow(lineWindow);
    return std::abs(line2-line1);
}

std::vector<checkpoint> getPoints(cv::Mat image){//function to get the points
    //display map
    const std::string mapWindow = "Rogaine Map";
    cv::namedWindow(mapWindow);
    cv::setMouseCallback(mapWindow, onMouse, &image);
    //add text to top of screen
    cv::Mat display = image.clone();
    std::string top = "Click Points, Type Label in Terminal, ESC when done";
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(top, cv::FONT_HERSHEY_SIMPLEX, 0.8, 2, &baseline);
    cv::putText(display, top, cv::Point((display.cols-textSize.width)/2,textSize.height+10), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 0), 2);
    cv::imshow(mapWindow, display);

    std::cout<<"\nClick on the map to mark the control points. Press ESC to exit."<<std::endl;
    std::cout<<"Please click the start location first."<<std::endl;
    while(true){if(cv::waitKey(20)==27){break;}}//ESC
    cv::destroyWindow(mapWindow);

    return points;
}

double pixToKilometres(double pixels,int scale){
    return pixels/scale;
}

void displayRoute(const cv::Mat image, const std::vector<checkpoint>& points, const std::vector<int>& visitedPath) {
    const std::string lineWindow = "Suggested Route";
    for(const auto& point:points){//draw points and labels
        cv::circle(image, cv::Point(point.getX(), point.getY()), 4, cv::Scalar(0,0,255), cv::FILLED);
        cv::putText(image, std::to_string(point.getID()), cv::Point(point.getX()+5, point.getY()-5), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(139, 0, 0), 2);
    }
    
    for(size_t i=1;i<visitedPath.size();i++){//draw lines between points in order
        int index=visitedPath[i-1];
        int index1=visitedPath[i];
        cv::line(image, cv::Point(static_cast<int>(points[index].getX()), static_cast<int>(points[index].getY())), 
        cv::Point(static_cast<int>(points[index1].getX()), static_cast<int>(points[index1].getY())),cv::Scalar(128, 0, 128), 2, cv::LINE_AA);

    }

    cv::imshow(lineWindow, image);//show window and close with any key
    std::cout<<"Press any key to close the map"<<std::endl;
    cv::waitKey(0);
    cv::destroyWindow(lineWindow);
}
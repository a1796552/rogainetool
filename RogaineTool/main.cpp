#include "routePlanner.h"
#include "interactive.h"

int main() {

    std::cout<<"Welcome to the Rogaine Route Planner Tool!"<<std::endl;
    std::cout<<"The purpose of this tool is to help plan an optimal route for a rogaine"<<std::endl;
    std::cout<<"based upon a photo of the map and the control points selected by you. The steps are as follows: "<<std::endl<<std::endl;
    std::cout<<"1. Input the name of the file including the filetype (e.g. mountcrawford.png)"<<std::endl<<std::endl;
    std::cout<<"2. Input how far you would like to travel in kilometres (e.g. 12, 30, 75)."<<std::endl<<std::endl;
    std::cout<<"3. Select the scale of the map by placing two vertical lines 1km apart."<<std::endl<<std::endl;
    std::cout<<"4. Select all the control points on the map or at least the points you are interested in starting with the START TRIANGLE."<<std::endl<<std::endl;
    std::cout<<"5. The program will then output the optimal route to take and display it on the map."<<std::endl<<std::endl;

    cv::Mat image;
    std::string filename = "";
    while(true){
        std::cout<<"Please enter the map file name including the extension: ";
        std::cin>>filename;
        image = cv::imread(filename);
        if(image.empty()){
            std::cout<<"Not a valid file name"<<std::endl;
        }else{
            break;
        }
    }

    int distance = 0;
    while(true){
        std::cout<<"Please enter the distance you wish to travel in km: ";
        std::cin>>distance;
        if(distance>0){
            break;
        }else{
            std::cout<<"Please enter a valid positive integer."<<std::endl;
        }
    }

    int scale=getScale(image);
    distance*=scale;
    std::vector<checkpoint> points=getPoints(image);

    routePlanner newMap(points, distance);
    auto greedy = newMap.greedyRoute();

    int prev = -1;
    std::cout<<"\n\nThe most efficient route is from the start: "<<std::endl;
    for (int id : greedy.visitedPath){
        if(prev==-1){
        }else{
            std::cout<< "Control: "<<points[id].getID();
            double dx = points[id].getX()-points[prev].getX();
            double dy = points[id].getY()-points[prev].getY();
            double dist = std::sqrt(dx*dx+dy*dy);
            std::cout << ". Distance from previous: "<<std::fixed<<std::setprecision(1)<<pixToKilometres(dist, scale)*1000 << " metres"<<std::endl;
        }
        prev = id;
    }
    std::cout<<"\nTotal Distance: "<<std::fixed<<std::setprecision(3)<<pixToKilometres(greedy.totalDistance,scale)<<" kilometres"<<std::endl;
    std::cout<<"Total Points: "<<greedy.totalPoints<<std::endl<<std::endl;

    displayRoute(image, points, greedy.visitedPath);
    return 0;
}
#include <iostream>

#include "Pathfinder.h"
#include "Point.h"

#include "algo_trajectoire/info_algo.h"
#include "algo_trajectoire/points_trajectoire.h"
#include "algo_trajectoire/point.h"
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

using namespace std;

Pathfinder* path;
vector<pair<int,int>*> trajectoire;
ros::Publisher points_Trajectoire_pub;
void trouverTrajectoire(const algo_trajectoire::info_algo& msg);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "trajectoire");
    ros::NodeHandle n;
    path=new Pathfinder();
    points_Trajectoire_pub = n.advertise<algo_trajectoire::points_trajectoire>("pointDeTrajectoire", 100);
    ros::Subscriber info_algo_sub = n.subscribe("info_A*", 100, trouverTrajectoire);
    ros::spin();
    return 0;
}

void trouverTrajectoire(const algo_trajectoire::info_algo& msg)
{
    trajectoire=path->aStar(msg.x_dep,msg.y_dep,msg.x_dest,msg.y_dest,msg.angle);
    algo_trajectoire::points_trajectoire result;
    algo_trajectoire::point pointCourant;
    for(unsigned int i=0; i<trajectoire.size(); ++i)
    {
       pair<int,int>* ppoint= trajectoire[i];
       pointCourant.x=ppoint->first;
       pointCourant.y=ppoint->second;
       result.points_trajectoire.push_back(pointCourant);
    }

    points_Trajectoire_pub.publish(result);
}

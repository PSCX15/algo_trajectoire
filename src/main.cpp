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
    ros::Rate loop_rate(10);
    int count = 0;
    while (ros::ok())
    {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    //chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;

    }

    return 0;
}

void trouverTrajectoire(const algo_trajectoire::info_algo& msg)
{
    trajectoire=path->aStar(msg.x_dep,msg.y_dep,msg.x_dest,msg.y_dest,msg.angle);
}

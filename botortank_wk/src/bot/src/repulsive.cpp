#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double forceX = 0;
double forceY = 0;
double deltaX = 0;
double deltaY = 0;
double dist_opp1 = 0;
double dist_opp2 = 0;
double dist_wall1 = 0;
double dist_wall2 = 0;
double dist_wall3 = 0;
double angle_opp1 = 0;
double angle_opp2 = 0;
double angle_wall1 = 0;
double angle_wall2 = 0;
double angle_wall3 = 0;
double force_repX = 0;
double force_repY = 0;

double angle = 0;
double eta = 1;

void Callback1(const bot::quad& opp)
{
	dist_opp1 = opp.motor1;
    dist_opp2 = opp.motor2;
    angle_opp1 = opp.motor3;
	angle_opp2 = opp.motor4;
}
void Callback2(const geometry_msgs::Twist& wall)
{
	dist_wall1 = wall.linear.x;
    dist_wall2 = wall.linear.y;
    dist_wall3 = wall.linear.z;
    angle_wall1 = wall.angular.x;
    angle_wall2 = wall.angular.y;
    angle_wall3 = wall.angular.z;
}
void forcerep() // ne pas eviter les murs tout le temps !!!!
{
	force_repX = eta*dist_opp1*cos(angle_opp1) + eta*dist_opp2*cos(angle_opp1);
	force_repY = eta*dist_opp2*sin(angle_opp2) + eta*dist_opp2*sin(angle_opp2);
	
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "repulsive");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("opponent", 10, Callback1);
	ros::Subscriber sub2 = n.subscribe("nearest_wall", 10, Callback2);
    ros::Publisher pub = n.advertise<geometry_msgs::Point>("force_rep",10);
    ros::Rate loop_rate(100);
	
    geometry_msgs::Point force;
	
    while(ros::ok())
    {
        forcerep();
        force.x = force_repX;
		force.y = force_repY;
        pub.publish(force);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

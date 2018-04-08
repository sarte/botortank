#include "ros/ros.h"
#include "std_msgs/Int8.h"
//#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double forceX = 0;
double forceY = 0;
double deltaX = 0;
double deltaY = 0;
double dist_opp = 0;
double dist_wall = 0;
double theta_opp = 0;
double theta_wall = 0;

double angle = 0;
double eta = 1;

void Callback1(const bot::opp& opponent)
{
	dist_opp = opp.dist;
	theta_opp = opp.theta;
}
void Callback2(const bot::wall& nearest_wall)
{
	dist_wall = wall.dist;
	theta_wall = wall.theta;
}
void forcerep() // ne pas eviter les murs tout le temps !!!!
{
	cvs->force_repX = eta*dist_opp*cos(theta_opp) + eta*dist_wall*cos(theta_wall);
	cvs->force_repY = eta*dist_opp*sin(theta_opp) + eta*dist_wall*sin(theta_wall);
	
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_rep");
    ros::NodeHandle n;
    ros::Subscriber sub2 = n.subscribe("opponent", 10, Callback1);
	ros::Subscriber sub2 = n.subscribe("nearest_wall", 10, Callback2);
	
    ros::Publisher pub = n.advertise<bot::Force>("force_rep",10);
	
    ros::Rate loop_rate(100);
	
    bot::Force force;
	
    while(ros::ok())
    {
        forcerep();
        force.forcex = cvs->force_repX;
		force.forcey = cvs->force_repY;
        pub.publish(force_rep);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

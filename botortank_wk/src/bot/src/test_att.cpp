#include "ros/ros.h"
#include "std_msgs/Int8.h"
//#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double forceX = 0;
double forceY = 0;
double number1 =0;
double number2 = 0;
double X =0;
double Y = 0;
double theta = 0; // angle robot in ref frame
double deltaX = 0;
double deltaY = 0;
double dist = 0;
double angle = 0; // angle force in ref frame
double xsi = 10;



void Callback1(const bot::pose& localisation_odom)
{
	X = localisation_odom.x;
	Y = localisation_odom.y;
	theta = localisation_odom.theta;
}
void Callback2(const bot::coord& target)
{
	number1 = target.x;
	number2 = target.y;
}
void forceatt()
{
    deltaX = number1 - X;
	deltaY = number2 - Y;
	
	dist = sqrt(deltaX*deltaX + deltaY*deltaY);
	angle = atan(deltaY/deltaX);
	
	if(deltaX<0 && deltaY>0 && angle<0)
	{
		angle += M_PI;
	}
	if(deltaX<0 && deltaY<0 && angle>0)
	{
		angle -= M_PI;
	}
	
	forceX = xsi*dist*cos(angle-theta);
	forceY = xsi*dist*sin(angle-theta);
	
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_att");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("localisation_odom", 10, Callback1);
    ros::Subscriber sub2 = n.subscribe("target", 10, Callback2);
    ros::Publisher pub = n.advertise<bot::Force>("force_att",1);
    ros::Rate loop_rate(100);
    bot::Force force;
	
    while(ros::ok())
    {
        forceatt();
        force.forcex = cvs->forceX;
		force.forcey = cvs->forceY;
        pub.publish(force);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

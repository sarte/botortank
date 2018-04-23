#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double forceX = 0;
double forceY = 0;
double number1 =0;
double number2 = 0;
double Xg =0;
double Yg = 0;
double thetag = 0; // angle robot in ref frame
double Xo =0;
double Yo = 0;
double thetao = 0; // angle robot in ref frame
double deltaX = 0;
double deltaY = 0;
double dist = 0;
double angle = 0; // angle force in ref frame
double xsi = 5;
bool team;
double X = 0;
double Y = 0;
double theta = 0;

void Callbackgreen(const geometry_msgs::Pose2D& green)
{
	Xg = green.x;
	Yg = green.y;
	thetag = green.theta;
}
void Callbackorange(const geometry_msgs::Pose2D& orange)
{
    Xo = orange.x;
    Yo = orange.y;
    thetao = orange.theta;
}
void Callback2(const geometry_msgs::Pose2D& target)
{
	number1 = target.x;
	number2 = target.y;
}
void Callbackteam(const std_msgs::Bool& teamdata)
{
    team = teamdata.data;
}
void forceatt()
{
    if(team){
        X = Xo;
        Y = Yo;
        theta = thetao*M_PI/180;
    }
    else {
        X = Xg;
        Y = Yg;
        theta = thetag*M_PI/180;
    }
    deltaX = number1 - X;
	deltaY = number2 - Y;
    printf("deltaX = %f deltaY = %f",deltaX,deltaY);
	dist = sqrt((deltaX*deltaX) + (deltaY*deltaY));
    angle = atan2(deltaY,deltaX); //quadrant finder
    printf("distance = %f angle = %f\n",dist,angle*180/M_PI);
	forceX = -xsi*dist*cos(angle-theta);
	forceY = -xsi*dist*sin(angle-theta);
	forceX = std::min(std::max(forceX, -10.0), 10.0); //saturation
	forceY = std::min(std::max(forceY, -10.0), 10.0); //saturation
	
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "attraction");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("origin_green", 1, Callbackgreen);
    ros::Subscriber sub3 = n.subscribe("origin_orange", 1, Callbackorange);
    ros::Subscriber sub4 = n.subscribe("team", 1, Callbackteam);
    ros::Subscriber sub2 = n.subscribe("target", 10, Callback2);
    ros::Publisher pub = n.advertise<geometry_msgs::Point>("force_att",1);
    ros::Rate loop_rate(500);
    geometry_msgs::Point force;
	
    while(ros::ok())
    {
        forceatt();
        force.x = forceX;
		force.y = forceY;
        pub.publish(force);
        ros::spinOnce();
        loop_rate.sleep();
    }


   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

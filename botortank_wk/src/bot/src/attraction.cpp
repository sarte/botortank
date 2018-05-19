#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Pose2D.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double forceX = 0;
double forceY = 0;
double tar_x =0;
double tar_y = 0;
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
double xsi = 0;
bool team;
double X = 0;
double Y = 0;
double theta = 0;
double Xslam = 0;
double Yslam = 0;
double thetaslam = 0;

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
void Callbackslam(const geometry_msgs::Pose2D& slam_out)
{
	Xslam = slam_out.x;
    Yslam = slam_out.y;
	thetaslam = slam_out.theta * M_PI / 180;
	// printf("thetaslam:%f\n", thetaslam* 180 /M_PI);
}
void Callback2(const geometry_msgs::Pose2D& target)
{
	tar_x = target.x;
	tar_y = target.y;
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

    // X = Xslam;
    // Y = Yslam;
    // theta = thetaslam*M_PI/180;
    deltaX = tar_x - X;
	deltaY = tar_y - Y;
//    printf("deltaX = %f deltaY = %f",deltaX,deltaY);
	dist = sqrt((deltaX*deltaX) + (deltaY*deltaY));
    angle = atan2(deltaY,deltaX); //quadrant finder
    // printf("angle: %f\n", angle* 180 /M_PI);
//    printf("distance = %f angle = %f\n",dist,angle*180/M_PI);
	forceX = -xsi*dist*cos(angle-theta);
	forceY = -xsi*dist*sin(angle-theta);
	forceX = std::min(std::max(forceX, -10.0), 10.0); //saturation
	forceY = std::min(std::max(forceY, -10.0), 10.0); //saturation
	
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "attraction");
//    double xsi = 5;
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Pose2D>("force_att",1);
    ros::Subscriber sub1 = n.subscribe("origin_green", 1, Callbackgreen);
    ros::Subscriber sub3 = n.subscribe("origin_orange", 1, Callbackorange);
    ros::Subscriber sub5 = n.subscribe("slam_out", 1, Callbackslam);
    ros::Subscriber sub4 = n.subscribe("team", 1, Callbackteam);
    ros::Subscriber sub2 = n.subscribe("target", 10, Callback2);
    ros::Rate loop_rate(100);
    geometry_msgs::Pose2D force;

    ros::NodeHandle nh_private("~");
    nh_private.param<double>("xsi", xsi, 5);
    printf("attraction xsi: %f\n",xsi);
    printf("TEAM: disabled\n");

    while(ros::ok())
    {
        forceatt();
        force.x = forceX;
		force.y = forceY;
        force.theta = (angle + theta) * 180 /M_PI;
        pub.publish(force);
        // ROS_INFO("attraction x:%f  y:%f  theta2:%f  \n", force.x, force.y, force.theta);
        ROS_INFO("attraction x:%f  y:%f \n", force.x, force.y);
        ros::spinOnce();
        loop_rate.sleep();
    }


   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

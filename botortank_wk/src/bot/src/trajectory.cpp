#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



double force_att_X = 0;
double force_att_Y = 0;
double force_rep_X = 0;
double force_rep_Y = 0;
int enable_move;
double ftotX =0;
double ftotY = 0;
double velocityX = 0;
double velocityY = 0;

double katt = 0;
double krep = 0;


// double X =0;
// double Y = 0;
// double theta = 0; // angle robot in ref frame
// double deltaX = 0;
// double deltaY = 0;
// double dist = 0;
// double angle = 0; // angle force in ref frame
// double xsi = 10;

void Callback1(const geometry_msgs::Pose2D& fatt)
{
	force_att_X = fatt.x;
	force_att_Y = fatt.y;
}
void Callback2(const geometry_msgs::Point& frep)
{
	force_rep_X = frep.x;
	force_rep_Y = frep.y;
}
//void Callback3(const std_msgs::Int8& mvt)
//{
//	enable_move = mvt.data;
//}

void trajectory()
{
		
		ftotX = katt*force_att_X + krep*force_rep_X;
		ftotY = katt*force_att_Y + krep*force_rep_Y;

        velocityX = std::min(std::max(ftotX, -10.0), 10.0); //saturation
        velocityY = std::min(std::max(ftotY, -10.0), 10.0); //saturation
	
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "trajectory");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("force_att", 10, Callback1);
    ros::Subscriber sub2 = n.subscribe("force_rep", 10, Callback2);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("velocity_ref",1);
    ros::Rate loop_rate(100);

    ros::NodeHandle nh_private("~");
    nh_private.param<double>("katt", katt, 1);
    nh_private.param<double>("krep", krep, 1);

    printf("trajectory att coeff: %f\n", katt);
    printf("trajectory rep coeff: %f\n", krep);
	
    geometry_msgs::Twist velocity_ref;
	
    while(ros::ok())
    {
        trajectory();
        velocity_ref.linear.x = velocityX;
		velocity_ref.linear.y = velocityY;
        pub.publish(velocity_ref);
        ROS_INFO("trajectory x: %f y: %f \n", velocity_ref.linear.x, velocity_ref.linear.y);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

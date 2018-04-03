#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structure.h"

int main(int argc, char **argv)
{
	Struct *cvs;
	ros::init(argc, argv, "compteur");
	ros::NodeHandle n;
	ros::Publisher counter_pub = n.advertise<std_msgs::Int8>("counter",10);
	ros:: Rate loop_rate(1);

	while(ros::ok())
	{
		std_msgs::Int8 msg;
		msg.data = cvs->count;
		//ROS_INFO("%i",msg.data);
        //printf("%i",msg.data);
		counter_pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		cvs->count = cvs->count + 1;
	}
}

#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double number1 = 0;
double number2 = 0;
double result = 0;

void Callback1(const std_msgs::Int8& data1)
{
	number1 = data1.data;
}
void Callback2(const std_msgs::Int8& data2)
{
	number2 = data2.data;
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "essaidouble");
  ros::NodeHandle n1;
  ros::NodeHandle n2;
  ros::Subscriber sub1 = n1.subscribe("data1", 1000, Callback1);
  ros::Subscriber sub2 = n2.subscribe("data2", 1000, Callback2); // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
  ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

  return 0;
}

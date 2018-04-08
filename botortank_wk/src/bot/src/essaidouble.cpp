#include "ros/ros.h"
#include "std_msgs/Int8.h"
//#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int number1 = 0;
int number2 = 0;
int result = 0;

void Callback1(const std_msgs::Int8& data1)
{
	number1 = data1.data;
}
void Callback2(const std_msgs::Int8& data2)
{
	number2 = data2.data;
}
void sum()
{
    result = number1 + number2;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "essaidouble");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("data1", 10, Callback1);
    ros::Subscriber sub2 = n.subscribe("data2", 10, Callback2);
    ros::Publisher pub = n.advertise<std_msgs::Int8>("result",10);
    ros::Rate loop_rate(1);
    std_msgs::Int8 resultat;
    while(ros::ok())
    {
        sum();
        resultat.data = result;
        pub.publish(resultat);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

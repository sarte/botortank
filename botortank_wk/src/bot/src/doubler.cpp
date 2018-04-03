#include "ros/ros.h"
#include "std_msgs/String.h"
#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "CtrlStruct_gr5.h"


int main(int argc, char **argv) {
    ros::init(argc, argv, "foonode");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<bot::quad>("pub1", 1000);
    ros::Rate loop_rate(1);

    while (ros::ok())
    {

        ros::Subscriber sub = n.subscribe("sub1", 100);
//        ros::Subscriber sub = n.subscribe("sub2", 100);
        bot::quad pub1;
        chatter_pub.publish(pub1); //here is the actual broadcast
        ros::spinOnce(); //important to call the callbacks
        loop_rate.sleep(); //puts node tu sleep to complete the 10Hz cycle

    }

    ros::spin(); //enters a loop calling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}
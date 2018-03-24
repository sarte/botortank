
#include "ros/ros.h" //include headers to use in most ros system
#include "std_msgs/String.h" //includes the std_msgs/String message from the std_msgs package

#include <sstream>

int main (int argc, char **argv)
{
        ros::init(argc, argv, "talker"); //allows ros to do name remapping
        ros::NodeHandle n; //this will actually do the initialization of node, and will be the last d$
        ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000); //tell master we$
        ros::Rate loop_rate(10); //set the freq at 10 Hz

        int count = 0; //initialize counter at 0
        while (ros::ok()) //ok() returns false when ctfl-C, or other node kicks it out, or all nodes $
        {
                //We broadcast a message on ROS using a message-adapted class
                std_msgs::String msg;
                std::stringstream ss;
                ss <<"get shwifty"<<count;
                msg.data = ss.str();
                ROS_INFO("%s",msg.data.c_str()); //the ros equivalent to printf
                chatter_pub.publish(msg); //here is the actual broadcast
                ros::spinOnce(); //important to call the callbacks
                loop_rate.sleep(); //puts node tu sleep to complete the 10Hz cycle
                ++count; //increase the count
        }
        return 0;
}

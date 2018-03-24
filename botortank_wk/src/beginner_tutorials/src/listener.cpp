#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg) //callback function is called anytime a new msgs arrives. Msg is passsed in a boost shared_ptr, we can store it if we want without worrying about it getting deleted
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback); // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
  ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

  return 0;
}

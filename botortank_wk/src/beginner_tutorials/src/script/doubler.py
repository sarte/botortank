#!/usr/bin/env python


import rospy
from std_msgs.msg import Int32
from bot.msg import quad


def callback(msg):
    pub = rospy.Publisher('doubled', quad, queue_size=1)
#    doubled = Int32()
    doubled.data = msg.data * 2
    pub.publish(doubled)
    rospy.loginfo(doubled)
    print(doubled)


def doubler():
    rospy.init_node('doubler', anonymous=True)
    rospy.Subscriber('number', quad, callback)
    rospy.spin()


if __name__ == '__main__':
    doubler()
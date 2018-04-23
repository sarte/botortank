#!/usr/bin/env python


import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist
from bot.msg import *

def callback(joy_cmd):
    pub = rospy.Publisher('velocity_ref', Twist, queue_size=1)
    rate = rospy.Rate(1000)
    while not rospy.is_shutdown():
        vel_cmd = Twist()
        joy_cmd.axes.1 = vel_cmd.linear.x
        pub.publish(vel_cmd)
        # pub.publish(vel)
        rate.sleep()


def joy2twist():
    rospy.init_node('joy2twist', anonymous=True)  # "doubler" node creation
    rospy.Subscriber('joy', Joy, callback)  # "/number" topic subscription --> into callback function
    rospy.spin()


if __name__ == '__main__':
    try:
        joy2twist()
    except rospy.ROSInterruptException:
        pass
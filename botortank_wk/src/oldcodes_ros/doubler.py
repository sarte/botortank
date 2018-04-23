#!/usr/bin/env python


import rospy
from std_msgs.msg import Int32
from bot.msg import *


def callback(msg):
    pub = rospy.Publisher('doubled', quad, queue_size=1)  # "/doubled" topic creation
    doublede = quad()
    doublede.motor1 = msg.motor4
    doublede.motor2 = msg.motor3
    doublede.motor3 = msg.motor2
    doublede.motor4 = msg.motor1
    pub.publish(doublede)
#    rospy.loginfo(doubled)
    print(doublede)


def doubler():
    rospy.init_node('doubler', anonymous=True)  # "doubler" node creation
    rospy.Subscriber('number', quad, callback)  # "/number" topic subscription --> into callback function
    rospy.spin()


if __name__ == '__main__':
    try:
        doubler()
    except rospy.ROSInterruptException:
        pass
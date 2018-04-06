#!/usr/bin/env python


import rospy
import time
from time import sleep
from ctypes import c_double
from math import *
from math import pi
from std_msgs.msg import String
# from geometry_msgs.msg import Twist
from bot.msg import *


def testJordan():
    pub = rospy.Publisher('omega_cmd',quad,queue_size = 10)
    rospy.init_node('testJordan', anonymous=True)
    rate = rospy.Rate(100)
    command = quad()
    count = 0
    while not rospy.is_shutdown():
        if count < 1000:
            command.motor1 = 10
            command.motor2 = 10
            command.motor3 = 10
            command.motor4 = 10
        else:
            command.motor1 = 20
            command.motor2 = 20
            command.motor3 = 20
            command.motor4 = 20

        count += 1
        print(count)
        pub.publish(command)
        rate.sleep()


if __name__ == '__main__':
    try:
        testJordan()
    except rospy.ROSInterruptException:
        pass 


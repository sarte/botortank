#!/usr/bin/env python


import rospy
import time
from time import sleep
from math import sqrt
from geometry_msgs.msg import Twist
from bot.msg import *


def norm(a,b):
    return sqrt((a * a) + (b * b))


def callback(cmd):
    vel_x = cmd.linear.x
    vel_y = cmd.linear.y
    # rot_z = cmd.angular.z
    pub = rospy.Publisher('omega_ref', quad, queue_size=10)
    omega_ref = quad()
    vel_norm = norm(vel_x, vel_y)
    omega_ref.motor1 = ((vel_x + vel_y) / vel_norm)  # + rot_z
    omega_ref.motor2 = ((vel_x - vel_y) / vel_norm)  # + rot_z
    omega_ref.motor3 = ((vel_x + vel_y) / vel_norm)  # - rot_z
    omega_ref.motor4 = ((vel_x - vel_y) / vel_norm) # - rot_z
    pub.publish(omega_ref)
    print(omega_ref)


def midlevel():
    rospy.init_node('midlevel', anonymous=True)
    rospy.Subscriber('velocity_ref', Twist, callback)
    rospy.spin()


if __name__ == '__main__':
    try:
        midlevel()
    except rospy.ROSInterruptException:
        pass
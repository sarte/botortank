#!/usr/bin/env python


import rospy
# import tf
import time
from time import sleep
from geometry_msgs.msg import Pose2D
from geometry_msgs.msg import PoseStamped
import math
import numpy as np
from numpy.linalg import inv


def quaternion_to_euler_angle(w, x, y, z):
    ysqr = y * y
    t0 = +2.0 * (w * x + y * z)
    t1 = +1.0 - 2.0 * (x * x + ysqr)
    X = math.degrees(math.atan2(t0, t1))
    t2 = +2.0 * (w * y - z * x)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    Y = math.degrees(math.asin(t2))
    t3 = +2.0 * (w * z + x * y)
    t4 = +1.0 - 2.0 * (ysqr + z * z)
    Z = math.degrees(math.atan2(t3, t4))
    return X, Y, Z


def green(pose):
    a = -1.3
    b = 1.8
    c = -90
    bot_pose_green = Pose2D()
    bot_pose_green.x = pose.x + a
    bot_pose_green.y = pose.y + b
    bot_pose_green.theta = pose.theta + c
    pubg = rospy.Publisher('origin_green', Pose2D, queue_size=1)
    pubg.publish(bot_pose_green)
     

def orange(pose):
    a = 1.3
    b = 1.8
    c = 90
    bot_pose_orange = Pose2D()
    bot_pose_orange.x = pose.x + a
    bot_pose_orange.y = pose.y + b
    bot_pose_orange.theta = pose.theta + c
    pubo = rospy.Publisher('origin_orange', Pose2D, queue_size=1)
    pubo.publish(bot_pose_orange)
    rospy.loginfo(pubo)


def callback(cmd):
    # pub = rospy.Publisher('origin_frame', Pose2D, queue_size=1)
    out = Pose2D()
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        out.x = cmd.pose.position.x
        out.y = cmd.pose.position.y
        (a, b, c) = quaternion_to_euler_angle(cmd.pose.orientation.w, cmd.pose.orientation.x, cmd.pose.orientation.y, cmd.pose.orientation.z)
        out.theta = c
        # print(a, b, c)
        # pub.publish(out)
        # rospy.loginfo(out)
        green(out)
        orange(out)
        # rate.sleep()
        

def referenceframe():
    rospy.init_node('referenceframe')
    rospy.Subscriber('slam_out_pose', PoseStamped, callback)
    rospy.spin()


if __name__ == '__main__':
    try:
        referenceframe()
    except rospy.ROSInterruptException:
        pass

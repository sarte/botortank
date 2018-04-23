#!/usr/bin/env python


# import roslib
import rospy
import tf
import time
from time import sleep
import math
from geometry_msgs.msg import Pose2D
from tf.transformations import euler_from_quaternion, quaternion_from_euler


def set_origin(trans, rot, origin):
    finalpose = Pose2D
    finalpose.x = trans.x - origin.x
    finalpose.y = trans.y - origin.y
    roll = pitch = yaw = 0.0
    (roll, pitch, yaw) = euler_from_quaternion(rot)
    finalpose.theta = yaw


def callback():


if __name__ == '__main__':
    rospy.init_node('hector2useful')
    listener = tf.TransformListener()
    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            (trans,rot) = listener.lookupTransform('base_link', 'map', rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue

        # angular = 4 * math.atan2(trans[1], trans[0])
        # linear = 0.5 * math.sqrt(trans[0] ** 2 + trans[1] ** 2)
        # cmd = geometry_msgs.msg.Twist()
        # cmd.linear.x = linear
        # cmd.angular.z = angular
        # turtle_vel.publish(cmd)

        rate.sleep()

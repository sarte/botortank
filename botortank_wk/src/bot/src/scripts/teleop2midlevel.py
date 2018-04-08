#!/usr/bin/env python


import rospy
from geometry_msgs.msg import Twist

def callback(msg):
    pub = rospy.Publisher('velocity_ref', Twist, queue_size=1)
    newvel = Twist()
    reductionratio = 0.2
    newvel.linear.x = reductionratio * 100 * msg.linear.x
    newvel.linear.y = reductionratio * 100 * msg.linear.y
    newvel.linear.z = reductionratio * 100 * msg.linear.z
    newvel.angular.x = reductionratio * 100 * msg.angular.x
    newvel.angular.y = reductionratio * 100 * msg.angular.y
    newvel.angular.z = reductionratio * 100 * msg.angular.z
    pub.publish(newvel)


def teleop2midlevel():
    rospy.init_node('teleop2midlevel', anonymous=True)
    rospy.Subscriber('cmd_vel', Twist, callback)
    rospy.spin()


if __name__ == '__main__':
    try:
        teleop2midlevel()
    except rospy.ROSInterruptException:
        pass

#!/usr/bin/env python


import rospy
from std_msgs.msg import Int32


def callback(param):
    if param[1] | param[2]:
        a = param[1]
        b = param[2]
    else:
        a = 0
        b = 1
    pub = rospy.Publisher('result', Int32, queue_size=10)
    timed = Int32()
    timed.data = a * b
    pub.publish(timed)
    rospy.loginfo(timed)
    print(param1, param2, timed)


def times():
    rospy.init_node('doubler', anonymous=True)
    param1 = rospy.Subscriber('number1', Int32, callback)
    param2 = rospy.Subscriber('number2', Int32, callback)
    param = [param1, param2]
    rospy.spin()


if __name__ == '__main__':
    times()
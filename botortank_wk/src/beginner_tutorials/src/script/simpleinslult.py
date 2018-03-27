#!/usr/bin/env python


import rospy
from std_msgs.msg import String


def callback(data):
	rospy.loginfo(rospy.get_caller_id() + "Fucking %s", data.data)
	
def simpleinsult():
	rospy.init_node('simpleinsult', anonymous=True)
	rospy.Subscriber("chatter", String, callback)
	rospy.spin()
	
if __name__ == '__main__':
	simpleinsult()
#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String #import string from std_msgs to publish

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        shwifty_str = "get shwifty in python %s" % rospy.get_time()
        rospy.loginfo(shwifty_str)
        pub.publish(shwifty_str)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass

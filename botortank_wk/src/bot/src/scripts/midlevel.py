#!/usr/bin/env python


import rospy
import time
from time import sleep
from math import sqrt
from geometry_msgs.msg import *
from std_msgs.msg import *
from bot.msg import *

vel_x = 0
vel_y = 0
rot_z = 0
move=0
rotation=0

def norm(a,b):
    # if a * b != 0:
    #     return sqrt((a * a) + (b * b))
    # else:
        return 1


def callback(cmd):
    global vel_x
    global vel_y
    global rot_z
    vel_x = cmd.linear.x
    vel_y = cmd.linear.y
    rot_z = cmd.angular.z

def callback_move(cmd):
    global move
    move=cmd.data

def callback_rotation(cmd):
    global rotation
    rotation=cmd.data

def midlevel():
    rospy.init_node('midlevel', anonymous=True)
    rospy.Subscriber('velocity_ref', Twist, callback)
    rospy.Subscriber('move',Int8,callback_move)
    rospy.Subscriber('enable_rotation',Int8,callback_rotation)
    pub = rospy.Publisher('omega_ref', quad, queue_size=1)
    omega_ref = quad()
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        print(move)
        if(move == 0):
            omega_ref.motor1 = 0
            omega_ref.motor2 = 0
            omega_ref.motor3 = 0
            omega_ref.motor4 = 0
        elif(move == 1):
            vel_norm = norm(vel_x, vel_y)
            omega_ref.motor1 = ((vel_x + vel_y) / vel_norm) + rot_z
            omega_ref.motor2 = ((vel_x - vel_y) / vel_norm) + rot_z
            omega_ref.motor3 = ((vel_x + vel_y) / vel_norm) - rot_z
            omega_ref.motor4 = ((vel_x - vel_y) / vel_norm) - rot_z
        elif(move==2):
            omega_ref.motor1 =  rotation*3
            omega_ref.motor2 =  rotation*3
            omega_ref.motor3 =  -rotation*3
            omega_ref.motor4 =  -rotation*3
        elif (move==3):
            omega_ref.motor1 =  6
            omega_ref.motor2 =  6
            omega_ref.motor3 =  6
            omega_ref.motor4 =  6
        elif(move==4):
            omega_ref.motor1 =  -6
            omega_ref.motor2 =  -6
            omega_ref.motor3 =  -6
            omega_ref.motor4 =  -6
        elif(move==5):#gauche
            omega_ref.motor1 =  6
            omega_ref.motor2 =  -6
            omega_ref.motor3 =  6
            omega_ref.motor4 =  -6
        elif(move==6):#droite
            omega_ref.motor1 =  -6
            omega_ref.motor2 =  6
            omega_ref.motor3 =  -6
            omega_ref.motor4 =  6
        elif(move==7):#2vers4
            omega_ref.motor1 =  6
            omega_ref.motor2 =  0
            omega_ref.motor3 =  6
            omega_ref.motor4 =  0
        elif(move==8):#1vers3
            omega_ref.motor1 =  0
            omega_ref.motor2 =  -6
            omega_ref.motor3 =  0
            omega_ref.motor4 =  -6
        elif(move==9):#3vers1
            omega_ref.motor1 =  0
            omega_ref.motor2 =  6
            omega_ref.motor3 =  0
            omega_ref.motor4 =  6
        elif(move==10):#4vers2
            omega_ref.motor1 =  -6
            omega_ref.motor2 =  0
            omega_ref.motor3 =  -6
            omega_ref.motor4 =  0
        elif(move==11):#domo
            omega_ref.motor1 =  -4
            omega_ref.motor2 =  -4
            omega_ref.motor3 =  -4
            omega_ref.motor4 =  -4
        elif(move==12):#domo
            omega_ref.motor1 = 4
            omega_ref.motor2 = 4
            omega_ref.motor3 = 4
            omega_ref.motor4 = 4

        pub.publish(omega_ref)
        rate.sleep()
        rospy.loginfo("omega motor 1 %s", omega_ref.motor1)
        rospy.loginfo("omega motor 2 %s", omega_ref.motor2)
        rospy.loginfo("omega motor 3 %s", omega_ref.motor3)
        rospy.loginfo("omega motor 4 %s", omega_ref.motor4)

    # rospy.Subscriber('cmd_vel', Twist, callback)
    rospy.spin()


if __name__ == '__main__':
    try:
        midlevel()
    except rospy.ROSInterruptException:
        pass

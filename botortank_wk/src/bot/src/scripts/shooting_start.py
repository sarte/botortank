#!/usr/bin/env python


import rospy
import RPi.GPIO as GPIO
import spidev
import MyMCP2515
import time
from time import sleep
from ctypes import c_double
from std_msgs.msg import *

CAN = MyMCP2515.MCP2515()
MyARM_ResetPin = 19  # Pin 4 of connector = BCM19 = GPIO[1]

MySPI_FPGA = spidev.SpiDev()
MySPI_FPGA.open(0, 0)
MySPI_FPGA.max_speed_hz = 500000

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(MyARM_ResetPin, GPIO.OUT)

GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)

start = 0

def callback(enable):
    global start
    start = enable.data
    #rospy.loginfo(start)



def shooting_start():
    rospy.init_node('shooting', anonymous=True)
    rospy.Subscriber("shoot_enable", Int8, callback, queue_size=1)
    rate= rospy.Rate(10)
    while not rospy.is_shutdown():
        if start == 1:
            rospy.loginfo('Shooooot')
            ToSPI=[0xAA,0x00,0x00,0x00,0x01]
            FromSPI = MySPI_FPGA.xfer2(ToSPI)
        else:
             rospy.loginfo('Hold your fire')
             ToSPI=[0xAA,0x00,0x00,0x00,0x00]
             FromSPI = MySPI_FPGA.xfer2(ToSPI)
    rospy.spin()
    ToSPI=[0xAA,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

if __name__ == '__main__':
    try:
        shooting_start()
    except rospy.ROSInterruptException:
        pass

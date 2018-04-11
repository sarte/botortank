#!/usr/bin/env python


import rospy
import RPi.GPIO as GPIO
import spidev
import MyMCP2515
import time
from time import sleep
from ctypes import c_double
from math import *
from math import pi
from std_msgs.msg import String
# from geometry_msgs.msg import Twist
from bot.msg import *

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
start=1;

def callback(enable):
    global start;
    start=enable;


def shooting_start():
    rospy.init_node('shooting', anonymous=True)
    # rospy.Subscriber("omega_ref", String, callback)
    rospy.Subscriber("shoot_enable", Bool, callback, queue_size=1)
    rate= rospy.Rate(100)
    while not rospy.is_shutdown():
        ToSPI=[0xAA,0x00,0x00,0x00,enable]
        FromSPI = MySPI_FPGA.xfer2(ToSPI)
    rospy.spin()
    ToSPI=[0xAA,0x00,0x00,0x00,0x01]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

if __name__ == '__main__':
    try:
        driver()
    except rospy.ROSInterruptException:
        pass

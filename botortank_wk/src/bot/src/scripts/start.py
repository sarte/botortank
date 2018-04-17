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
from std_msgs.msg import *
# from geometry_msgs.msg import Twist
from bot.msg import *

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


def startrecup():
    ToSPI=[0x0f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    start=(FromSPI[1] & 0x80)>>7
    return start


def start():
    rospy.init_node('startrecup', anonymous=True)
    pub = rospy.Publisher('start', Bool, queue_size=10)
    rate = rospy.Rate(100)
    while not rospy.is_shutdown():
        start = startrecup()
        pub.publish(start)
        rate.sleep()


if __name__ == '__main__':
    try:
        start()
    except rospy.ROSInterruptException:
        pass

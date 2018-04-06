#!/usr/bin/env python


import rospy
import RPi.GPIO as GPIO
import spidev
import MyMCP2515
import time
from time import sleep
from math import *
from math import pi
from std_msgs.msg import String
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


# starting adc
def adc_start():
    ToSPI=[0x55,0x80,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)


# return the line follower values
def follow():
    sens = tetra()
    ToSPI = [0x8f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F34 = (FromSPI[1] & 0x0f)*256+FromSPI[2]
    # print(F34)
    F23 = (FromSPI[3] & 0x0f)*256+FromSPI[4]
    # print(F23)
    ToSPI = [0x9f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F12 = (FromSPI[1] & 0x0f)*256+FromSPI[2]
    # print(F12)
    F41 = (FromSPI[3] & 0x0f)*256+FromSPI[4]
    # print(F41)
    th = 1000
    sens.a = F12 > th
    sens.b = F23 > th
    sens.c = F34 > th
    sens.d = F41 > th
    return sens


def linesensor():
    pub = rospy.Publisher('blackline', tetra, queue_size=1)
    rospy.init_node('linesensor', anonymous=True)
    rate = rospy.Rate(1)
    line = tetra()
    adc_start()
    while not rospy.is_shutdown():
        # rospy.loginfo('nice and easy cowboy')
        line = follow()
        pub.publish(line)
        rate.sleep()


if __name__ == '__main__':
    try:
        linesensor()
    except rospy.ROSInterruptException:
        pass

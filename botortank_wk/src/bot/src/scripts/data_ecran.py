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
from std_msgs.msg import Int8
from std_msgs.msg import Bool


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

def get_data():
    int team
    int strategy
    ToSPI[0x0f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    team=FromSPI[4]
    strategy=FromSPI[3]
    return strategy,team


def data_ecran():
    pub1 = rospy.Publisher('team', Bool, queue_size=1)
    pub2 = rospy.Publisher('strategy',Int8,queue_size=1)
    rospy.init_node('data_ecran', anonymous=True)
    rate = rospy.Rate(100)
    while not rospy.is_shutdown():
        strategy,team = get_data()
        pub1.publish(team)
        pub2.publish(strategy)
        rate.sleep()



if __name__ == '__main__':
    try:
        data_ecran()
    except rospy.ROSInterruptException:
        pass





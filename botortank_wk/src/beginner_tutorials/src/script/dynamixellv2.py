#!/usr/bin/env python


import rospy
from std_msgs.msg import String

import RPi.GPIO as GPIO
import MyMCP2515
import spidev

# setup the SPI
MySPI_FPGA = spidev.SpiDev()
MySPI_FPGA.open(0,0)
MySPI_FPGA.max_speed_hz = 500000

# set the GPIO modes
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(MyARM_ResetPin, GPIO.OUT)

GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)

# det dynamixel ID
ID_tri=0x05
ID_bee=0x06
ID_ball=0x01
vit_tri=57

# enable dynamixel
def dynamixel_start(ID):
    instru_dyna(ID,0x05,0x03,0x18,0x01,0x01)
	
def # Message handler
def CommandCallback(commandMessage):
    command = commandMessage.data
	if command == 'enable dynamixel ball':
        print('Enabling ball')
        dynamixel_start(ID_ball)
    elif command == 'tri_1':
        print('enable dynamixel bee')
        tri_1()
    elif command == 'stop':
        print('Stopping')
        stop()
    else:
        print('Unknown command, stopping instead')
        stop()

rospy.init_node('dyna')

rospy.Subscriber('command', String, CommandCallback)

rospy.spin()
print('Shutting down: stopping motors')
stop()
GPIO.cleanup()
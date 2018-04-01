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
from geometry_msgs.msg import Twist


ADDRESS1 = 0x708  # identifiant pour envoyer des donnees
ADDRESS_RECEIVE1 = 0x700  # identifiant pour recevoir
ADDRESS2 = 0x408  # identifiant pour envoyer des donnees
ADDRESS_RECEIVE2 = 0x400  # identifiant pour recevoir
# duty cycle=0.5 so robot stay at rest
# DCL = 0.5
# DCR = 0.5
PRESCALE = 0x00
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


# motor initialization
def Motor_init():
        CAN.DoSendMsg(ADDRESS1, [0x23, 0xFF, 0xFF], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1, [0x24, 0xFF, 0xFF], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2, [0x23, 0xFF, 0xFF], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2, [0x24, 0xFF, 0xFF], 3, 0x00)
        sleep(0.01)
        TCON = 0x80 | PRESCALE
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1, [0x21, 0xFF, TCON], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1, [0x22, 0xFF, TCON], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2, [0x21, 0xFF, TCON], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2, [0x22, 0xFF, TCON], 3, 0x00)
        sleep(0.01)
        Motor_setDC1(0.5)
        sleep(0.01)
        Motor_setDC2(0.5)
        sleep(0.01)
        Motor_setDC3(0.5)
        sleep(0.01)
        Motor_setDC4(0.5)
        sleep(0.01)


# led ON, Frein OFF
def Motor_start():
        CAN.DoSendMsg(ADDRESS1, [0x1F, 0x40, 0x00], 3, 0x00)
        sleep(0.001)
        CAN.DoSendMsg(ADDRESS1, [0x1E, 0x70, 0x40], 3, 0x00)
        CAN.DoSendMsg(ADDRESS2, [0x1F, 0x40, 0x00], 3, 0x00)
        sleep(0.001)
        CAN.DoSendMsg(ADDRESS2, [0x1E, 0x70, 0x40], 3, 0x00)


# led OFF, Frein ON
def Motor_stop():
        Motor_setDC1(0)
        sleep(0.01)
        Motor_setDC2(0)
        sleep(0.01)
        Motor_setDC3(0)
        sleep(0.01)
        Motor_setDC4(0)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1, [0x1E, 0x70, 0x30], 3, 0x00)
        CAN.DoSendMsg(ADDRESS2, [0x1E, 0x70, 0x30], 3, 0x00)
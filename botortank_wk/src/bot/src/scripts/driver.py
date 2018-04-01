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
def motor_init():
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
#        motor_setDC1(0.5)
        sleep(0.01)
#        motor_setDC2(0.5)
        sleep(0.01)
#        motor_setDC3(0.5)
        sleep(0.01)
#        motor_setDC4(0.5)
        sleep(0.01)


# led ON, Frein OFF
def motor_start():
        CAN.DoSendMsg(ADDRESS1, [0x1F, 0x40, 0x00], 3, 0x00)
        sleep(0.001)
        CAN.DoSendMsg(ADDRESS1, [0x1E, 0x70, 0x40], 3, 0x00)
        CAN.DoSendMsg(ADDRESS2, [0x1F, 0x40, 0x00], 3, 0x00)
        sleep(0.001)
        CAN.DoSendMsg(ADDRESS2, [0x1E, 0x70, 0x40], 3, 0x00)


# led OFF, Frein ON
def motor_stop():
        motor_setDC1(0)
        sleep(0.01)
        motor_setDC2(0)
        sleep(0.01)
        motor_setDC3(0)
        sleep(0.01)
        motor_setDC4(0)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1, [0x1E, 0x70, 0x30], 3, 0x00)
        CAN.DoSendMsg(ADDRESS2, [0x1E, 0x70, 0x30], 3, 0x00)


# Duty Cycle Moteur 1, input de -100 a 100
def motor_setDC1(Duty):
        if Duty >= 100:
            DC10B = round(195 * 1023 / 200)
        elif Duty <= -100:
            DC10B = round(5 * 1023 / 200)
        else:
            DC10B = round((Duty * 0.9 + 100) * 1023 / 200)
        print('decimal:')
        print(DC10B)
        print('\nbinary:')
        print(DC10B)
        LSB = 0b11111111  # bin(DC10B) & 0x03)
        MSB = 0b11  # bun(DC10B) >> 2
        CAN.DoSendMsg(ADDRESS1, [0x22, 0x03, LSB], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1, [0x26, 0xFF, MSB], 3, 0x00)
        sleep(0.01)


# Duty Cycle Moteur 2, input de -100 a 100
def motor_setDC2(Duty):
        if Duty >= 100:
            DC10B = round(195 * 1023 / 200)
        elif Duty <= -100:
            DC10B = round(5 * 1023 / 200)
        else:
            DC10B = round((Duty * 0.9 + 100) * 1023 / 200)
        LSB = DC10B & 0x03
        MSB = DC10B >> 2
        CAN.DoSendMsg(ADDRESS1, [0x21, 0x03, LSB], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1, [0x25, 0xFF, MSB], 3, 0x00)
        sleep(0.01)


# Duty Cycle Moteur 3, input de -100 a 100
def motor_setDC3(Duty):
        if Duty >= 100:
            DC10B = round(195 * 1023 / 200)
        elif Duty <= -100:
            DC10B = round(5 * 1023 / 200)
        else:
            DC10B = round((Duty * 0.9 + 100) * 1023 / 200)
        LSB = DC10B & 0x03
        MSB = DC10B >> 2
        CAN.DoSendMsg(ADDRESS2, [0x22, 0x03, LSB], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2, [0x26, 0xFF, MSB], 3, 0x00)
        sleep(0.01)


# Duty Cycle Moteur 4, input de -100 a 100
def motor_setDC4(Duty):
        if Duty >= 100:
            DC10B = round(195 * 1023 / 200)
        elif Duty <= -100:
            DC10B = round(5 * 1023 / 200)
        else:
            DC10B = round((Duty * 0.9 + 100) * 1023 / 200)
        LSB = DC10B & 0x03
        MSB = DC10B >> 2
        CAN.DoSendMsg(ADDRESS2, [0x21, 0x03, LSB], 3, 0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2, [0x25, 0xFF, MSB], 3, 0x00)
        sleep(0.01)


# Message handler
def callback(cmd):
    command = cmd.data
    if command == 'forwards':
        print('initializing motors')
        motor_init()
        sleep(1.0)
        print('starting motors')
        motor_start()
        sleep(2.0)
        print('set motor1')
        motor_setDC1(10)
        sleep(2.0)
        print('set motor2')
        motor_setDC2(10)
        sleep(2.0)
        print('set motor3')
        motor_setDC3(10)
        sleep(2.0)
        print('set motor4')
        motor_setDC4(10)
        sleep(5.0)
        print('stopping motors')
        motor_stop()
    elif command == 'backwards':
        print('initializing and starting motors')
        motor_init()
        motor_start()
        print('moving forwards')
        motor_setDC1(10)
        motor_setDC2(10)
        motor_setDC3(10)
        motor_setDC4(10)
        sleep(3.0)
        print('stopping motors')
        motor_stop()
    elif command == 'stop':
        print('moving forwards')
        motor_setDC1(0)
        motor_setDC2(0)
        motor_setDC3(0)
        motor_setDC4(0)
        sleep(3.0)
        print('stopping motors')
        motor_stop()
    else:
        print('Unknown command, stopping instead')
        motor_stop()


def driver():
    rospy.init_node('driver', anonymous=True)
    rospy.Subscriber("omega_ref", String, callback)
    rospy.spin()


if __name__ == '__main__':
    try:
        driver()
    except rospy.ROSInterruptException:
        pass
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


# vitesse Roue 1(rad/s)
def Motor_getSpeed1():
    ToSPI = [0x1f, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    wheel_speed = 0
    # print(FromSPI)            #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if dirR:
        direction = -1
    else:
        direction = 1
    NbClockbetweenTrans = ((FromSPI[1] & 0x7f) * 256 ** 3) + (FromSPI[2] * 256 ** 2) + (FromSPI[3] * 256) + FromSPI[4]
    if NbClockbetweenTrans != 0:
        wheel_speed = direction * 2 * pi / (9728 * NbClockbetweenTrans * 2e-8)
    if (wheel_speed > 35) | (wheel_speed < -35):
        wheel_speed = 0
    return wheel_speed


# vitesse Roue 2(rad/s)
def Motor_getSpeed2():
    ToSPI = [0x2f, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    wheel_speed = 0
    # print(FromSPI)            #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if dirR:
        direction = -1
    else:
        direction = 1
    NbClockbetweenTrans = ((FromSPI[1] & 0x7f) * 256 ** 3) + (FromSPI[2] * 256 ** 2) + (FromSPI[3] * 256) + FromSPI[4]
    if NbClockbetweenTrans != 0:
        wheel_speed = direction * 2 * pi / (9728 * NbClockbetweenTrans * 2e-8)
    if (wheel_speed > 35) | (wheel_speed < -35):
        wheel_speed = 0
    return wheel_speed


# vitesse Roue 3(rad/s)
def Motor_getSpeed3():
    ToSPI = [0x3f, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    wheel_speed = 0
    # print(FromSPI)            #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if dirR:
        direction = -1
    else:
        direction = 1
    NbClockbetweenTrans = ((FromSPI[1] & 0x7f) * 256 ** 3) + (FromSPI[2] * 256 ** 2) + (FromSPI[3] * 256) + FromSPI[4]
    if NbClockbetweenTrans != 0:
        wheel_speed = direction * 2 * pi / (9728 * NbClockbetweenTrans * 2e-8)
    if (wheel_speed > 35) | (wheel_speed < -35):
        wheel_speed = 0
    return wheel_speed


# vitesse Roue 4(rad/s)
def Motor_getSpeed4():
    ToSPI = [0x4f, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    wheel_speed = 0
    # print(FromSPI)            #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if dirR:
        direction = 1
    else:
        direction = -1
    NbClockbetweenTrans = ((FromSPI[1] & 0x7f) * 256 ** 3) + (FromSPI[2] * 256 ** 2) + (FromSPI[3] * 256) + FromSPI[4]
    if NbClockbetweenTrans != 0:
        wheel_speed = direction * 2 * pi / (9728 * NbClockbetweenTrans * 2e-8)
    if (wheel_speed > 35) | (wheel_speed < -35):
        wheel_speed = 0
    return wheel_speed


def encoder():
    pub = rospy.Publisher('omega_mes', quad, queue_size=10)
    rospy.init_node('encoder', anonymous=True)
    rate = rospy.Rate(100)
    omega_mes = quad()
    while not rospy.is_shutdown():
        omega_mes.motor1 = Motor_getSpeed1()
        omega_mes.motor2 = Motor_getSpeed2()
        omega_mes.motor3 = Motor_getSpeed3()
        omega_mes.motor4 = Motor_getSpeed4()
        pub.publish(omega_mes)
        rate.sleep()


if __name__ == '__main__':
    try:
        encoder()
    except rospy.ROSInterruptException:
        pass

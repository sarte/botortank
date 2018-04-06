#!/usr/bin/env python


import rospy
import RPi.GPIO as GPIO
import spidev
import MyMCP2515
import time
from time import sleep
from ctypes import c_double
from math import *
from std_msgs.msg import String


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

ID_sorting = 0x01
ID_bee = 0x06
sorting_speed = 57


# send an instruction to the dynamixel
def instru_dyna(ID, LENGTH, INSTRU, P0, P1, P2):

    CHECK = ( ~(ID + LENGTH + INSTRU + P0 + P1 + P2)) & 0x000000FF

    ToSPI = [0x55, 0x00, 0x00, 0x01, 0x40]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x77, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x55, 0x00, 0x00, 0x01, 0x50]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x77,  CHECK, INSTRU, LENGTH, ID]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x55, 0x00, 0x00, 0x01, 0x60]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x77, 0x00, P2, P1, P0]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x55, 0x00, 0x00, 0x01, 0x40]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x77, 0x00, 0x00, 0x00, 0x01]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x77, 0x00, 0x00, 0x01, 0x40]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)


# enable dynamixel
def enable(ID):
    instru_dyna(ID, 0x05, 0x03, 0x18, 0x01, 0x01)


# disable dynamixel
def disable(ID):
    instru_dyna(ID, 0x05, 0x03, 0x18, 0x00, 0x00)


# gives an angle position
def dynamixel_angle(ID, angle, sorting_speed):
    if angle < 0:
        ang = 0x000
    elif angle > 300:
        ang = 0x3FF
    else:
        ang = round(angle * 0x3FF / 300)
    angLSB = ang & 0x00FF
    angMSB = ang >> 2
    # instru_dyna(ID,0x05,0x04,0x20,vitLSB,vitMSB)
    instru_dyna(ID, 0x05, 0x03, 0x1E, angLSB, angMSB)
    # instru_dyna(ID,0x02,0x05,0x00,0x00,0x00)


# sorting dynamixel initialization
def sorting_start():
    enable(ID_sorting)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x20, 0x00, 0x01)
    disable(ID_sorting)


# sorting dynamixel stop
def sorting_stop():
    enable(ID_sorting)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x00)
    disable(ID_sorting)


# 1st sorting sequence
def sorting1():
    enable(ID_sorting)
    # first ball
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)  # (ID, long, 0x03=write, changger angle,  angedeux premier bytes, angle dernier byte,
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    # all other balls
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)

    disable(ID_sorting)


# 2nd sorting sequence
def sorting2():
    enable(ID_sorting)
    # first two balls
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x66, 0x02)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    # all other balls
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x66, 0x02)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x66, 0x02)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x66, 0x02)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    sleep(0.3)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x00, 0x02)
    sleep(0.7)
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99, 0x01)
    disable(ID_sorting)


# bee dynamixel initialization
def bee_start():
    enable(ID_bee)
    instru_dyna(ID_bee, 0x05, 0x03, 0x20, 0x00, 0x02)
    disable(ID_bee)


# bee sequence
def bee():
    enable(ID_bee)
    sleep(1)
    instru_dyna(ID_bee, 0x05, 0x03, 0x1E, 0x00, 0x01)
    sleep(3)
    instru_dyna(ID_bee, 0x05, 0x03, 0x1E, 0x00, 0x02)


# stop everything
def stop():
    disable(ID_bee)
    disable(ID_sorting)


# Message handler
def callback(data):
    command = data.data
    if command == 'sorting1':
        print('enabling sorting dynamixel \n starting 1st sequence')
        sorting_start()
        sorting1()
        sorting_stop()
    elif command == 'sorting2':
        print('enabling sorting dynamixel \n starting 2nd sequence')
        sorting_start()
        sorting2()
    elif command == 'bee':
        print('enabling bee dynamixel \n starting bee sequence')
        bee_start()
        bee()
    else:
        print('Unknown command, stopping instead')
        stop()


# the node definition itself
def dynamixel():
    rospy.init_node('dynamixel', anonymous=True)
    print('node initiation: dynamixel')
    rospy.Subscriber('dynamixel_cmd', String, callback)
    print('topic initiation: dynamixel_cmd')
    rospy.spin()
    print('Shutting down: disabling dynamixels')
    stop()
    GPIO.cleanup()



if __name__ == '__main__':
    try:
        dynamixel()
    except rospy.ROSInterruptException:
        passs
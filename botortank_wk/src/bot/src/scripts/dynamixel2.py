#!/usr/bin/env python


import rospy
import RPi.GPIO as GPIO
import spidev
import MyMCP2515
import time
from time import sleep
from ctypes import c_double
from math import *
from std_msgs.msg import Int8

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

ID_bee = 0x01
ID_sorting = 0x06
ID_ball = 0x02
sorting_speed = 57
command = 0


# send an instruction to the dynamixel
def instru_dyna(ID, LENGTH, INSTRU, P0, P1, P2):
    CHECK = (~(ID + LENGTH + INSTRU + P0 + P1 + P2)) & 0x000000FF

    ToSPI = [0x55, 0x00, 0x00, 0x01, 0x40]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x77, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x55, 0x00, 0x00, 0x01, 0x50]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    ToSPI = [0x77, CHECK, INSTRU, LENGTH, ID]
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


# sorting dynamixel initialization
def sorting_init():
    instru_dyna(ID_sorting, 0x05, 0x03, 0x20, 0x00, 0x01)


# 1st sorting sequence
def sorting1():
    # first ball
    instru_dyna(ID_sorting, 0x05, 0x03, 0x1E, 0x99,
                0x01)  # (ID, long, 0x03=write, changger angle,  angedeux premier bytes, angle dernier byte,
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


# 2nd sorting sequence
def sorting2():
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


# bee dynamixel initialization
def bee_init():
    instru_dyna(ID_bee, 0x05, 0x03, 0x20, 0x00, 0x02)


# bee sequence
def bee_up():
    sleep(0.1)
    instru_dyna(ID_bee, 0x05, 0x03, 0x1E, 0xaa, 0x02)


def bee_down():
    sleep(0.1)
    instru_dyna(ID_bee, 0x05, 0x03, 0x1E, 0x00, 0x02)


def ball():
    sleep(1)
    instru_dyna(ID_ball, 0x05, 0x03, 0x20, 0x00, 0x03)
    sleep(10)


# stop everything
def stop():
    disable(ID_bee)
    disable(ID_sorting)
    disable(ID_ball)


# Message handler
def callback(data):
    global command
    command = data.data
    rospy.loginfo(command)


# the node definition itself
def dynamixel2():
    rospy.init_node('dynamixel', anonymous=True)
    # print('node initiation: dynamixel')
    rospy.Subscriber('dynamixel_cmd', Int8, callback, queue_size=1)
    # print('topic initiation: dynamixel_cmd')
    pub = rospy.Publisher('dyna_feedback', Int8, queue_size=1)
    rate = rospy.Rate(10)
    enable(ID_sorting)
    sleep(0.1)
    enable(ID_bee)
    sleep(0.1)
    enable(ID_ball)
    sleep(0.1)
    bee_init()
    sleep(0.1)
    sorting_init()
    sleep(0.1)
    while not rospy.is_shutdown():
        feedback = 0
        if command == 1:  # 'sorting1':
            # print('enabling sorting \n starting 1')
            # enable(ID_sorting)
            # sleep(0.1)
            # sorting_init()
            # sleep(0.1)
            sorting1()
            sleep(0.1)
            # disable(ID_sorting)
            # sleep(0.1)
            feedback = 1
            pub.publish(feedback)
        elif command == 2:  # 'sorting2':
            # print('enabling sorting \n starting 2')
            # enable(ID_sorting)
            # sleep(0.1)
            # sorting_init()
            # sleep(0.1)
            sorting2()
            sleep(0.1)
            # disable(ID_sorting)
            # sleep(0.1)
            feedback = 2
            pub.publish(feedback)
        elif command == 3:  # 'bee':
            # rospy.loginfo('blow me')
            bee_up()
            sleep(0.1)
            feedback = 3
            sleep(0.1)
            pub.publish(feedback)
            sleep(1)
            bee_down()
            sleep(0.1)
            # disable(ID_bee)
            # rospy.loginfo('no, blow me')
            # print('enabling bee \n starting bee')
            # feedback = 3
            # pub.publish(feedback)
        elif command == 4:  # 'ball':
            # print('starting ball sequence')
            # enable(ID_ball)
            # sleep(0.1)
            instru_dyna(0xFE, 0x05, 0x03, 0x18, 0x01, 0x01)
            ball()
            sleep(10)
            feedback = 4
            pub.publish(feedback)
        else:
            # print('Unknown command, stopping instead')
            rospy.loginfo('nothing')
            stop()
            # rate.sleep()
    print('Shutting down: disabling dynamixels')
    stop()
    GPIO.cleanup()


if __name__ == '__main__':
    try:
        dynamixel2()
    except rospy.ROSInterruptException:
        pass

#!/usr/bin/env python3

import rospy
from std_msgs.msg import String

import RPi.GPIO as GPIO
import MyMCP2515
import spidev

#import time
#from time import sleep

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

# set ID s for dynamixel
ID_tri=0x05
ID_bee=0x06
ID_ball=0x01
vit_tri=57

# Start the dynamixel
def dynamixel_start(ID):
    instru_dyna(ID,0x05,0x03,0x18,0x01,0x01)

#disable dynamixel
def dynamixel_stop(ID):
    instru_dyna(ID,0x05,0x03,0x18,0x00,0x00)

#envoie une instruction au dynamixel
def instru_dyna(ID,LENGTH,INSTRU,P0,P1,P2):

    CHECK=(~(ID+LENGTH+INSTRU+P0+P1+P2)) & 0x000000FF

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


def dynamixel_angle(ID,angle,speed):
   # vit=round(speed*0x3FF/114)
    #if (vit<1):
     #   vit=0x001
  #  if(vit>0x3FF):
   #     vit=0x3FF
    #vitLSB= vit & 0x00FF
    #vitMSB= vit>>2
    if (angle<0):
        ang=0x000
    elif(angle>300):
        ang=0x3FF
    else:
        ang=round(angle*0x3FF/300)
    angLSB= ang & 0x00FF
    angMSB= ang>>2
    #instru_dyna(ID,0x05,0x04,0x20,vitLSB,vitMSB)
    instru_dyna(ID,0x05,0x03,0x1E,angLSB,angMSB)
    #instru_dyna(ID,0x02,0x05,0x00,0x00,0x00)


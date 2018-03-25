#!/usr/bin/env python


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

# det dynamixel ID
ID_tri=0x05
ID_bee=0x06
ID_ball=0x01
vit_tri=57

# enable dynamixel
def dynamixel_start(ID):
    instru_dyna(ID,0x05,0x03,0x18,0x01,0x01)

# disable dynamixel
def dynamixel_stop(ID):
    instru_dyna(ID,0x05,0x03,0x18,0x00,0x00)

# envoie une instruction au dynamixel
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

#iniatialise le tri
def tri_start():
    dynamixel_start(ID_tri)
    instru_dyna(ID_tri,0x05,0x03,0x20,0x00,0x02)
    dynamixel_stop(ID_tri)

#lance la 1ere sequence de tri
def tri_1():
    dynamixel_start(ID_tri)
    cnt=0
    if(cnt<=8):
        instru_dyna(ID_tri,0x05,0x03,0x1E,0x00,0x01)
        sleep(0.3)
        instru_dyna(ID_tri,0x05,0x03,0x1E,0x00,0x02)
        sleep(0.7)
        cnt+=1
    dynamixel_stop(ID_tri)

#lance la 2e sequence de tri
def tri_2():
    dynamixel_start(ID_tri)
    cnt=0
    if (cnt<4):
        instru_dyna(ID_tri,0x05,0x03,0x1E,0x00,0x03)
        sleep(0.3)
        instru_dyna(ID_tri,0x05,0x03,0x1E,0x00,0x02)
        sleep(0.7)
        instru_dyna(ID_tri,0x05,0x03,0x1E,0x00,0x01)
        sleep(0.3)
        instru_dyna(ID_tri,0x05,0x03,0x1E,0x00,0x02)
        sleep(0.7)
        cnt+=1
    dynamixel_stop(ID_tri)

#iniatilise l'abeille
def bee_start():
    dynamixel_start(ID_bee)
    instru_dyna(ID_bee,0x05,0x03,0x20,0x00,0x02)
    dynamixel_stop(ID_bee)
#lance la sequence de l'abeille
def bee():
    dynamixel_start(ID_bee)
    sleep(0.3)
    instru_dyna(ID_bee,0x05,0x03,0x1E,0x00,0x01)
    sleep(3)
    instru_dyna(ID_bee,0x05,0x03,0x1E,0x00,0x02)

#initialise pour le bloquage de ball
def ball_start():
    dynamixel_start(ID_ball)
    instru_dyna(ID_ball,0x05,0x03,0x20,0x00,0x02)
    dynamixel_stop(ID_ball)
	
#lance la sequence
def ball():
    dynamixel_start(ID_ball)
    sleep(0.3)
    instru_dyna(ID_ball,0x05,0x03,0x1E,0x80,0x00)
    sleep(3)
    instru_dyna(ID_ball,0x05,0x03,0x1E,0x00,0x03)
	
# stop all dynamixel
def stop():
    dynamixel_stop(ID_tri)
    dynamixel_stop(ID_bee)
    dynamixel_stop(ID_ball)



# Message handler
def CommandCallback(commandMessage):
    command = commandMessage.data
    if command == 'tri_start':
        print('Enabling Tri')
        tri_start()
    elif command == 'tri_1':
        print('Triage 1')
        tri_1()
    elif command == 'tri_2':
        print('Triage 2')
        tri_2()
    elif command == 'bee_start':
        print('Enabling Bee')
        bee_start()
    elif command == 'bee':
        print('Deploying bee arm')
        bee()	
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
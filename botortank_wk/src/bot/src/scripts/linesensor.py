import RPi.GPIO as GPIO
import time
from time import sleep
import spidev
#import MyMotor
#import Turret
import MyMCP2515
from ctypes import c_double
from math import *

MyARM_ResetPin = 19 # Pin 4 of connector = BCM19 = GPIO[1]

MySPI_FPGA = spidev.SpiDev()
MySPI_FPGA.open(0,0)
MySPI_FPGA.max_speed_hz = 500000

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(MyARM_ResetPin, GPIO.OUT)

GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)


#Lance l'adc
def ADC_start():
    ToSPI=[0x55,0x80,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

#retourne les valeurs de line followers
#nommé entre les 2 roues où ils sont situés
def Follow():
    ToSPI=[0x8f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F34= (FromSPI[1] & 0x0f)*256+FromSPI[2]#niqué
    #print(F1)
    F23= (FromSPI[3] & 0x0f)*256+FromSPI[4]
    #print(F0)
    ToSPI=[0x9f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F12= (FromSPI[1] & 0x0f)*256+FromSPI[2]
    #print(F3)
    F41= (FromSPI[3] & 0x0f)*256+FromSPI[4]
    #print(F2)
    return F12,F23,F34,F41

#retourne la valeur du IR
def IR():
    ToSPI=[0x0f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F1= (FromSPI[1] & 0x0f)*256+FromSPI[2]

import RPi.GPIO as GPIO
import time
from time import sleep
import spidev
#import MyMotor
#import Turret
import MyMCP2515
from ctypes import c_double
from math import *

#Lance l'adc
def ADC_start():
    ToSPI=[0x55,0x80,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

#retourne les valeurs de line followers
def Follow():
    ToSPI=[0x8f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F1= (FromSPI[1] & 0x0f)*256+FromSPI[2]
    F0= (FromSPI[3] & 0x0f)*256+FromSPI[4]
    ToSPI=[0x9f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F3= (FromSPI[1] & 0x0f)*256+FromSPI[2]
    F2= (FromSPI[3] & 0x0f)*256+FromSPI[4]

#retourne la valeur du IR
def IR():
    ToSPI=[0x0f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    F1= (FromSPI[1] & 0x0f)*256+FromSPI[2]

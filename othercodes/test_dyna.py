import RPi.GPIO as GPIO
import time
from time import sleep
import spidev
from MOTOR import *
from GETC import *
from DYNA import *
import MyMCP2515
from math import *


dynamixel_start(1)

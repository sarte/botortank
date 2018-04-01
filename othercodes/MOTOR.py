import MyMCP2515
from time import sleep
import spidev
import RPi.GPIO as GPIO
from math import pi

ADDRESS1= 0x708 #identifiant pour envoyer des donnees
ADDRESS_RECEIVE1= 0x700 #identifiant pour recevoir
ADDRESS2= 0x408 #identifiant pour envoyer des donnees
ADDRESS_RECEIVE2= 0x400 #identifiant pour recevoir
#duty cycle=0.5 so robot stay at rest
DCL=0.5
DCR=0.5
PRESCALE=0x00
CAN= MyMCP2515.MCP2515()
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



#initialisation moteur
def Motor_init():
        CAN.DoSendMsg(ADDRESS1,[0x23,0xFF,0xFF],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1,[0x24,0xFF,0xFF],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2,[0x23,0xFF,0xFF],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2,[0x24,0xFF,0xFF],3,0x00)
        sleep(0.01)
        TCON= 0x80 | PRESCALE
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1,[0x21,0xFF,TCON],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1,[0x22,0xFF,TCON],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2,[0x21,0xFF,TCON],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2,[0x22,0xFF,TCON],3,0x00)
        sleep(0.01)
        Motor_setDC1(0.5)
        sleep(0.01)
        Motor_setDC2(0.5)
        sleep(0.01)
        Motor_setDC3(0.5)
        sleep(0.01)
        Motor_setDC4(0.5)
        sleep(0.01)





#led ON, Frein OFF
def Motor_start():
        CAN.DoSendMsg(ADDRESS1,[0x1F,0x40,0x00],3,0x00)
        sleep(0.001)
        CAN.DoSendMsg(ADDRESS1,[0x1E,0x70,0x40],3,0x00)
        CAN.DoSendMsg(ADDRESS2,[0x1F,0x40,0x00],3,0x00)
        sleep(0.001)
        CAN.DoSendMsg(ADDRESS2,[0x1E,0x70,0x40],3,0x00)
#led OFF, Frein ON
def Motor_stop():
        Motor_setDC1(0)
        sleep(0.01)
        Motor_setDC2(0)
        sleep(0.01)
        Motor_setDC3(0)
        sleep(0.01)
        Motor_setDC4(0)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1,[0x1E,0x70,0x30],3,0x00)
        CAN.DoSendMsg(ADDRESS2,[0x1E,0x70,0x30],3,0x00)



#Duty Cycle Moteur 1, input de -100 a 100
def Motor_setDC1(Duty):
        if Duty >= 100:
            DC10B=round(195*1023/200)
        elif(Duty<=-100):
            DC10B=round(5*1023/200)
        else:
            DC10B = round((Duty*0.9+100)*1023/200)
        LSB = DC10B & 0x03
        MSB = DC10B >> 2
        CAN.DoSendMsg(ADDRESS1,[0x22,0x03,LSB],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1,[0x26,0xFF,MSB],3,0x00)
        sleep(0.01)

#Duty Cycle Moteur 2, input de -100 a 100
def Motor_setDC2(Duty):
        if(Duty>=100):
            DC10B=round(195*1023/200)
        elif(Duty<=-100):
            DC10B=round(5*1023/200)
        else:
            DC10B = round((Duty*0.9+100)*1023/200)
        LSB = DC10B & 0x03
        MSB = DC10B >> 2
        CAN.DoSendMsg(ADDRESS1,[0x21,0x03,LSB],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS1,[0x25,0xFF,MSB],3,0x00)
        sleep(0.01)

#Duty Cycle Moteur 3, input de -100 a 100
def Motor_setDC3(Duty):
        if(Duty>=100):
            DC10B=round(195*1023/200)
        elif(Duty<=-100):
            DC10B=round(5*1023/200)
        else:
            DC10B = round((Duty*0.9+100)*1023/200)
        LSB = DC10B & 0x03
        MSB = DC10B >> 2
        CAN.DoSendMsg(ADDRESS2,[0x22,0x03,LSB],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2,[0x26,0xFF,MSB],3,0x00)
        sleep(0.01)

#Duty Cycle Moteur 4, input de -100 a 100
def Motor_setDC4(Duty):
        if(Duty>=100):
            DC10B=round(195*1023/200)
        elif(Duty<=-100):
            DC10B=round(5*1023/200)
        else:
            DC10B = round((Duty*0.9+100)*1023/200)
        LSB = DC10B & 0x03
        MSB = DC10B >> 2
        CAN.DoSendMsg(ADDRESS2,[0x21,0x03,LSB],3,0x00)
        sleep(0.01)
        CAN.DoSendMsg(ADDRESS2,[0x25,0xFF,MSB],3,0x00)
        sleep(0.01)







#vitesse Roue 1(rad/s)
def Motor_getSpeed1():
    ToSPI = [0x1f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    wheel_speed=0
    #print(FromSPI)            #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if(dirR):
        direction = -1
    else:
        direction = 1
    NbClockbetweenTrans = ((FromSPI[1]&0x7f)*256**3) + (FromSPI[2]*256**2) + (FromSPI[3]*256) + FromSPI[4]
    if(NbClockbetweenTrans != 0):
        wheel_speed = direction*2*pi/(9728*NbClockbetweenTrans*2e-8)
    if( wheel_speed>35 || wheel_speed<-35):
        wheel_speed=0;
    return wheel_speed

#vitesse Roue 2(rad/s)
def Motor_getSpeed2():
    ToSPI = [0x2f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    wheel_speed=0
    #print(FromSPI)            #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if(dirR):
        direction = 1
    else:
        direction = -1
    NbClockbetweenTrans = ((FromSPI[1]&0x7f)*256**3) + (FromSPI[2]*256**2) + (FromSPI[3]*256) + FromSPI[4]
    if(NbClockbetweenTrans != 0):
        wheel_speed = direction*2*pi/(9728*NbClockbetweenTrans*2e-8)
    if(wheel_speed>35 || wheel_speed<-35):
        wheel_speed=0;

    return wheel_speed

#vitesse Roue 3(rad/s)
def Motor_getSpeed3():
    ToSPI = [0x3f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    #print(FromSPI)
    wheel_speed=0   #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if(dirR):
        direction = 1
    else:
        direction = -1
    NbClockbetweenTrans = ((FromSPI[1]&0x7f)*256**3) + (FromSPI[2]*256**2) + (FromSPI[3]*256) + FromSPI[4]
    if(NbClockbetweenTrans != 0):
        wheel_speed = direction*2*pi/(9728*NbClockbetweenTrans*2e-8)
    if( wheel_speed>35 || wheel_speed<-35):
        wheel_speed=0;

    return wheel_speed

#vitesse Roue 4(rad/s)
def Motor_getSpeed4():
    ToSPI = [0x4f,0x00,0x00,0x00,0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    wheel_speed=0
    #print(FromSPI)            #we got a response on the last byte slot of FromSPI
    dirR = FromSPI[1] & 0x80
    if(dirR):
        direction = 1
    else:
        direction = -1
    NbClockbetweenTrans = ((FromSPI[1]&0x7f)*256**3) + (FromSPI[2]*256**2) + (FromSPI[3]*256) + FromSPI[4]
    if(NbClockbetweenTrans != 0):
        wheel_speed = direction*2*pi/(9728*NbClockbetweenTrans*2e-8)
    if( wheel_speed>35 || wheel_speed<-35):
        wheel_speed=0;

    return wheel_speed



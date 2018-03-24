import RPi.GPIO as GPIO
import time
from time import sleep
import spidev
from MOTOR import *
from GETC import *
from DYNA import *
import MyMCP2515
from math import *



#CAN= MyMCP2515.MCP2515()

#CAN.DoSendMsg(0x508,[0x1f,0x40,0x00],3,0x00)

#CAN.DoSendMsg(0x708,[0x1E,0x70,0x40],3,0x00)


Motor_init()
sleep(0.5)
Motor_start()
sleep(2)
theCtrlStruct, c_init_speedController, c_run_speedController = Getc()
w1=Motor_getSpeed1()
w2=Motor_getSpeed2()
w3=Motor_getSpeed3()
w4=Motor_getSpeed4()
theCtrlStruct.theCtrlIn.contents.wheel_1_speed= w1
theCtrlStruct.theCtrlIn.contents.wheel_2_speed= w2
theCtrlStruct.theCtrlIn.contents.wheel_3_speed= w3
theCtrlStruct.theCtrlIn.contents.wheel_4_speed= w4
referenceSpeedArray = c_double * 4
omega_ref_array = referenceSpeedArray(vit,vit,vit,vit)
c_init_speedController(theCtrlStruct)
t = time.clock()
old_t = time.clock()
theCtrlStruct.theCtrlIn.contents.t = time.clock()
vit=2

refresh=0.01
i=0
while(i<100):
    if((t-old_t)>refresh):
        w1=Motor_getSpeed1()
        w2=Motor_getSpeed2()
        w3=Motor_getSpeed3()
        w4=Motor_getSpeed4()
        theCtrlStruct.theCtrlIn.contents.wheel_1_speed= w1
        theCtrlStruct.theCtrlIn.contents.wheel_2_speed= w2
        theCtrlStruct.theCtrlIn.contents.wheel_3_speed= w3
        theCtrlStruct.theCtrlIn.contents.wheel_4_speed= w4
        referenceSpeedArray = c_double * 4
        omega_ref_array = referenceSpeedArray(vit,vit,vit,vit)
        c_run_speedController(theCtrlStruct, omega_ref_array)
        Motor_setDC1(theCtrlStruct.theCtrlOut.contents.wheel_commands[0])
        Motor_setDC2(theCtrlStruct.theCtrlOut.contents.wheel_commands[1])
        Motor_setDC3(theCtrlStruct.theCtrlOut.contents.wheel_commands[2])
        Motor_setDC4(theCtrlStruct.theCtrlOut.contents.wheel_commands[3])
        print(w1,w3)
        i+=1
        old_t=time.clock()
        #sleep(0.005)
    t=time.clock()


Motor_stop()
#Motor_setDC1(60)
#sleep(0.001)
#Motor_setDC2(60)
#sleep(0.001)
#Motor_setDC3(60)
#sleep(0.001)
#Motor_setDC4(60)
#i=0
#start = time.clock()
#while (i<1000):
#    w1 = Motor_getSpeed1()
#    w2 = Motor_getSpeed2()
#    w3 = Motor_getSpeed3()
#    w4 = Motor_getSpeed4()
#    t = i*0.002
#    print(t,w1,w2,w3,w4)
#    i+=1
#    sleep(0.002)
#Motor_stop()




#Motor_setDC1(20)
#sleep(1)
#Motor_setDC1(20)
#sleep(5)
#i=0
#while(i<10):
 #   w=Motor_getSpeed1()
  #  i+=1
   # sleep(0.2)
    #print(w)
#Motor_setDC1(20)
#sleep(0.001)
#Motor_setDC2(-20)
#sleep(5)
#Motor_setDC1(-20)
#sleep(0.001)
#Motor_setDC2(0)
#sleep(5)
#Motor_setDC1(-20)
#sleep(0.001)
#Motor_setDC2(20)
#sleep(5)


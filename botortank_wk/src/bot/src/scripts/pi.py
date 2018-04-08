#!/usr/bin/env python


import rospy
import time
from time import sleep
from math import *
from math import pi
from bot.msg import *

old_time = 0
omega_ref_1 = 0
omega_ref_2 = 0
omega_ref_3 = 0
omega_ref_4 = 0
omega_1 = 0
omega_2 = 0
omega_3 = 0
omega_4 = 0
ratio = 19
ie1 = 0
ie2 = 0
ie3 = 0
ie4 = 0


def PI(ref1, ref2, ref3, ref4, mes1, mes2, mes3, mes4):
    current_time = rospy.get_rostime()
    error1 = ref1 - mes1
    error1 = ref2 - mes2
    error1 = ref3 - mes3
    error1 = ref4 - mes4
    dt = current_time - old_time
    delta_error1 = dt * e1
    delta_error2 = dt * e2
    delta_error3 = dt * e3
    delta_error4 = dt * e4
    old_ie1 = ie1
    old_ie2 = ie2
    old_ie3 = ie3
    old_ie4 = ie4
    old_time = current_time


def refcallback(ref):
    global omega_ref_1
    global omega_ref_2
    global omega_ref_3
    global omega_ref_4
    omega_ref_1 = ref.motor1 * ratio
    omega_ref_2 = ref.motor2 * ratio
    omega_ref_3 = ref.motor3 * ratio
    omega_ref_4 = ref.motor4 * ratio


def mescallback(mes):
    global omega_mes_1
    global omega_mes_2
    global omega_mes_3
    global omega_mes_4
    omega_mes_1 = mes.motor1 * ratio
    omega_mes_2 = mes.motor2 * ratio
    omega_mes_3 = mes.motor3 * ratio
    omega_mes_4 = mes.motor4 * ratio


def speed():
    rospy.init_node('speed', anonymous=True)
    rospy.Subscriber("omega_cmd", quad, refcallback, queue_size=10)
    rospy.Subscriber("omega_mes", quad, mescallback, queue_size=10)
    rate = rospy.Rate(100)
    global kp
    global ki
    kp = 0.316039698735464
    ki = 5.5203351563618
    global old_ie1


    while not rospy.is_shutdown():
        PI(omega_ref_1, omega_ref_2, omega_ref_3, omega_ref_4, omega_1, omega_2, omega_3, omega_4);
        old_ie1 = ie1
        old_ie2 = ie2
        old_ie3 = ie3
        old_ie4 = ie4
    rospy.spin()



if __name__ == '__main__':
    try:
        speed()
    except rospy.ROSInterruptException:
        pass

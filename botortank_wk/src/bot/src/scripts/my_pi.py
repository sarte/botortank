#!/usr/bin/env python


import rospy
import time
from time import sleep
from math import *
from math import pi
from bot.msg import *

ref_1 = 0
ref_2 = 0
ref_3 = 0
ref_4 = 0
mes_1 = 0
mes_2 = 0
mes_3 = 0
mes_4 = 0


class PID:
    """PID Controller
    """

    def __init__(self, P=0.2, I=0.0, D=0.0):

        self.Kp = P
        self.Ki = I
        self.Kd = D

        self.sample_time = 0.00
        self.current_time = time.time()
        self.last_time = self.current_time

        self.clear()

    def clear(self):
        """Clears PID computations and coefficients"""
        self.SetPoint = 0.0

        self.PTerm = 0.0
        self.ITerm = 0.0
        self.DTerm = 0.0
        self.last_error = 0.0

        # Windup Guard
        self.int_error = 0.0
        self.windup_guard = 20.0

        self.output = 0.0

    def update(self, feedback_value):
        """Calculates PID value for given reference feedback
        .. math::
            u(t) = K_p e(t) + K_i \int_{0}^{t} e(t)dt + K_d {de}/{dt}
        .. figure:: images/pid_1.png
           :align:   center
           Test PID with Kp=1.2, Ki=1, Kd=0.001 (test_pid.py)
        """
        error = self.SetPoint - feedback_value

        self.current_time = time.time()
        delta_time = self.current_time - self.last_time
        delta_error = error - self.last_error

        if (delta_time >= self.sample_time):
            self.PTerm = self.Kp * error
            self.ITerm += error * delta_time

            if (self.ITerm < -self.windup_guard):
                self.ITerm = -self.windup_guard
            elif (self.ITerm > self.windup_guard):
                self.ITerm = self.windup_guard

            self.DTerm = 0.0
            if delta_time > 0:
                self.DTerm = delta_error / delta_time

            # Remember last time and last error for next calculation
            self.last_time = self.current_time
            self.last_error = error

            self.output = self.PTerm + (self.Ki * self.ITerm) + (self.Kd * self.DTerm)

    def setKp(self, proportional_gain):
        """Determines how aggressively the PID reacts to the current error with setting Proportional Gain"""
        self.Kp = proportional_gain

    def setKi(self, integral_gain):
        """Determines how aggressively the PID reacts to the current error with setting Integral Gain"""
        self.Ki = integral_gain

    def setKd(self, derivative_gain):
        """Determines how aggressively the PID reacts to the current error with setting Derivative Gain"""
        self.Kd = derivative_gain

    def setWindup(self, windup):
        """Integral windup, also known as integrator windup or reset windup,
        refers to the situation in a PID feedback controller where
        a large change in setpoint occurs (say a positive change)
        and the integral terms accumulates a significant error
        during the rise (windup), thus overshooting and continuing
        to increase as this accumulated error is unwound
        (offset by errors in the other direction).
        The specific problem is the excess overshooting.
        """
        self.windup_guard = windup

    def setSampleTime(self, sample_time):
        """PID that should be updated at a regular interval.
        Based on a pre-determined sampe time, the PID decides if it should compute or return immediately.
        """
        self.sample_time = sample_time


def control_motor(mes, ref):
    pid = PID(5, 0.3, 0.001)
    pid.setSampleTime(0.01)
    pid.SetPoint = ref
    feedback = mes
    pid.update(feedback)
    return pid.output


def refcallback(ref):
    global ref_1
    global ref_2
    global ref_3
    global ref_4
    ref_1 = ref.motor1 * ratio
    ref_2 = ref.motor2 * ratio
    ref_3 = ref.motor3 * ratio
    ref_4 = ref.motor4 * ratio


def mescallback(mes):
    global mes_1
    global mes_2
    global mes_3
    global mes_4
    mes_1 = mes.motor1 * ratio
    mes_2 = mes.motor2 * ratio
    mes_3 = mes.motor3 * ratio
    mes_4 = mes.motor4 * ratio

def speed():
    rospy.init_node('speed', anonymous=True)
    pub = rospy.Publisher('omega_cmd', quad, queue_size=1)
    rospy.Subscriber('omega_ref', quad, refcallback)
    rospy.Subscriber('omega_mes', quad, mescallback)
    rate = rospy.Rate(1000)
    while not rospy.is_shutdown():
        rospy.Publisher('omega_cmd', quad)
        cmd.motor1 = control_motor(mes_1, ref_1)
        sleep(0.01)
        cmd.motor2 = control_motor(mes_2, ref_2)
        sleep(0.01)
        cmd.motor3 = control_motor(mes_3, ref_3)
        sleep(0.01)
        cmd.motor4 = control_motor(mes_4, ref_4)
        sleep(0.01)
        pub.publish(cmd)
        rate.sleep()
        rospy.spin()



if __name__ == '__main__':
    try:
        speed()
    except rospy.ROSInterruptException:
        pass

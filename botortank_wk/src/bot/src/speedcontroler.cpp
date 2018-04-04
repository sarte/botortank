#include "ros/ros.h"
#include "std_msgs/String.h"
#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structure.h"
#define Kp 0.03
#define Ki 0.052

Struct* cvs;
ros::Time old_time = ros::Time::now();
double omega_ref_1 = 0;
double omega_ref_2 = 0;
double omega_ref_3 = 0;
double omega_ref_4 = 0;
double omega_1 = 0;
double omega_2 = 0;
double omega_3 = 0;
double omega_4 = 0;
double error_1 = 0;
double error_2 = 0;
double error_3 = 0;
double error_4 = 0;
double int_error_1 = 0;
double int_error_2 = 0;
double int_error_3 = 0;
double int_error_4 = 0;
double ratio = 19;
double dt = 0;

void refCallback(const bot::quad& omega_ref)
{
    omega_ref_1 = omega_ref.motor1 * ratio; // right motor reference speed
    omega_ref_2 = omega_ref.motor2 * ratio;
    omega_ref_3 = omega_ref.motor3 * ratio;
    omega_ref_4 = omega_ref.motor4 * ratio;
}

void speedControllerCallback(const bot::quad& omega_mes){

    ros::Time current_time = ros::Time::now();

    //double vsat = 24;
    //double isat = 0.78;
    double v1, v2, v3, v4;

    omega_1 = omega_mes.motor1 * ratio; // left motor current speed
    omega_2 = omega_mes.motor2 * ratio;
    omega_3 = omega_mes.motor3 * ratio;
    omega_4 = omega_mes.motor4 * ratio;
    /*CtrlIn *in = cvs->inputs;
    CtrlOut *out = cvs->outputs;*/
    // left motor reference speed
     // right motor current speed
    error_1 = omega_ref_1 - omega_1; // left speed error
    error_2 = omega_ref_2 - omega_2;
    error_3 = omega_ref_3 - omega_3;
    error_4 = omega_ref_4 - omega_4; // right speed error
    int_error_1 = cvs->int_error_1; //left speed integrarion error
    int_error_2 = cvs->int_error_2;
    int_error_3 = cvs->int_error_3;
    int_error_4 = cvs->int_error_4; //right speed integration error
    dt = (current_time.toSec()-old_time.toSec());
    int_error_1 += dt*error_1;
    int_error_2 += dt*error_2;
    int_error_3 += dt*error_3;
    int_error_4 += dt*error_4;
    cvs->int_error_1 = int_error_1;
    cvs->int_error_2 = int_error_2;
    cvs->int_error_3 = int_error_3;
    cvs->int_error_4 = int_error_4;
    v1 = Kp*error_1 + Ki*int_error_1; // voltage command in [-24;24]
    v2 = Kp*error_2 + Ki*int_error_2; // voltage command in [-24;24]
    v3 = Kp*error_3 + Ki*int_error_3; // voltage command in [-24;24]
    v4 = Kp*error_4 + Ki*int_error_4; // voltage command in [-24;24]
    if (v1 > 0.9*24)
        v1 = 0.9*24;
    if (v1 < -0.9*24)
        v1 = -0.9*24;
    if (v2 > 0.9*24)
        v2 = 0.9*24;
    if (v2 < -0.9*24)
        v2 = -0.9*24;
    if (v3 > 0.9*24)
        v3 = 0.9*24;
    if (v3 < -0.9*24)
        v3 = -0.9*24;
    if (v4 > 0.9*24)
        v4 = 0.9*24;
    if (v4 < -0.9*24)
        v4 = -0.9*24;

    v1 = 1000*v1/(24*9);
    v2 = 1000*v2/(24*9);
    v3 = 1000*v3/(24*9);
    v4 = 1000*v4/(24*9);



    cvs->wheel_commands1 = v1;
    cvs->wheel_commands2 = v2;
    cvs->wheel_commands3 = v3;
    cvs->wheel_commands4 = v4;
    old_time = current_time;

}

int main(int argc, char **argv) {
    Struct* cvs;
    ros::init(argc, argv, "speedcontroller");
    ros::NodeHandle n;
    ros::NodeHandle n1;
    ros::NodeHandle n2;
    ros::Subscriber sub1 = n1.subscribe("omega_ref", 1000, speedControllerCallback);
    ros::Subscriber sub2 = n2.subscribe("omega_mes", 1000, speedControllerCallback);
    ros::Publisher pub = n.advertise<bot::quad>("omega_cmd", 1000);
    ros::Rate loop_rate(100);
    bot::quad command;

    while (ros::ok())
    {

        command.motor1 = cvs->wheel_commands1;
        command.motor2 = cvs->wheel_commands2;
        command.motor3 = cvs->wheel_commands3;
        command.motor4 = cvs->wheel_commands4;
        pub.publish(command);
        ros::spinOnce();
        loop_rate.sleep();

    }

    ros::spin(); //enters a loop calling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}
#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "structure.h"
//#define Kp //100//0.03//6.20286471355455//0.316039698735464//0.3//0.03
//#define Ki  //0.142897881346661//0//0.052//0.052//15663.5814742697//5.5203351563618//0.52//0.052
double omega_ref_1 = 0;
double omega_ref_2 = 0;
double omega_ref_3 = 0;
double omega_ref_4 = 0;
double omega_1 = 0;
double omega_2 = 0;
double omega_3 = 0;
double omega_4 = 0;
int ratio = 19;
ros::Time old_time(0.0);
//Struct* cvs;// = (Struct*)malloc(sizeof(Struct));
//cvs = init_Struct();


typedef struct Struct
{
    double int_error_1,int_error_2,int_error_3,int_error_4;
    double wheel_commands1,wheel_commands2,wheel_commands3,wheel_commands4;
    //double omega_ref_1,omega_ref_2,omega_ref_3,omega_ref_4;
    //double omega_1,omega_2,omega_3,omega_4;
    //int ratio;
} Struct;

Struct* init_Struct()
{
    Struct *cvs;
    cvs = (Struct*)malloc(sizeof(Struct));
    cvs->int_error_1 = 0;
    cvs->int_error_2 = 0;
    cvs->int_error_3 = 0;
    cvs->int_error_4 = 0;
    cvs->wheel_commands1 = 0;
    cvs->wheel_commands2 = 0;
    cvs->wheel_commands3 = 0;
    cvs->wheel_commands4 = 0;
    //cvs->omega_ref_1 = 0;
    //cvs->omega_ref_2 = 0;
    //cvs->omega_ref_3 = 0;
    //cvs->omega_ref_4 = 0;
    //cvs->omega_1 = 0;
    //cvs->omega_2 = 0;
    //cvs->omega_3 = 0;
    //cvs->omega_4 = 0;
    //cvs->ratio = 19;
    
    return cvs;
    
}

void free_Struct(Struct *cvs)
{
    free(cvs);
}


void refCallback(const bot::quad& omega_ref)
{
    omega_ref_1 = omega_ref.motor1 * ratio;
    omega_ref_2 = omega_ref.motor2 * ratio;
    omega_ref_3 = omega_ref.motor3 * ratio;
    omega_ref_4 = omega_ref.motor4 * ratio;
}


void mesCallback(const bot::quad& omega_mes)
{
    omega_1 = omega_mes.motor1 * ratio;
    omega_2 = omega_mes.motor2 * ratio;
    omega_3 = omega_mes.motor3 * ratio;
    omega_4 = omega_mes.motor4 * ratio;
}

void PIcontroller(Struct* cvs)
{
    ros::Time current_time = ros::Time::now();
    //Struct* cvs;
    
    double error_1 = omega_ref_1 - omega_1; // left speed error
    double error_2 = omega_ref_2 - omega_2;
    double error_3 = omega_ref_3 - omega_3;
    double error_4 = omega_ref_4 - omega_4; // right speed error
    printf("\n error_4 = %f",error_4);
    double int_error_1 = cvs->int_error_1; //left speed integrarion error
    double int_error_2 = cvs->int_error_2;
    double int_error_3 = cvs->int_error_3;
    double int_error_4 = cvs->int_error_4; //right speed integration error
    //printf("int_error_4 = %f",int_error_4);
    double dt = (current_time-old_time).toSec();
    //printf("dt = %f",dt);
    int_error_1 += dt*error_1;
    int_error_2 += dt*error_2;
    int_error_3 += dt*error_3;
    int_error_4 += dt*error_4;
    printf("\n int_error_4 = %f",int_error_4);
    old_time = current_time;
    cvs->int_error_1 = int_error_1;
    cvs->int_error_2 = int_error_2;
    cvs->int_error_3 = int_error_3;
    cvs->int_error_4 = int_error_4;
    
    //printf("int_error_1 = %f\n",cvs->int_error_1);
    double v1 = 0.02*error_1 + 0.1*int_error_1; // voltage command in [-24;24]
    double v2 = 0.02*error_2 + 0.1*int_error_2; // voltage command in [-24;24]
    double v3 = 0.02*error_3 + 0.1*int_error_3; // voltage command in [-24;24]
    double v4 = 0.02*error_4 + 0.1*int_error_4; // voltage command in [-24;24]
    printf("\n v4 = %f",v4);
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
    //printf("v4 = %f\n",v4);
    
    
    //cvs->wheel_commands1 = omega_ref_1 - omega_1;
    //cvs->wheel_commands2 = omega_ref_2 - omega_2;
    //cvs->wheel_commands3 = omega_ref_3 - omega_3;
    //cvs->wheel_commands4 = omega_ref_4 - omega_4;
    
    
    cvs->wheel_commands1 = v1;
    cvs->wheel_commands2 = v2;
    cvs->wheel_commands3 = v3;
    cvs->wheel_commands4 = v4;
    printf("\n wheel_command1 = %f",cvs->wheel_commands1);
}



int main(int argc, char **argv) {
    Struct* cvs;
    cvs = init_Struct();
    ros::init(argc, argv, "speedcontroler");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("omega_ref", 1, refCallback);
    ros::Subscriber sub2 = n.subscribe("omega_mes", 1, mesCallback);
    ros::Publisher pub = n.advertise<bot::quad>("omega_cmd", 1);
    ros::Rate loop_rate(1000);
    bot::quad command;
    

    while (ros::ok())
    {
        PIcontroller(cvs);
        command.motor1 = cvs->wheel_commands1;
        command.motor2 = cvs->wheel_commands2;
        command.motor3 = cvs->wheel_commands3;
        command.motor4 = cvs->wheel_commands4;
        
        pub.publish(command);
        ros::spinOnce();
        loop_rate.sleep();
    }

//    ros::spin(); //enters a loop calling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
    free_Struct(cvs); 
}

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "CtrlStruct_gr5.h"

void init_speed_controller(CtrlStruct* theCtrlStruct){

    theCtrlStruct->theUserStruct->t_old = theCtrlStruct->theCtrlIn->t;
    theCtrlStruct->theUserStruct->int_error_1 = 0;
    theCtrlStruct->theUserStruct->int_error_2 = 0;
    theCtrlStruct->theUserStruct->int_error_3 = 0;
    theCtrlStruct->theUserStruct->int_error_4 = 0;

}

double *Kp_Ki_Computation(double overshoot, double time_response)
{
    double *output = (double*) malloc(sizeof(double)*2);

    double Ra =5.84; // resistance de l'induit
    double La=(0.560e-3); // inductance de l'induit
    double kphi=37.83e-3;
    double J=0.58e-6;
    double Jrobot = 1.33e-5;
    double Kv=1.75e-5;
    double K = 1;

    double t_mechanical = (Jrobot)/Kv; // mechanical time constant
    double xsi = sqrt((log(overshoot)*log(overshoot))/((M_PI*M_PI)+ log(overshoot)*log(overshoot)));
    double wn = 4/(xsi*time_response);
    double Ki = ((wn*wn)*Kv*Ra*t_mechanical)/(K*kphi);
    double Kp =((2*xsi*wn)*(Ra*Kv*t_mechanical) - Ra*Kv)/(K*kphi);

    output[0] = Kp; // 14 is the reduction ratio
    output[1] = Ki;
    return output;

}

void speedControllerCallback(CtrlStruct* theCtrlStruct, double* omega_ref){

    double* out= Kp_Ki_Computation(0.05,0.02);
    double Kp = out[0]; // a recalculer
    double Ki = out[1]; // a recalculer
    double ratio = 19;
    //double vsat = 24;
    //double isat = 0.78;
    double v1, v2, v3, v4;
    /*CtrlIn *in = cvs->inputs;
    CtrlOut *out = cvs->outputs;*/
    double omega_ref_1 = omega_ref[ID_1] * ratio; // right motor reference speed
    double omega_ref_2 = omega_ref[ID_2] * ratio;
    double omega_ref_3 = omega_ref[ID_3] * ratio;
    double omega_ref_4 = omega_ref[ID_4] * ratio; // left motor reference speed
    double omega_1 = theCtrlStruct->theCtrlIn->wheel_1_speed * ratio; // left motor current speed
    double omega_2 = theCtrlStruct->theCtrlIn->wheel_2_speed * ratio;
    double omega_3 = theCtrlStruct->theCtrlIn->wheel_3_speed * ratio;
    double omega_4 = theCtrlStruct->theCtrlIn->wheel_4_speed * ratio; // right motor current speed
    double error_1 = omega_ref_1 - omega_1; // left speed error
    double error_2 = omega_ref_2 - omega_2;
    double error_3 = omega_ref_3 - omega_3;
    double error_4 = omega_ref_4 - omega_4; // right speed error
    double int_error_1 = theCtrlStruct->theUserStruct->int_error_1; //left speed integrarion error
    double int_error_2 = theCtrlStruct->theUserStruct->int_error_2;
    double int_error_3 = theCtrlStruct->theUserStruct->int_error_3;
    double int_error_4 = theCtrlStruct->theUserStruct->int_error_4; //right speed integration error
    int_error_1 += 0.01*error_1;
    int_error_2 += 0.01*error_2;
    int_error_3 += 0.01*error_3;
    int_error_4 += 0.01*error_4;
    theCtrlStruct->theUserStruct->int_error_1 = int_error_1;
    theCtrlStruct->theUserStruct->int_error_2 = int_error_2;
    theCtrlStruct->theUserStruct->int_error_3 = int_error_3;
    theCtrlStruct->theUserStruct->int_error_4 = int_error_4;
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

    theCtrlStruct->theCtrlOut->wheel_commands[ID_1] = v1;
    theCtrlStruct->theCtrlOut->wheel_commands[ID_2] = v2;
    theCtrlStruct->theCtrlOut->wheel_commands[ID_3] = v3;
    theCtrlStruct->theCtrlOut->wheel_commands[ID_4] = v4;

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "speedcontroler");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::Float32>("voltage_ref", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok()) //ok() returns false when ctfl-C, or other node kicks it out, or all nodes $
    {

        ros::Subscriber sub = n.subscribe("omega_ref", 1000, speedControllerCallback);
        ros::Subscriber sub = n.subscribe("omega_mes", 1000, speedControllerCallback);
        std_msgs::Float voltage_ref;
        chatter_pub.publish(voltage_ref); //here is the actual broadcast
        ros::spinOnce(); //important to call the callbacks
        loop_rate.sleep(); //puts node tu sleep to complete the 10Hz cycle

    }

    ros::spin(); //enters a loop calling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}
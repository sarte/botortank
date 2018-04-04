#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define wheel_radius 0.03
#define wheel_distance 0.225

ros::Time old_time(0.0);

//double omega=0.0;
//double vitesseX=0.0;
//double vitesseY=0.0;
//double dtheta=0.0;
//double dx=0.0;
//double dy=0.0;

double dt=0.0;
double v1=0.0;
double v2=0.0;
double v3=0.0;
double v4=0.0;

void odom(const bot::quad& omega_mes)
{
   ros::Time current_time = ros::Time::now();
   
   double v1=omega_mes.motor1*wheel_radius;
   double v2=omega_mes.motor2*wheel_radius;
   double v3=omega_mes.motor3*wheel_radius;
   double v4=omega_mes.motor4*wheel_radius;

   
   dt=(current_time-old_time).toSec();
   
   old_time=current_time;
   
   printf("temps = %f\n",dt);
     
   
   
//cvs->X+=1;
//	CtrlIn *ivs;
//	CtrlOut *ovs;
//	ivs = cvs->inputs;
//	ovs = cvs->outputs;
//	double omega;
//	double vitesse;
//	double theta;
//
//	double vL = (ivs->l_wheel_speed)*(wheel_radius);
//	double vR = (ivs->r_wheel_speed)*(wheel_radius);
//
//	vitesse = (vL+vR)/2;
//	omega = (vR-vL)/wheel_distance;
//	//printf("t_old = %f t = %f delta_t = %f\n",cvs->t_old,ivs->t,ivs->t-cvs->t_old);
//
//	//theta = cvs->theta + (cvs->team)*(omega+(cvs->omega))*delta_t/2;
//	theta = cvs->theta + (omega+(cvs->omega))*(ivs->t-cvs->t_old)/2;
//	cvs->X += (cvs->vitesse*cos(cvs->theta) + vitesse*cos(theta))*(ivs->t-cvs->t_old)/2;
//	cvs->Y	+= (cvs->vitesse*sin(cvs->theta) + vitesse*sin(theta))*(ivs->t-cvs->t_old)/2;
//	cvs->t_old = ivs->t;
//
//	//theta += ;
//	//printf("theta odometry2 = %f\n",theta);
//	if(theta>M_PI){
//		theta -= 2*M_PI;
//	}
//	else if(theta<(-M_PI)){
//		theta += 2*M_PI;
//	}
//	//printf("theta odometry1 = %f\n",theta);
//	cvs->theta = theta;
//	cvs->vitesse = vitesse;
//	cvs->omega = omega;
//	//cvs->t +=delta_t;

}




int main(int argc, char **argv) {
    ros::init(argc, argv, "odometry");
    ros::NodeHandle n;
//    ros::Publisher counter_pub = n.advertise<std_msgs::Int8>("counter",10);
    ros::Subscriber sub = n.subscribe("omega_mes",1000,odom);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("localisation_odom",50);
    ros::Rate loop_rate(100);

    double x=0;
    double y=0;
    double theta=0;
	
    geometry_msgs::Twist loc;

    while (ros::ok())
    {
		double omega = (v1+v2-v3-v4)/4;
		double vitesseX = (v1+v2+v3+v4)/4;
		double vitesseY = (v1-v2+v3-v4)/4;
		double dtheta = omega*dt;
		double dx = vitesseX*dt;
		double dy = vitesseY*dt;
		
        x+=dx;
        y+=dy;
        theta+=dtheta;
		
        if(theta>M_PI){
		theta -= 2*M_PI;
	    }
	    else if(theta<(-M_PI)){
		theta += 2*M_PI;
	    }
		
        loc.linear.x=x;
        loc.linear.y=y;
        loc.angular.z=theta;
		
        pub.publish(loc); //here is the actual broadcast
        ros::spinOnce(); //important to call the callbacks
        loop_rate.sleep(); //puts node tu sleep to complete the 10Hz cycle

    }

    ros::spin(); //enters a loop calling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

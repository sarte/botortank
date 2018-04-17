/*
 * Copyright (c) 2014, RoboPeak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 *  RoboPeak LIDAR System
 *  RPlidar ROS Node client test app
 *
 *  Copyright 2009 - 2014 RoboPeak Team
 *  http://www.robopeak.com
 *
 */


#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"
#include "bot/quad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RAD2DEG(x) ((x)*180./M_PI)

double dist1_opp = 0;
double dist2_opp = 0;
double angle1_opp = 0;
double angle2_opp = 0;
int f_edge = 0;
int r_edge = 0;
int deg90minus = 0;
int deg90plus = 0;
int iter = 0;
double X = 0;
double Y = 0;
double Xg = 0;
double Yg = 0;
double Thetag = 0;
double Xo = 0;
double Yo = 0;
double Thetao = 0;
bool teamchoice;
int stop = 0;
float scan_opp[360][2];
int mvt;

//float scan_opp2[360][2];
//float scan_filter[360][2];
int size = 0;
//int size = 0;
//int deg90minus = 0;
//int deg90plus = 0;



/*typedef struct Struct
{
    int size;
	float scan_opp[360][2];
    //double omega_ref_1,omega_ref_2,omega_ref_3,omega_ref_4;
    //double omega_1,omega_2,omega_3,omega_4;
    //int ratio;
} Struct;

Struct* init_Struct()
{
    Struct *cvs;
	cvs = (Struct*)malloc(sizeof(Struct));
	cvs->size = 0;

    // cvs->int_error_1 = 0;
    // cvs->int_error_2 = 0;
    // cvs->int_error_3 = 0;
    // cvs->int_error_4 = 0;
    // cvs->wheel_commands1 = 0;
    // cvs->wheel_commands2 = 0;
    // cvs->wheel_commands3 = 0;
    // cvs->wheel_commands4 = 0;
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
*/


void teamCallback(const std_msgs::Int8& move){
    mvt = move.data;
}

// void greenCallback(const geometry_msgs::Pose2D& pose){
    // Xg = pose.x;
    // Yg = pose.y;
    // Thetag = pose.theta;
// }
// void orangeCallback(const geometry_msgs::Pose2D& pose){
    // Xo = pose.x;
    // Yo = pose.y;
    // Thetao = pose.theta;
// }

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    //printf("Je commence\n");
    int count = scan->scan_time / scan->time_increment;
	int cnt = 0;
	int f_edge = 0;
	int r_edge = 0;

	size = 0;


    for(int i = 0; i < count; i++) {

        //cvs->scan_opp[i] = (double*)malloc(2*sizeof(double));

        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);

        if(scan->ranges[i] < 0.5  && scan->ranges[i] > 0.16){

            scan_opp[size][0] = degree;
            scan_opp[size][1] = scan->ranges[i];
            size++;
        }
    }
}


void opponent_filter(){

    if(mvt = 3){ //orange

        iter = 0;

        for(int j = 0; j<size ; j++){

            //X = Xo + (scan_opp[j][1]*cos(Thetao+scan_opp[j][0]));
            //Y = Yo + (scan_opp[j][1]*cos(Thetao+scan_opp[j][0]));

            if(scan_opp[j][0] < -90){

                //scan_opp2[iter][1] = scan_opp[j][1];
                //scan_opp2[iter][0] = scan_opp[j][0];
                iter++;

            }

        }
    }
    else
    {
        iter = 0;

        for(int j = 0; j<size ; j++){

            //X = Xg + (scan_opp[j][1]*cos(Thetag+scan_opp[j][0]));
            //Y = Yg + (scan_opp[j][1]*cos(Thetag+scan_opp[j][0]));

            if(scan_opp[j][0] > 90){

                //scan_opp2[iter][1] = scan_opp[j][1];
                //scan_opp2[iter][0] = scan_opp[j][0];
                iter++;
            }

        }
    }

    if(iter > 3){

        stop = 1;
    }

}



/////////////////////////////////////////////////////////////////////////////



int main(int argc, char **argv)
{

    ros::init(argc, argv, "opponent_domo");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("scan", 1, scanCallback);
    //ros::Subscriber sub2 = n.subscribe("origin_green",1,greenCallback);
    //ros::Subscriber sub3 = n.subscribe("origin_orange",1,orangeCallback);
    ros::Subscriber sub4 = n.subscribe("move",1,teamCallback);

    //ros::Publisher pub = n.advertise<bot::quad>("opponent",1);
    ros::Publisher pub2 = n.advertise<std_msgs::Int8>("opponent_homo",1);

	//bot::quad opponent;
    std_msgs::Int8 message_opp;

    ros::Rate loop_rate(100);


    while(ros::ok())
    {
        opponent_filter();
        //opponent.motor1 = dist1_opp;
		//opponent.motor2 = dist2_opp;
		//opponent.motor3 = angle1_opp;
		//opponent.motor4 = angle2_opp;

        message_opp.data = stop;

        pub2.publish(message_opp);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

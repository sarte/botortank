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

#include <iostream>
#include <fstream>

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
//float scan_opp2[360][2];
//float scan_filter[360][2];
int size = 0;
int insideCallabck = 0;
int insideOpponent = 0;
int flag2written = 0;
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


void teamCallback(const std_msgs::Bool& team){
    teamchoice = team.data;
}

void greenCallback(const geometry_msgs::Pose2D& pose){
    Xg = pose.x;
    Yg = pose.y;
    Thetag = pose.theta;
}
void orangeCallback(const geometry_msgs::Pose2D& pose){
    Xo = pose.x;
    Yo = pose.y;
    Thetao = pose.theta;
}

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
	if(flag2written == 0){
    //printf("Je commence\n");
    int count = scan->scan_time / scan->time_increment;
	int cnt = 0;
	int f_edge = 0;
	int r_edge = 0;
    insideCallabck += 1;
	size = 0;
    printf("In scan %i\n",count);
    std::fstream fichier;
    fichier.open("brut.txt",std::fstream::app|std::fstream::out);



    for(int i = 0; i < count; i++) {

        //cvs->scan_opp[i] = (double*)malloc(2*sizeof(double));

        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);

        //if(scan->ranges[i] < 0.5  && scan->ranges[i] > 0.16){
		if(scan->ranges[i] < 0.5){
            scan_opp[size][0] = degree;
            scan_opp[size][1] = scan->ranges[i];
            printf("call back distance = %f angle = %f,distance2 = %f angle2 = %f %i\n",scan->ranges[i],degree,scan_opp[size][0],scan_opp[size][1],insideCallabck);
            size++;
            fichier << "t:" << degree << " d:" << scan->ranges[i] << " \n";
        }
    }

    fichier.close();
	flag2written = 1;
	}

}


void opponent_filter(){

	if(flag2written == 1){

		std::fstream fichier;
    fichier.open("semi_brut.txt",std::fstream::app|std::fstream::out);

	for(int i = 0; i < size; i++) {

       fichier << "t:" << scan_opp[i][0] << " d:" << scan_opp[i][1] << " \n";

    }
	 fichier.close();
    double myAngle;
    double myDist;
    double myShift = Thetao*M_PI/180;
    double myShift2 =  Thetag*M_PI/180;

    if(teamchoice){ //orange
        stop = 0;
        iter = 0;
        insideOpponent +=1;
        printf("size = %i\n",size);
        //printf("In opponent\n");
        std::fstream fichier;
        fichier.open("map.txt",std::fstream::app|std::fstream::out);


        Thetao = Thetao*M_PI/180;
        for(int j = 0; j<size ; j++){
            //print("in the if")
            //scan_opp[j][0] = double  (scan_opp[j][0]/180.0)*M_PI;
            //printf("before distance = %f angle = %f Thetao = %f  %i\n",scan_opp[j][1],scan_opp[j][0],Thetao,insideOpponent);
            myAngle = scan_opp[j][0]*M_PI/180.0;
            myDist = scan_opp[j][1];
            //Thetao = double (Thetao/180)*M_PI;

            X = Xo + (scan_opp[j][1]*cos(myShift+myAngle));
            Y = Yo + (scan_opp[j][1]*sin(myShift+myAngle));
            //printf("Xo = %f Yo = %f\n",Xo,Yo);
             //printf("X = %f Y = %f\n",X,Y);
            //printf(" after distance = %f angle = %f Thetao = %f \n",scan_opp[j][1],scan_opp[j][0],Thetao);
            fichier << "X:" << X << " Y:" << Y << " \n";
            if((X<1.35)&&(X>-1.35)&&(Y<0.85)&&(Y>-0.70)){


                //scan_opp2[iter][1] = scan_opp[j][1];
                //scan_opp2[iter][0] = scan_opp[j][0];
                iter++;
                //printf(" iter = %i %f %f\n",iter,X,Y);
                fichier << "Xi:" << X << " Yi:" << Y << " \n";

            }


        }
        fichier.close();
    }
    else
    {
        stop = 0;
        iter = 0;

        for(int j = 0; j<size ; j++){
            myAngle = scan_opp[j][0]*M_PI/180.0;
            myDist = scan_opp[j][1];

            X = Xg + (scan_opp[j][1]*cos(myShift2+myAngle));
            Y = Yg + (scan_opp[j][1]*sin(myShift2+myAngle));

            if((X<1.35)&&(X>-1.35)&&(Y<0.85)&&(Y>-0.70)){

                //scan_opp2[iter][1] = scan_opp[j][1];
                //scan_opp2[iter][0] = scan_opp[j][0];
                iter++;
            }

        }
    }

    if(iter > 5){

        stop = 1;
    }

	flag2written =0;
	}

}



/////////////////////////////////////////////////////////////////////////////



int main(int argc, char **argv)
{

    ros::init(argc, argv, "opponent");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("scan", 1, scanCallback);
    ros::Subscriber sub2 = n.subscribe("origin_green",1,greenCallback);
    ros::Subscriber sub3 = n.subscribe("origin_orange",1,orangeCallback);
    ros::Subscriber sub4 = n.subscribe("team",1,teamCallback);

    //ros::Publisher pub = n.advertise<bot::quad>("opponent",1);
    ros::Publisher pub2 = n.advertise<std_msgs::Int8>("message_opp",1);

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
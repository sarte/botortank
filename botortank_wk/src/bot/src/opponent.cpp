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
#include "geometry_msgs/Twist.h"
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
//int size = 0;
//int deg90minus = 0;
//int deg90plus = 0;


void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    //printf("Je commence\n");
    int count = scan->scan_time / scan->time_increment;
	int cnt = 0;
	int size = 0;
	int f_edge = 0;
	int r_edge = 0;
	float scan_opp[360][2];
		
    for(int i = 0; i < count; i++) {
        
        //cvs->scan_opp[i] = (double*)malloc(2*sizeof(double));
        
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        
        if(scan->ranges[i] < 3.6  && scan->ranges[i] > 0.16 && ( (degree < 92) && (degree > -92) ) ){
            
            scan_opp[size][0] = degree;
            scan_opp[size][1] = scan->ranges[i];
            size++;
        }
    }
    dist1_opp = 0;
    angle1_opp = 0;
    dist2_opp = 0;
    angle2_opp = 0;
    
    for(int j = 1; j<size ; j++){
        printf("scan_opp = %f size = %i j = %i angle = %f\n",scan_opp[j][1],size,j,scan_opp[j][0]);
        if((scan_opp[j][1] < 0.5||scan_opp[j-1][1])){
            //printf("scan_opp_cond = %f\n",scan_opp[j][1]);
            printf("Difference fall = %f degree = %f\n",scan_opp[j][1]-scan_opp[j-1][1],scan_opp[j][0]);
            if(scan_opp[j][1]-scan_opp[j-1][1]>0.12){
                //Falling
                dist2_opp = scan_opp[j-1][1];
                angle2_opp = scan_opp[j-1][0];
            }
            if(scan_opp[j][1]-scan_opp[j-1][1]<-0.12){
                //Rising
                dist1_opp = scan_opp[j][1];
                angle1_opp = scan_opp[j][0];
            }
                
                //if((scan_opp[j][1]-scan_opp[j-1][1])>0){
                    //f_edge = j;
                    
                //}
                //if((scan_opp[j][1]-scan_opp[j-1][1])<0){
                    //r_edge = j;
                    
                //}
        }
    }
    
}
		
	
	
	
	  //(scan_opp[r_edge][0]/180)*M_PI;
	  //(scan_opp[f_edge][0]/180)*M_PI;
	
	

/////////////////////////////////////////////////////////////////////////////



int main(int argc, char **argv)
{
    ros::init(argc, argv, "opponent");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("scan", 1000, scanCallback);

    ros::Publisher pub = n.advertise<bot::quad>("opponent",10);
	
	bot::quad opponent;
	
    ros::Rate loop_rate(10);


    while(ros::ok())
    {
        opponent.motor1 = dist1_opp;
		opponent.motor2 = dist2_opp;
		opponent.motor3 = angle1_opp;
		opponent.motor4 = angle2_opp;
		
        pub.publish(opponent);
		
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

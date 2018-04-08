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

#define RAD2DEG(x) ((x)*180./M_PI)

double dist1_opp = 0;
double dist2_opp = 0;
double angle1_opp = 0;
double angle2_opp = 0;
//int size = 0;
//int deg90minus = 0;
//int deg90plus = 0;


void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int count = scan->scan_time / scan->time_increment;
	int cnt = 0;
	int size = 0;
	int f_edge = 0;
	int r_edge = 0;
	
		
	for(int i = 0; i < count; i++) {
		
		cvs->scan_opp[i] = (double*)malloc(2*sizeof(double));
		
		float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
		
		if(degree > 89.5 && degree < 90.5){
			deg90plus = i;
		}
		if(degree < -89.5 && degree > -90.5){
			deg90minus = i;
		}
		
		if(scan->ranges[i] < 3.6  && ( (degree < 92)||(degree > -92) ) ){
			
			cvs->scan_opp[i][0] = degree;
			cvs->scan_opp[i][1] = scan->ranges[i];
			size++;
		}
	}
	
	for(int j = 1; j<size-1 ; j++){
		
		if(cvs->scan_opp[j][1] < 0.5){
			if(fabs(cvs->scan_opp[j][1]-cvs->scan_opp[j-1][1])>0.3){
				
				if((cvs->scan_opp[j][1]-cvs->scan_opp[j-1][1])>0){
					f_edge = j;
				}
				if((cvs->scan_opp[j][1]-cvs->scan_opp[j-1][1])<0){
					r_edge = j;
				}
			}
		}
		
	}
	
	cvs->dist1_opp = cvs->scan_opp[r_edge][1];
	cvs->dist2_opp = cvs->scan_opp[f_edge][1];
	cvs->angle1_opp = (cvs->scan_opp[r_edge][0]/180)*M_PI;
	cvs->angle2_opp = (cvs->scan_opp[f_edge][0]/180)*M_PI;
	
	
}

/////////////////////////////////////////////////////////////////////////////



int main(int argc, char **argv)
{
    ros::init(argc, argv, "rplidar_node_client");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);

    ros::Publisher pub = n.advertise<bot::quad>("opponent",10);
	
	bot::quad opponent;


    while(ros::ok())
    {
        opponent.motor1 = cvs->dist1_opp;
		opponent.motor2 = cvs->dist1_opp;
		opponent.motor3 = cvs->angle1_opp;
		opponent.motor4 = cvs->angle2_opp;
		
        pub.publish(opponent);
		
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

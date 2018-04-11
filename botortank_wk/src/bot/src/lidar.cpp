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
double nearwall1 = 100;
double nearwall2 = 100;
double nearwall3 = 100;
double nearangle1 = 0;
double nearangle2 = 0;
double nearangle3 = 0;
double scan_lidar[360][2];
double corner[10][2];

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int count = scan->scan_time / scan->time_increment;
    int cnt = 0;
    int size = 0;
    float dx2 = 0;
    float dy2 = 0;
    float dx3 = 0;
    float dy3 = 0;
    float dx4 = 0;
    float dy4 = 0;
    float norme1 = 0;
    float norme2 = 0;
    float scalar = 0;
	
		
	for(int i = 0; i < count; i++) {
		
		//scan_lidar[i] = (double*)malloc(2*sizeof(double));
		
		float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
		
		// if(degree > 89.5 && degree < 90.5){
			// deg90plus = i;
		// }
		// if(degree < -89.5 && degree > -90.5){
			// deg90minus = i;
		// }
		
		if(scan->ranges[i] < 3.6  && ( (degree > 88)||(degree < -88) ) ){
			
			scan_lidar[i][0] = degree;
			scan_lidar[i][1] = scan->ranges[i];
            //printf("ranges = %f\n",scan_lidar[i][1]);
			size++;
		}
	}
	//printf("size = %i",size);
	
	for(int j = 3; j<size-3 ; j++){
        printf("angle = %f cos = %f\n",scan->angle_increment,cos(scan->angle_increment));
		
		dx2 = scan_lidar[j-2][1]*cos(scan->angle_increment) - scan_lidar[j-3][1];
		dy2 = scan_lidar[j-2][1]*sin(scan->angle_increment);
        printf("dx2 = %f dy2 = %f\n",dx2,dy2);
		dx3 = scan_lidar[j-1][1]*cos(2*(scan->angle_increment)) - scan_lidar[j-3][1];
		dy3 = scan_lidar[j-1][1]*sin(2*(scan->angle_increment));
		printf("dx3 = %f dy3 = %f\n",dx3,dy3);
		dx4 = scan_lidar[j][1]*cos(3*(scan->angle_increment)) - scan_lidar[j-3][1];
		dy4 = scan_lidar[j][1]*sin(3*(scan->angle_increment));
		printf("dx4 = %f dy4 = %f\n",dx4,dy4);
		norme1 = sqrt(dx2*dx2+dy2*dy2);
		norme2 = sqrt((dx4-dx3)*(dx4-dx3)+(dy4-dy3)*(dy4-dy3));
        printf("norme1 = %f norme2 = %f\n",norme1,norme2);
		
		scalar = (dx2/norme1)*((dx4-dx3)/norme2) + (dy2/norme1)*((dy4-dy3)/norme2);
        printf("scalar = %f\n",scalar);
		
		if(fabs(scalar) < 0.22){
			
            printf("corner i = %i\n",j);
			
			corner[cnt][0] = j-2;
			corner[cnt][1] = j-1;
			cnt++;
		}
	}
	
	for(int i=0 ; i < corner[0][0] ; i++ ){
		
		if(scan_lidar[i][1] < nearwall1){
			nearwall1 = scan_lidar[i][1];
			nearangle1 = scan_lidar[i][0];
		}
	}
	for(int i=corner[0][1] ; i < corner[1][0] ; i++ ){
		
		if(scan_lidar[i][1] < nearwall2){
			nearwall2 = scan_lidar[i][1];
			nearangle2 = scan_lidar[i][0];
		}
	}
	for(int i=corner[1][1] ; i < size ; i++ ){
		
		if(scan_lidar[i][0] < nearwall3){
			nearwall3 = scan_lidar[i][1];
			nearangle3 = scan_lidar[i][0];
		}
	}
	
	
}

/////////////////////////////////////////////////////////////////////////////


// typedef struct Struct
// {
    // double nearwall1, nearwall2, nearwall3;
	// double nearangle1, nearangle2, nearangle3;
	// double** scan_lidar;
	// double** corner;
	// double dx2, dx3, dx4, dy2, dy3, dy4;
	// double scalar;
	// double norme1, norme2;
	// int deg90minus, deg90plus;
	
// } Struct;

// Struct* init_Struct()
// {
    // Struct *cvs;
    // cvs = (Struct*)malloc(sizeof(Struct));
    // cvs->nearangle1 = 0;
    // cvs->nearangle2 = 0;
    // cvs->nearangle3 = 0;
    // cvs->nearwall1 = 100;
    // cvs->nearwall2 = 100;
    // cvs->nearwall3 = 100;
	// cvs->scan_lidar = (double**)malloc(360*sizeof(double*));
	// cvs->corner = (double**)malloc(2*sizeof(double*));
	// cvs->dx2 = 0;
	// cvs->dy2 = 0;
	// cvs->dx3 = 0;
	// cvs->dy3 = 0;
	// cvs->dx4 = 0;
	// cvs->dy4 = 0;
	// cvs->norme1 = 0;
	// cvs->norme2 = 0;
	// cvs->scalar = 0;
	// cvs->deg90minus = 0;
	// cvs->deg90plus = 0;

 
    
    // return cvs;
    
// }

// void free_Struct(Struct *cvs)
// {
    // free(cvs);
// }


int main(int argc, char **argv)
{
	//Struct *cvs;
	//cvs = init_Struct();
    ros::init(argc, argv, "lidar");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
	
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("wall_dist",10);
	
	
    ros::Rate loop_rate(10);
	
	geometry_msgs::Twist wall_dist;


    while(ros::ok())
    {
		
        wall_dist.linear.x = nearwall1;
		wall_dist.linear.y = nearwall2;
		wall_dist.linear.z = nearwall3;
		wall_dist.angular.x = nearangle1;
		wall_dist.angular.y = nearangle2;
		wall_dist.angular.z = nearangle3;
		
        pub.publish(wall_dist);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

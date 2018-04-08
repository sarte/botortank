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

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int count = scan->scan_time / scan->time_increment;
	int cnt = 0;
	int size = 0;
	//double dx2 = 0;
	//double dy2 = 0;
	//double dx3 = 0;
	//double dy3 = 0;
	//double dx4 = 0;
	//double dy4 = 0;
	//double norme1 = 0;
	//double norme2 = 0;
	//double scalar = 0;
	
		
	for(int i = 0; i < count; i++) {
		
		cvs->scan_lidar[i] = (double*)malloc(2*sizeof(double));
		
		float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
		
		if(degree > 89.5 && degree < 90.5){
			cvs->deg90plus = i;
		}
		if(degree < -89.5 && degree > -90.5){
			cvs->deg90minus = i;
		}
		
		if(scan->ranges[i] < 3.6  && ( (degree > 88)||(degree < -88) ) ){
			
			cvs->scan_lidar[i][0] = degree;
			cvs->scan_lidar[i][1] = scan->ranges[i];
			size++;
		}
	}
	
	for(int j = 3; j<size-3 ; j++){
		
		cvs->dx2 = cvs->scan_lidar[j-2][0]*cos(scan->angle_increment) - cvs->scan_lidar[j-3][0];
		cvs->dy2 = cvs->scan_lidar[j-2][0]*sin(scan->angle_increment);
		
		cvs->dx3 = cvs->scan_lidar[j-1][0]*cos(2*(scan->angle_increment)) - cvs->scan_lidar[j-3][0];
		cvs->dy3 = cvs->scan_lidar[j-1][0]*sin(2*(scan->angle_increment));
		
		cvs->dx4 = cvs->scan_lidar[j][0]*cos(3*(scan->angle_increment)) - cvs->scan_lidar[j-3][0];
		cvs->dy4 = cvs->scan_lidar[j][0]*sin(3*(scan->angle_increment));
		
		cvs->norme1 = sqrt(cvs->dx2*cvs->dx2+cvs->dy2*cvs->dy2); 
		cvs->norme2 = sqrt((cvs->dx4-cvs->dx3)*(cvs->dx4-cvs->dx3)+(cvs->dy4-cvs->dy3)*(cvs->dy4-cvs->dy3)); 
		
		cvs->scalar = (cvs->dx2/cvs->norme1)*((cvs->dx4-cvs->dx3)/cvs->norme2) + (cvs->dy2/cvs->norme1)*((cvs->dy4-cvs->dy3)/cvs->norme2);
		
		if(cvs->scalar < 0.22){
			cvs->corner[cnt][0] = j-2;
			cvs->corner[cnt][1] = j-1;
			cnt++;
		}
	}
	
	for(i=0 ; i < cvs->corner[0][0] ; i++ ){
		
		if(cvs->scan_lidar[i][1] < cvs->nearwall1){
			cvs->nearwall1 = cvs->scan_lidar[i][1];
			cvs->nearangle1 = cvs->scan_lidar[i][0];
		}
	}
	for(i=cvs->corner[0][1] ; i < cvs->corner[1][0] ; i++ ){
		
		if(cvs->scan_lidar[i][1] < cvs->nearwall2){
			cvs->nearwall2 = cvs->scan_lidar[i][1];
			cvs->nearangle2 = cvs->scan_lidar[i][0];
		}
	}
	for(i=cvs->corner[1][1] ; i < size ; i++ ){
		
		if(cvs->scan_lidar[i][0] < cvs->nearwall3){
			cvs->nearwall3 = cvs->scan_lidar[i][1];
			cvs->nearangle3 = cvs->scan_lidar[i][0];
		}
	}
	
	
}

/////////////////////////////////////////////////////////////////////////////


typedef struct Struct
{
    double nearwall1, nearwall2, nearwall3;
	double nearangle1, nearangle2, nearangle3;
	double** scan_lidar;
	double** corner;
	double dx2, dx3, dx4, dy2, dy3, dy4;
	double scalar;
	double norme1, norme2;
	int deg90minus, deg90plus;
	
} Struct;

Struct* init_Struct()
{
    Struct *cvs;
    cvs = (Struct*)malloc(sizeof(Struct));
    cvs->nearangle1 = 0;
    cvs->nearangle2 = 0;
    cvs->nearangle3 = 0;
    cvs->nearwall1 = 100;
    cvs->nearwall2 = 100;
    cvs->nearwall3 = 100;
	cvs->scan_lidar = (double**)malloc(360*sizeof(double*));
	cvs->corner = (double**)malloc(2*sizeof(double*));
	cvs->dx2 = 0;
	cvs->dy2 = 0;
	cvs->dx3 = 0;
	cvs->dy3 = 0;
	cvs->dx4 = 0;
	cvs->dy4 = 0;
	cvs->norme1 = 0;
	cvs->norme2 = 0;
	cvs->scalar = 0;
	cvs->deg90minus = 0;
	cvs->deg90plus = 0;

 
    
    return cvs;
    
}

void free_Struct(Struct *cvs)
{
    free(cvs);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "rplidar_node_client");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
	
	ros::Publisher pub = n.advertise<bot::Wall>("wall_dist",10);
	
	bot::Wall wall_dist;


    while(ros::ok())
    {
        wall_dist.dist1 = cvs->nearwall1;
		wall_dist.dist2 = cvs->nearwall2;
		wall_dist.dist3 = cvs->nearwall3;
		wall_dist.dist3 = cvs->nearangle1;
		wall_dist.dist3 = cvs->nearangle2;
		wall_dist.dist3 = cvs->nearangle3;
		
        pub.publish(wall_dist);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose2D.h"
#include "bot/quad.h"
#include "bot/lidar_array.h"
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

double deltaX = 0;
double deltaY = 0;

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
float ennem_list[360][2];
int size = 0;
int insideCallabck = 0;
int insideOpponent = 0;
int flag2written = 0;


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
        int count = scan->scan_time / scan->time_increment;
    	int cnt = 0;
    	int f_edge = 0;
    	int r_edge = 0;
        insideCallabck += 1;
    	size = 0;

        for(int i = 0; i < count; i++) {
            float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
    		if(scan->ranges[i] < 0.5){
                scan_opp[size][0] = degree;
                scan_opp[size][1] = scan->ranges[i];
                size++;
            }
        }
	   flag2written = 1;
	}

}


void opponent_filter(){

	if(flag2written == 1){

    double myAngle;
    double myDist;
    double myShift = Thetao*M_PI/180;
    double myShift2 =  Thetag*M_PI/180;

    if(teamchoice){ //orange
        stop = 0;
        iter = 0;
        insideOpponent +=1;
        Thetao = Thetao*M_PI/180;

        for(int j = 0; j<size ; j++){

            myAngle = scan_opp[j][0]*M_PI/180.0;
            myDist = scan_opp[j][1];

            X = Xo + (scan_opp[j][1]*cos(myShift+myAngle));
            Y = Yo + (scan_opp[j][1]*sin(myShift+myAngle));
           
            if((X<1.35)&&(X>-1.35)&&(Y<0.85)&&(Y>-0.70))
            {
                // ennem_list[iter][0] = X;
                // ennem_list[iter][1] = Y;
                // deltaX = Xo - X;
                // deltaY = Yo - Y;
                // ennem_list[iter][0] = sqrt(deltaX*deltaX + deltaY*deltaY);
                // ennem_list[iter][1] = atan(deltaY/deltaX);
                // if(deltaX<0 && deltaY>0 && ennem_list[iter][1]<0)
                // {
                //     ennem_list[iter][1] += M_PI;
                // }
                // if(ennem_list[iter][1]<0 && deltaY<0 && ennem_list[iter][1]>0)
                // {
                //     ennem_list[iter][1] -= M_PI;
                // }
                ennem_list[iter][0] = myAngle; // rad
                ennem_list[iter][1] = myDist;

                    iter++;
            }
        }
    }
    else
    {
        stop = 0;
        iter = 0;

        for(int j = 0; j<size ; j++)
        {
            myAngle = scan_opp[j][0]*M_PI/180.0;
            myDist = scan_opp[j][1];

            X = Xg + (scan_opp[j][1]*cos(myShift2+myAngle));
            Y = Yg + (scan_opp[j][1]*sin(myShift2+myAngle));

            if((X<1.35)&&(X>-1.35)&&(Y<0.85)&&(Y>-0.70))
            {
                //deltaX = X - Xg;
                //deltaY = Y - Yg;
                //ennem_list[iter][0] = sqrt(deltaX*deltaX + deltaY*deltaY);
                //ennem_list[iter][1] = atan(deltaY/deltaX);
                //if(deltaX<0 && deltaY>0 && ennem_list[iter][1]<0)
                //{
                //    ennem_list[iter][1] += M_PI;
                //}
                //if(ennem_list[iter][1]<0 && deltaY<0 && ennem_list[iter][1]>0)
                //{
                //    ennem_list[iter][1] -= M_PI;
                //}
                ennem_list[iter][0] = myAngle; // rad
                ennem_list[iter][1] = myDist;
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
    ros::Publisher pub2 = n.advertise<bot::lidar_array>("message_opp",1);

	//bot::quad opponent;
    bot::lidar_array message_opp;

    ros::Rate loop_rate(100);


    while(ros::ok())
    {
        opponent_filter();
        message_opp.iter = iter;
          for (int i=0; i < iter; i++) {
            message_opp.angles[i] = ennem_list[i][0];
            message_opp.distances[i] = ennem_list[i][1];
          }

        pub2.publish(message_opp);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

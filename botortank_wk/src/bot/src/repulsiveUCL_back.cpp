#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float64MultiArray.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
#include "bot/quad.h"
#include "bot/lidar_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double forceX = 0;
double forceY = 0;
double deltaX = 0;
double deltaY = 0;
double force = 0;

bool teamchoice = 0;
double Xg = 0;
double Yg = 0;
double Thetag = 0;
double Xo = 0;
double Yo = 0;
double Thetao = 0;

double dist = 0;
double angle = 0;

int signX = 0;
int signY = 0;

float ennem_list [360][2];
double iter = 0;

//double fmax = 100; // a modifier
double fwall = 100;
double f_point = 0;

double force_repX = 0;
double force_repY = 0;

double eta = 1;
double rho = 0.5;

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



void Callback1(const bot::lidar_array& opp)
{
        iter = opp.iter;
        for (int i=0; i < iter; i++) {
        ennem_list[i][0] = opp.angles[i];
        ennem_list[i][1] = opp.distances[i];
        }

}

void forcerep() 
{
    force_repX = 0;
    force_repY = 0;
    forceX = 0;
    forceY = 0;
    f_point = 1 / iter;


    if(teamchoice){

        //Opponent
        for (int i = 0; i < iter; ++i)
        {
            force = eta*((1/ennem_list[i][1])-(1/rho))*(1/ennem_list[i][1])*(1/ennem_list[i][1]);
            forceX -= f_point*force*cos(ennem_list[i][0]-Thetao);
            forceY -= f_point*force*sin(ennem_list[i][0]-Thetao);
        }
        force = sqrt((forceX*forceX)+(forceY*forceY));
        angle = atan(forceY/forceX);
        printf("Force norm %f\n", force);
        printf("Force angl %f\n", angle);

        if(forceX<0 && forceY>0 && angle<0)
        {
            angle += M_PI;
        }
        if(forceX<0 && forceY<0 && angle>0)
        {
            angle -= M_PI;
        }

        if(force > 20)
        {
            force = 20;
        }
        if(force < -20)
        {
            force = -20;
        }

        forceX = force*cos(angle);
        forceY = force*sin(angle);
    

        //Walls
        // if(Xo>1.35 || Xo < -1.35 || Yo > 0.85 || Yo < -0.85)
        // {
        //     if(Xo<0){
        //         signX = -1;

        //     }
        //     else {
        //         signX = 1;
        //     }
        //     if(Yo<0){
        //         signY =  -1;

        //     }
        //     else {
        //         signY = 1;
        //     }

        //     force_repX += -signX * fwall * min((Xo - 1.35),(Xo + 1.35));
        //     force_repY += -signY * fwall * min((Yo - 0.85),(Yo + 0.85));
        // }

    }
    else {
        //Opponent
        for (int i = 0; i < iter; ++i)
        {
            force = eta*((1/ennem_list[i][1])-(1/rho))*(1/ennem_list[i][1])*(1/ennem_list[i][1]);
            forceX -= f_point*ennem_list[i][1]*cos(ennem_list[i][0]-Thetag);
            forceY -= f_point*ennem_list[i][1]*sin(ennem_list[i][0]-Thetag);
        }
        force = sqrt((forceX*forceX)+(forceY*forceY));
        angle = atan(forceY/forceX);

        if(forceX<0 && forceY>0 && angle<0)
        {
            angle += M_PI;
        }
        if(forceX<0 && forceY<0 && angle>0)
        {
            angle -= M_PI;
        }

        if(force > 20)
        {
            force = 20;
        }
        if(force < -20)
        {
            force = -20;
        }

        forceX = force*cos(angle);
        forceY = force*sin(angle);

        //Walls
        // if(Xo>1.35 || Xo < -1.35 || Yo > 0.85 || Yo < -0.85)
        // {
        //     if(Xg<0){
        //         signX = -1;

        //     }
        //     else {
        //         signX = 1;
        //     }
        //     if(Yg<0){
        //         signY =  -1;

        //     }
        //     else {
        //         signY = 1;
        //     }

        //     force_repX += -signX * fwall * min((Xg - 1.35),(Xg + 1.35));
        //     force_repY += -signY * fwall * min((Yg - 0.85),(Yg + 0.85));
        // }
    }
	
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "repulsive");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("message_opp", 10, Callback1);
    ros::Subscriber sub2 = n.subscribe("origin_green",1,greenCallback);
    ros::Subscriber sub3 = n.subscribe("origin_orange",1,orangeCallback);
    ros::Subscriber sub4 = n.subscribe("team",1,teamCallback);
    ros::Publisher pub = n.advertise<geometry_msgs::Point>("force_rep",10);
    ros::Rate loop_rate(100);
	
    geometry_msgs::Point force;
	
    while(ros::ok())
    {
        forcerep();
        force.x = forceX;
		force.y = forceY;
        pub.publish(force);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

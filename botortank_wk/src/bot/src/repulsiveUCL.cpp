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
double angle2 = 0;

int signX = 0;
int signY = 0;

float ennem_list [360][2];
double iter = 0;

//double fmax = 100; // a modifier
double fwall = 100;
double f_point = 0;

double force_repX = 0;
double force_repY = 0;

double eta = 0;
double rho = 0;

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
//        printf("iter %f",iter);
        for (int i=0; i < iter; i++) {
            ennem_list[i][0] = opp.angles[i];
            ennem_list[i][1] = opp.distances[i];
//            printf("\nennem_list angles (deg) : %f dist : %f\n",ennem_list[i][0] * 180.0 / M_PI, ennem_list[i][1]);
        }
}

void forcerep() 
{
    force_repX = 0;
    force_repY = 0;
    forceX = 0;
    forceY = 0;
    f_point = 1 / iter;
//    printf("starting forcerep\n");


    if(teamchoice){

        //Opponent
        for (int i = 0; i < iter; ++i)
        {
            if(ennem_list[i][1]>0.15 && ennem_list[i][1] < rho){
                force = eta*((1/ennem_list[i][1])-(1/rho))*(1/ennem_list[i][1])*(1/ennem_list[i][1]);
                forceX -= f_point*force*cos(ennem_list[i][0]);
                forceY -= f_point*force*sin(ennem_list[i][0]);
            }
            else{
                forceX -= 0;
                forceY -= 0;
            }

        }

        force = sqrt((forceX*forceX)+(forceY*forceY));
        force = std::min(std::max(force, -10.0), 10.0); //saturation
        angle = atan2(forceY,forceX); //quadrant finder
//        printf("test3\nforce %f angle %f \nforceX %f forceY %f \n", force, angle, forceX, forceY);

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
            if(ennem_list[i][1]>0.15 && ennem_list[i][1]<rho){
                force = eta*((1/ennem_list[i][1])-(1/rho))*(1/ennem_list[i][1])*(1/ennem_list[i][1]);
                forceX -= f_point*force*cos(ennem_list[i][0] );
                forceY -= f_point*force*sin(ennem_list[i][0] );
            }
            else{
                forceX -= 0;
                forceY -= 0;
            }

        }

        force = sqrt((forceX*forceX)+(forceY*forceY));
        force = std::min(std::max(force, -15.0), 15.0); //saturation
        angle = atan2(forceY,forceX); //quadrant finder
//        printf("test3\nforce %f angle %f \nforceX %f forceY %f \n", force, angle, forceX, forceY);

        forceX = force*cos(angle);
        forceY = force*sin(angle);

//        printf("forceX %f forceY %f \n\n", forceX, forceY);



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
    int lr = 0;
    ros::init(argc, argv, "repulsive");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("message_opp", 10, Callback1);
    ros::Subscriber sub2 = n.subscribe("origin_green",1,greenCallback);
    ros::Subscriber sub3 = n.subscribe("origin_orange",1,orangeCallback);
    ros::Subscriber sub4 = n.subscribe("team",1,teamCallback);
    ros::Publisher pub = n.advertise<geometry_msgs::Point>("force_rep",10);

    ros::NodeHandle nh_private("~");
    nh_private.param<double>("eta", eta, 0.75);
    nh_private.param<double>("rho", rho, 0.8);
    nh_private.param<int>("loop_rate", lr, 100);
    ros::Rate loop_rate(lr);

    printf("repulsiveUCL eta: %f\n", eta);
    printf("repulsiveUCL rho: %f\n", rho);
    printf("repulsiveUCL lr : %i\n", lr);
	
    geometry_msgs::Point force;
	
    while(ros::ok())
    {
        forcerep();
        force.x = -forceX;
		force.y = -forceY;
        ROS_INFO("repulsiveUCL x: %f y: %f \n", force.x, force.y);
//        printf("force x: %f\n", force.x);
//        printf("force y: %f\n", force.y);
        pub.publish(force);
        ros::spinOnce();
        loop_rate.sleep();
    }

    // subscribe to the chatter topic with master. ROS will call chattercallback whenever a new msg arrives
   // ros::spin(); //enters a loop callling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
}

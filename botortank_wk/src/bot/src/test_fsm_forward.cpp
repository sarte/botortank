#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int8.h"
#include "geometry_msgs/Twist.h"
#include "bot/quad.h"
#include "bot/tetra.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "geometry_msgs/Pose2D.h"
#include <string>
using namespace std;



#define RAD2DEG(x) ((x)*180./M_PI)

bool team;
double pos_X =0;
double pos_Y = 0;
double pos_theta = 0;
double pos_X_G =0;
double pos_Y_G =0;
double pos_theta_G=0;
double pos_X_O=0;
double pos_Y_O=0;
double pos_theta_O=0;
double dist = 69;
double deltaX = 0;
double deltaY = 0;
int t=0;
int flagstart;
int start = 0;
int feedback;
int dyna=0;
int enable_shooting=0;
int follow=0;
int cnt=0;
//string feedback;
//string dyna;


/////////////////////////////////////////////////////////////////////

typedef enum States
{
	STANDBY, START, DOMO1, DOMO2, BALL1, BALL2, BALL3, BALL4, GO_SHOOT, TURN_SHOOT, SHOOT, GO_BEE1,GO_BEE2, TURN_BEE, BEE, PUSH_BEE
	//STANDBY, START, CAL_X, CAL_Y, HOME, TARG, VIA1, VIA2
} States;

typedef struct Struct
{
    double targetX, targetY;
    int move;//0rien,1attraction,2rotation,3hardcode avant, 4arriere,5gauche,6droite
    int team;
    int enable_rotation;//0 tournepas,1positif,-1 negatif
	//int enable_hardcode;//0rien,1attraction,2rotation,3hardcode temps
	States state;
	States prevstate;

    //double omega_ref_1,omega_ref_2,omega_ref_3,omega_ref_4;
    //double omega_1,omega_2,omega_3,omega_4;
    //int ratio;
} Struct;

Struct* init_Struct()
{
    Struct *cvs;
	cvs = (Struct*)malloc(sizeof(Struct));
	cvs->state = DOMO2;
	cvs->prevstate = DOMO2;
	cvs->targetX = 0;
	cvs->targetY = 0;
	cvs->move = 0;
	cvs->enable_rotation=0;
	cvs->team=0;

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


/////////////////////////////////////////////////////////////////////////




void Callback_opp(const std_msgs::Bool& teamdata)
{
    team = teamdata.data;
}

void Callback_team(const std_msgs::Int8& message)
{
    stop_message = message.data;
}

void Callback_lidar_g(const geometry_msgs::Pose2D& localisation_lidar)
{
    pos_X_G = localisation_lidar.x;
    pos_Y_G = localisation_lidar.y;
    pos_theta_G = localisation_lidar.theta;
}

void Callback_lidar_o(const geometry_msgs::Pose2D& localisation_lidar)
{
    pos_X_O = localisation_lidar.x;
    pos_Y_O = localisation_lidar.y;
    pos_theta_O = localisation_lidar.theta;
}


void Callback_feedback(const std_msgs::Int8& dyna_feedback)
{
    feedback = dyna_feedback.data;

}


void Callback_follow(const bot::tetra& blackline)
{
    follow= (blackline.a || blackline.b || blackline.c || blackline.d) ;
}

void Callback_start(const std_msgs::Bool& startdata)
{
    start=startdata.data;
}

///////////////////////////////////////////////////////////////////////////////

void FSM(Struct* cvs)
{
    if(start=1 && !flagstart)
    {
        flagstart=1;
        cvs->state= START;

    }
    // if (cvs->team){
        // pos_X= pos_X_O;
		// pos_Y=pos_Y_O;
		// pos_theta=pos_theta_G;

    // }
    // else{
        // pos_X=pos_X_G;
        // pos_Y=pos_Y_G;
        // pos_theta=pos_theta_G;
    // }
    // if(t>9800)
    // {
        // cvs->prevstate = cvs->state;
        // cvs->state = STANDBY;
    // }
	switch(cvs->state){

		case STANDBY:
        printf("STANDBY\n");


            cvs->move=0;
            cvs->prevstate = cvs->state;
            cvs->state = STANDBY;
        break;


		 case START:
			 //choose team
			 //nextstate
			 if(team == 1){
				 cvs->team = 1;

			 }
			 else{
				 cvs->team = 0;
			 }

			 cvs->prevstate = cvs->state;
			 cvs->state = DOMO1;
			 t++;

			 break;

		case DOMO1:

			if(stop_message == 1){

				cvs->move =0;

			}
			else{

				if(cvs->team){
					cvs->move =6 ;
				}
				else{
					cvs->move =6 ;
				}

				if(follow&& t>500){

					cvs->move = 0;
					cvs->prevstate = cvs->state;
					cvs->state = DOMO2;
				}
			}

			t++;

			break;

		case DOMO2://reecrire en fonction du temps

			if(message_stop==1){
				cvs->move = 0;

			}
			else{
				cnt++;

				if(cnt > 700){

					cvs->move=0;
					cvs->prevstate = cvs->state;
					cvs->state = GO_BEE1;
				}
				else{
					if(team){
						cvs->move=4;
					}
					else{
						cvs->move=3;
					}
				}
			}

			t++;

			break;

        case GO_BEE1:

			if(message_stop==1){

				cvs->move = 0;

			}
			else{

				if(cvs->team){
					cvs->move=3;
				}

				else{
					cvs->move = 4;
				}


				//deltaX = cvs->targetX - pos_X;
				//deltaY = cvs->targetY - pos_Y;
				//dist = sqrt(deltaX*deltaX + deltaY*deltaY);
				cnt++;

				if(cnt>700){

					cvs->move = 0;
					cnt=0;
					cvs->prevstate = cvs->state;
					cvs->state = STANDBY;
				}
			}

			t++;

			break;


        case GO_BEE2:

			if(cvs->team){
                cvs->targetX =1.3 ;
                cvs->targetY =-0.8 ;
			}

			else{
                cvs->targetX =-1.3 ;
                cvs->targetY = -0.8;
			}


			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist<0.03){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = STANDBY;
			}
			else{

				cvs->move = 1;
			}
			t++;

			break;

        case TURN_BEE:

			if(cvs->team){
                cvs->enable_rotation=1;
                if(pos_theta <-178   ||  pos_theta > 178  ){

                    cvs->move = 0;
                    cvs->prevstate = cvs->state;
                    cvs->state = GO_BEE2;
                    cvs->enable_rotation=0;
                }
                else{

                    cvs->move = 2;
                }
			}
			else{
                cvs->enable_rotation=-1;

                if(pos_theta <2   &&  pos_theta > -2  ){

                    cvs->move = 0;
                    cvs->prevstate = cvs->state;
                    cvs->state = GO_BEE2;
				cvs->enable_rotation=0;
                }
                else{

				cvs->move = 2;
                }
			}
			t++;

			break;

		case BEE:

			dyna = 3;
			cvs->prevstate = cvs->state;
            cvs->state = PUSH_BEE;
			t++; //bee

			break;

        case PUSH_BEE:

			dyna=0;
			if(team){
                cvs->targetX =0 ;
                cvs->targetY = 0;
			}
			else{
                cvs->targetX = 0;
                cvs->targetY = 0;
			}

			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist<0.03){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = STANDBY;
			}
			else{

				cvs->move = 1;
			}
			t++;

			break;

		case BALL1:

			if(team){
                cvs->targetX = 0;
                cvs->targetY = 0;
			}
			else{
                cvs->targetX = 0;
                cvs->targetY = 0;
			}

			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist < 0.03){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = BALL2;
			}
			else{

				cvs->move = 1;
			}
			t++;

			break;

		case BALL2:

			if(team){
                cvs->targetX = 0;
                cvs->targetY = 0;
			}
			else{
                cvs->targetX = 0;
                cvs->targetY = 0;
			}

			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist < 0.03){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = BALL3;
			}
			else{

				cvs->move = 1;
			}
			t++;
			break;

		case BALL3:

			cvs->targetX = 0;
			cvs->targetY =0 ;

			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist < 0.03){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = BALL4;
			}
			else{

				cvs->move = 3;
			}
			t++;

			break;

        case BALL4:

			dyna = 4; //ball;

            if(feedback == 4){
                dyna=0;
				cvs->prevstate = cvs->state;
				cvs->state = GO_SHOOT;
            }

			t++;

			break;

		case GO_SHOOT:

			if(team){
                cvs->targetX =0 ;
                cvs->targetY = 0;
			}
			else{
                cvs->targetX = 0;
                cvs->targetY = 0;
			}

			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist < 0.03){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = TURN_SHOOT;
			}
			else{

				cvs->move = 1;
			}
			t++;

			break;

		case TURN_SHOOT:

			if(cvs->team){
                cvs->enable_rotation=0;
			}
			else{
                cvs->enable_rotation=0;
			}

			if(pos_theta < 90  && pos_theta > 90  ){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = SHOOT;
			}
			else{

				cvs->move = 2;
			}
			t++;

			break;

		case SHOOT:

				dyna = 1; //sorting1
				enable_shooting=1;

				if(feedback == 1){
                    dyna=0;
                    enable_shooting=0;
					cvs->prevstate = cvs->state;
					cvs->state = STANDBY;
				}
				t++;


			break;


	}

}

////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv) {
    Struct* cvs;
    cvs = init_Struct();
    ros::init(argc, argv, "test_fsm_forward");
    ros::NodeHandle n;
    //ros::Subscriber sub1 = n.subscribe("team", 1, Callback_team);
    ros::Subscriber sub1 = n.subscribe("origin_green", 1, Callback_lidar_g);
    ros::Subscriber sub5 = n.subscribe("origin_orange",1,Callback_lidar_o);
    ros::Subscriber sub2 = n.subscribe("dyna_feedback", 1, Callback_feedback);
    ros::Subscriber sub3 = n.subscribe("blackline", 1, Callback_follow);
    ros::Subscriber sub4 = n.subscribe("team", 1, Callback_team);
    ros::Subscriber sub6 = n.subscribe("start", 1, Callback_start);
    ros::Subscriber sub6 = n.subscribe("message_opp2", 1, Callback_opp);


    ros::Publisher pub1 = n.advertise<std_msgs::Int8>("move", 1);
	ros::Publisher pub2 = n.advertise<geometry_msgs::Pose2D>("target", 1);
    ros::Publisher pub3 = n.advertise<std_msgs::Int8>("enable_rotation", 1);
    ros::Publisher pub4 = n.advertise<std_msgs::Int8>("dynamixel_cmd", 1);
    ros::Publisher pub5 = n.advertise<std_msgs::Bool>("shoot_enable",1);



    ros::Rate loop_rate(100);

	geometry_msgs::Pose2D target;
    std_msgs::Int8 move;
    std_msgs::Int8 enable_rotation;
    std_msgs::Int8 dynamixel_cmd;
    std_msgs::Bool shoot_enable;



    while (ros::ok())
    {
        FSM(cvs);
        move.data = cvs->move;
        target.x = cvs->targetX;
		target.y = cvs->targetY;
		enable_rotation.data = cvs->enable_rotation;
		dynamixel_cmd.data = dyna;
		shoot_enable.data = enable_shooting;

		pub1.publish(move);
        pub2.publish(target);
        pub3.publish(enable_rotation);
        pub4.publish(dynamixel_cmd);
        pub5.publish(shoot_enable);

        ros::spinOnce();
        loop_rate.sleep();
    }

//    ros::spin(); //enters a loop calling msgs callbacks afap. Is like waiting for the msg to arrive

    return 0;
    free_Struct(cvs);
}

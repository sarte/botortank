#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "bot/tetra.h"
#include "geometry_msgs/Twist.h"
#include "bot/quad.h"
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
double dist = 69;
double deltaX = 0;
double deltaY = 0;
double speedX = 0;
double speedY = 0;

bool line1;
bool line2;
bool line3;
bool line4;

int cnt = 0;

int feedback;
int dyna;
//string feedback;
//string dyna;


/////////////////////////////////////////////////////////////////////

typedef enum States
{
	STANDBY, DOMO1, DOMO2
	//STANDBY, START, DOMO1, DOMO2, BALL1, BALL2, BALL3, BALL4, GO_SHOOT, TURN_SHOOT, SHOOT, GO_BEE, TURN_BEE, BEE, PUSH_BEE
	//STANDBY, START, CAL_X, CAL_Y, HOME, TARG, VIA1, VIA2
} States;

typedef struct Struct
{
    double targetX, targetY;
    int move;
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
	cvs->state = DOMO1;
	cvs->prevstate = DOMO1;
	cvs->targetX = 0;
	cvs->targetY = 0;
	cvs->move = 0;

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




// void Callback_team(const std_msgs::Bool& team)
// {
    // team = team.data;
// }


// void Callback_lidar(const geometry_msgs::Pose2D& localisation_lidar)
// {
    // pos_X = localisation_lidar.x;
    // pos_Y = localisation_lidar.y;
    // pos_theta = localisation_lidar.theta;
// }


// void Callback_feedback(const std_msgs::String& dyna_feedback)
// {
    // feedback = dyna_feedback.data;

// }


void Callback_follow(const bot::tetra& blackline)
{
    line1 = blackline.a;
	line2 = blackline.b;
	line3 = blackline.c;
	line4 = blackline.d;
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

///////////////////////////////////////////////////////////////////////////////

void FSM(Struct* cvs)
{
	switch(cvs->state){

		case STANDBY:
        printf("STANDBY\n");

			speedX = 0;
			speedY = 0;
            cvs->prevstate = cvs->state;
            cvs->state = STANDBY;
        break;


		// case START:
			//choose team
			//nextstate
			// if(team == 1){
				// cvs->team = 1;
			// }
			// else{
				// cvs->team = 0;
			// }

			// cvs->prevstate = cvs->state;
			// cvs->state = DOMO1;

			// break;

		case DOMO1:
            printf("DOMO1\n");


			//cvs->targetX = ;
			//cvs->targetY = ;



			if(line1 || line2 || line3 || line4){

				speedX = 0;
				speedY = 0;
				cvs->prevstate = cvs->state;
				cvs->state = DOMO2;
			}
			else{
				speedX = 0;
				speedY = 4;
			}

			break;

		case DOMO2:
            printf("DOMO2\n");

			//cvs->targetX = ;
			//cvs->targetY = ;

			cnt++;

			if(cnt > 300){

				speedX = 0;
				speedY = 0;
				cvs->prevstate = cvs->state;
				cvs->state = STANDBY;
			}
			else{

				speedX = 4;
				speedY = 0;
			}

			break;

		// case BALL1:

			// cvs->targetX = ;
			// cvs->targetY = ;

			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist < 0.03){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = BALL2;
			// }
			// else{

				// cvs->move = 1;
			// }

			// break;

		// case BALL2:

			// cvs->targetX = ;
			// cvs->targetY = ;

			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist < 0.03){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = BALL3;
			// }
			// else{

				// cvs->move = 1;
			// }
			// break;

		// case BALL3:

			// cvs->targetX = ;
			// cvs->targetY = ;

			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist < 0.03){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = BALL4;
			// }
			// else{

				// cvs->move = 1;
			// }

			// break;

		// case BALL4;

			// dyna = 4; //ball;
			// cvs->targetX = ;
			// cvs->targetY = ;

			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist < 0.02){

				// if(feedback == 4){

					// cvs->move = 0;
					// cvs->prevstate = cvs->state;
					// cvs->state = GO_SHOOT;
				// }
			// }
			// else{

				// cvs->move =1;
			// }

			// break;

		// case GO_SHOOT:

			// cvs->targetX = ;
			// cvs->targetY = ;

			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist < 0.03){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = TURN_SHOOT;
			// }
			// else{

				// cvs->move = 1;
			// }

			// break;

		// case TURN_SHOOT:

			// cvs->targetX = ;
			// cvs->targetY = ;

			// if(angle <   && angle >   ){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = SHOOT;
			// }
			// else{

				// cvs->move = 1;
			// }

			// break;

		// case SHOOT:

				// dyna = 1; //sorting1

				// if(feedback == 1){

					// cvs->prevstate = cvs->state;
					// cvs->state = Go_BEE;
				// }


			// break;

		// case GO_BEE:

			// cvs->targetX = ;
			// cvs->targetY = ;

			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist<0.03){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = BALL4;
			// }
			// else{

				// cvs->move = 1;
			// }

			// break;

		// case TURN_BEE;

			// cvs->targetX = ;
			// cvs->targetY = ;

			// if(angle <   && angle >   ){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = BALL4;
			// }
			// else{

				// cvs->move = 1;
			// }

			// break;

		// case BEE:

			// dyna = 3; //bee

			// break;

		// case PUSH_BEE;

			// cvs->targetX = ;
			// cvs->targetY = ;

			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist<0.03){

				// cvs->move = 0;
				// cvs->prevstate = cvs->state;
				// cvs->state = STANDBY;
			// }
			// else{

				// cvs->move = 1;
			// }

			// break;

	}

}

////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv) {
    Struct* cvs;
    cvs = init_Struct();
    ros::init(argc, argv, "fsm");
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("team", 1, Callback_team);
    // ros::Subscriber sub2 = n.subscribe("", 1, Callback_lidar);
    ros::Subscriber sub3 = n.subscribe("dyna_feedback", 1, Callback_feedback);
    ros::Subscriber sub4 = n.subscribe("blackline", 1, Callback_follow);
    ros::Subscriber sub5 = n.subscribe("trajectory", 1, );
	ros::Subscriber sub6 = n.subscribe("origin_green",1,greenCallback);
    ros::Subscriber sub7 = n.subscribe("origin_orange",1,orangeCallback);

    ros::Publisher pub1 = n.advertise<std_msgs::int8>("move", 1);
	ros::Publisher pub2 = n.advertise<geometry_msgs::Pose2D>("target", 1);
	ros::Publisher pub3 = n.advertise<geometry_msgs::Twist>("velocity_ref",1);

    ros::Rate loop_rate(100);

    geometry_msgs::Twist velocity_ref;


	geometry_msgs::Pose2D target;
    std_msgs::int8 move;


    while (ros::ok())
    {
        FSM(cvs);

		velocity_ref.linear.x = speedX;
		velocity_ref.linear.y = speedY;
		pub.publish(velocity_ref);
        move.data = cvs->move;
        target.x = cvs->targetX;
		target.y = cvs->targetY;
		target.theta = cvs->target_theta;

		pub.publish(move);
        pub.publish(target);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
    free_Struct(cvs);
}

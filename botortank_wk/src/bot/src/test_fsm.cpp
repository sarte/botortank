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

bool team ;
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
int flagdyna3 = 0;
double theta_slam = 0;
int cnt2 = 0;
//string feedback;
//string dyna;
int cntr1=100;
int cntr2=100;
int cntr3=100;
int cntr4=100;
int cntr5=100;
int cntr6=100;
int cntr7=100;
int cntr8=100;
int cntr9=100;
int cntr10=100;
int cntr11=100;
int cntr12=100;
int cntr13=100;
int cntr14=100;
int cntr15=100;
double xtarg1=0.0;
double xtarg2=0.0;
double xtarg3=0.0;
double xtarg4=0.0;
double xtarg5=0.0;
double xtarg6=0.0;
double xtarg7=0.0;
double xtarg8=0.0;
double xtarg9=0.0;
double xtaro1=0.0;
double xtaro2=0.0;
double xtaro3=0.0;
double xtaro4=0.0;
double xtaro5=0.0;
double xtaro6=0.0;
double xtaro7=0.0;
double xtaro8=0.0;
double xtaro9=0.0;
double ytarg1=0.0;
double ytarg2=0.0;
double ytarg3=0.0;
double ytarg4=0.0;
double ytarg5=0.0;
double ytarg6=0.0;
double ytarg7=0.0;
double ytarg8=0.0;
double ytarg9=0.0;
double ytaro1=0.0;
double ytaro2=0.0;
double ytaro3=0.0;
double ytaro4=0.0;
double ytaro5=0.0;
double ytaro6=0.0;
double ytaro7=0.0;
double ytaro8=0.0;
double ytaro9=0.0;


/////////////////////////////////////////////////////////////////////

typedef enum States
{
	STANDBY, START, DOMO1, DOMO2, BALL1, BALL2, BALL3, TURN_BALL, LOQUET, BALL4, GO_SHOOT, TURN_SHOOT, SHOOT, GO_BEE1,GO_BEE2, TURN_BEE, BEE, PUSH_BEE, CAL_BEE, CAL_BEE1, CAL_BEE2,//STANDBY, START, CAL_X, CAL_Y, HOME, TARG, VIA1, VIA2
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
	cvs->state = STANDBY;
	cvs->prevstate = STANDBY;
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




void Callback_team(const std_msgs::Bool& teamdata)
{
    team = teamdata.data;
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

void Callback_slam_out(const geometry_msgs::Pose2D& slam_theta)
{
	theta_slam = slam_theta.theta;
}



///////////////////////////////////////////////////////////////////////////////

void FSM(Struct* cvs)
{
    if(start == 1 && !flagstart)
    {
        flagstart=1;
        cvs->state= START;
    }
    if (cvs->team){
        pos_X= pos_X_O;
		pos_Y=pos_Y_O;
		pos_theta=pos_theta_O;
	}
    else
    {
        pos_X=pos_X_G;
        pos_Y=pos_Y_G;
        pos_theta=pos_theta_G;
    }
    if(t>cntr1)
    {
        cvs->prevstate = cvs->state;
        cvs->state = STANDBY;
    }
	switch(cvs->state)
	{
		case STANDBY:
        	printf("STANDBY\n");
            cvs->move=0;
            cvs->prevstate = cvs->state;
            cvs->state = STANDBY;
        break;


		case START:
        	printf("START\n");
			//choose team
			//nextstate
			if(team == 1)
			{
				cvs->team = 1;
			}
			else
			{
				cvs->team = 0;
			}
			cvs->prevstate = cvs->state;
			cvs->state = DOMO1;
			t++;
		break;

		case DOMO1:
        	printf("DOMO1\n");
 			if(cvs->team)
 			{
                cvs->targetX =xtaro1 ;
                cvs->targetY =ytaro1 ;
			}

			else
			{
                cvs->targetX =xtarg1;
                cvs->targetY =ytarg1;
			}
			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist<0.06)
			{
				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = DOMO2;
			}
			else
			{
				cvs->move = 1;
			}
			t++;
		break;

		case DOMO2://reecrire en fonction du temps
        	printf("DOMO2\n");
        	cnt++;
			if(cnt > cntr2)
			{
				cnt = 0;
				cvs->move=0;
				cvs->prevstate = cvs->state;
				cvs->state = GO_BEE1;
			}
			else
			{
                if(team)
                {
                    cvs->move=4;
                }
                else
                {
                    cvs->move=3;
                }
			}
			t++;
		break;

			// if(cvs->team){
   //              cvs->targetX =1.3 ;
   //              cvs->targetY =-0.8 ;
			// }

			// else{
   //              cvs->targetX = -0.37 ;
   //              cvs->targetY = 0.8;
			// }


			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist<0.03){

			// 	cvs->move = 0;
			// 	cvs->prevstate = cvs->state;
			// 	cvs->state = GO_BEE1;
			// }
			// else{

			// 	cvs->move = 1;
			// }

			// t++;

			// break;

        case GO_BEE1:
        	printf("BEE1\n");
			if(cvs->team)
			{
                cvs->targetX =xtaro2;
                cvs->targetY =ytaro2 ;
			}
			else
			{
                cvs->targetX =xtarg2;
                cvs->targetY =ytarg2;
			}
			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);
			if(dist<0.05)
			{
				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = TURN_BEE;
			}
			else
			{
				cvs->move = 1;
			}
			t++;
		break;

        case GO_BEE2:
        	printf("BEE2\n");
			if(cvs->team)
			{
                cvs->targetX =xtaro3;
                cvs->targetY =ytaro3;
			}
			else
			{
                cvs->targetX =xtarg3;
                cvs->targetY =ytarg3;
			}
			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);
			if(dist<0.04)
			{
				cvs->move = 0;
				cvs->prevstate = cvs->state;
//				cvs->state = CAL_BEE1;
			}
			else
			{
				cvs->move = 1;
			}
			t++;
		break;

        case TURN_BEE:
        	printf("TURN_BEE\n");
     //    	if(cvs->team)
     //    	{
     //    		cvs->enable_rotation = 1;
     //    		if(theta_slam < -87 && theta_slam > -92)
     //    		{
     //    			cvs->move = 0;
     //    			cvs->prevstate = cvs->state;
     //    			cvs->state = GO_BEE2;
     //    			cvs->enable_rotation = 0;
     //    		}
     //    		else
     //    		{
     //    			cvs->move = 2;
     //    		}
     //    	}
     //    	else
     //    	{
     //    		cvs->enable_rotation = 1;
     //    		if(theta_slam < -87 && theta_slam > -92)
     //    		{
     //    			cvs->move = 0;
     //    			cvs->prevstate = cvs->state;
     //    			cvs->state = GO_BEE2;
     //    			cvs->enable_rotation = 0;
     //    		}
     //    		else
     //    		{
     //    			cvs->move = 2;
     //    		}
     //    	}
     //    	t++;
    	// break;



        	if(cvs->team){
                cvs->enable_rotation=1;
                if(cnt>cntr3){

                    cvs->move = 0;
                    if(cnt> cntr10){

                        cvs->prevstate = cvs->state;
                        cnt=0;
                        cvs->state = GO_BEE2;
                        cvs->enable_rotation=0;
                    }
                }
                else{

                    cvs->move = 2;
                }
			}
			else{
                cvs->enable_rotation=-1;

                if(cnt>cntr4){

                    cvs->move = 0;
                    cnt=0;
                    cvs->prevstate = cvs->state;
                    cvs->state = GO_BEE2;
				cvs->enable_rotation=0;
                }
                else{

				cvs->move = 2;
                }
			}
			cnt++;
			t++;

			break;
  //           cvs->enable_rotation=1;
  //           if(pos_theta < -178   ||  pos_theta > 178  )
  //           {
  //               cvs->move = 0;
  //               cvs->prevstate = cvs->state;
  //               cvs->state = GO_BEE2;
  //               cvs->enable_rotation=0;
  //           }
  //           else
  //           {
  //               cvs->move = 2;
  //           }
  //           t++;
		// break;
			// else{
   //              cvs->enable_rotation=-1;

   //              if(pos_theta <2   &&  pos_theta > -2  ){

   //                  cvs->move = 0;
   //                  cvs->prevstate = cvs->state;
   //                  cvs->state = GO_BEE2;
			// 	cvs->enable_rotation=0;
   //              }
   //              else{

			// 	cvs->move = 2;
   //              }
			// }


		case BEE:
        	printf("BEE\n");
        	if(cnt >2* cntr9){
        		dyna = 0;
        		cnt = 0;
        		cvs->prevstate = cvs->state;
        		cvs->state = PUSH_BEE;
        	}
        	else if(cnt> cntr9){
        		dyna = 3;
        	}
// //        	printf("count = %i\n",cnt);
// //			if(cnt >cntr5)
// //			{
// //				cvs->move=0;
// //				if(cnt > cntr6){
// //					printf("Cnt2 = %i\n",cnt2);
// //					if(cnt2 > cntr7){
// //						cnt=0;
// //						cvs->prevstate = cvs->state;
// //						cvs->state = PUSH_BEE;
// //						cnt2=0;
// //					}
// //					else{
// //						dyna = 3;
// //						cnt2++;
// //					}
// //				}
//                 if(cnt > cntr5){
//                 if(!flagdyna3){
//                     dyna = 3;
//                     flagdyna3 =0;
//                 }
//                 if(feedback == 3){
//                     cvs->prevstate = cvs->state;
//                     cvs->state = PUSH_BEE;
//                     cnt=0;
//                 }
//             }

// //			}
// 			else
// 			{
//                 if(cvs->team)
//                 {
//                     cvs->move=4;
//                 }
//                 else{

//                     cvs->move=10;
//                 }
// 			}
// 			cnt++;
// 			t++;
        	t++;
        	cnt++;
		break;


		case CAL_BEE1 :
			printf("CAL_BEE\n");
			if(cnt > cntr5) {
				cnt = 0;
				cvs->move = 0;
				cvs->prevstate = cvs->state;
				// cvs->state = CALL_BEE2;
			}
			else{
				if(cvs->team){
					cvs->move = 4;
				}
				else{
					cvs->move = 4;
				}
			}
			t++;
			cnt++;
			break;

		// case CAL_BEE1 :
		// 	printf("CAL_BEE\n");
		// 	if(cnt > cntr5) {
		// 		cnt = 0;
		// 		cvs->move = 0;
		// 		cvs->prevstate = cvs->state;
		// 		cvs->state = BEE;
		// 	}
		// 	else{
		// 		if(cvs->team){
		// 			cvs->move = 4;
		// 		}
		// 		else{
		// 			cvs->move = 4;
		// 		}
		// 	}
		// 	t++;
		// 	cnt++;
		// 	break;

//		case CAL_BEE :
//			printf("CAL_BEE\n");
//			if(cnt > 2*cntr5){
//				cnt = 0;
//				cvs->move = 0;
//				cvs->prevstate = cvs->state;
//				cvs->state = BEE;
//			}
//			else if(cnt > cntr5){
//				if(cvs->team){
//					cvs->move = 4;
//				}
//				else{
//					cvs->move = 6;
//				}
//			}
//			else{
//				if(cvs->team){
//					cvs->move = 4;
//				}
//				else{
//					cvs->move = 4;
//				}
//			}
//			t++;
//			cnt++;
//			break;




			// if(cvs->team)
			// {
   //              cvs->targetX =1.3 ;
   //              cvs->targetY =-0.8 ;
			// }

			// else{
   //              cvs->targetX =-1.35 ;
   //              cvs->targetY = 0.87 ;
			// }


			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			// if(dist<0.03){

			// 	cvs->move = 0;
			// 	dyna = 3;
			// 	cvs->prevstate = cvs->state;
			// 	cvs->state = PUSH_BEE;
			// }
			// else{

			// 	cvs->move = 1;
			// }

			// t++;

			// break;

        case PUSH_BEE:
        	printf("PUSH_BEE\n");
        	cnt++;
			if(cnt > cntr8)
			{
				cnt = 0;
				cvs->move=0;
				cvs->prevstate = cvs->state;
				cvs->state = BALL1;
			}
			else
			{
                if(team)
                {
                    cvs->move=6;
                }
                else
                {
                    cvs->move=3;
                }
			}
			t++;
		break;





		// 	if(cvs->team)
		// 	{
  //               cvs->targetX =1.3 ;
  //               cvs->targetY =-0.8 ;
		// 	}
		// 	else
		// 	{
  //               cvs->targetX =-1.12;
  //               cvs->targetY = 0.87;
		// 	}
		// 	deltaX = cvs->targetX - pos_X;
		// 	deltaY = cvs->targetY - pos_Y;
		// 	dist = sqrt(deltaX*deltaX + deltaY*deltaY);
		// 	if(dist<0.03)
		// 	{
		// 		cvs->move = 0;
		// 		cvs->prevstate = cvs->state;
		// 		cvs->state = BALL1;
		// 	}
		// 	else
		// 	{
		// 		cvs->move = 1;
		// 	}
		// 	t++;
		// break;

		case BALL1:
		printf("BALL1\n");
//			dyna = 0;
			if(cvs->team)
			{
                cvs->targetX =xtaro4;
                cvs->targetY =ytaro4;
			}
			else
			{
                cvs->targetX =xtarg4;
                cvs->targetY =ytarg4;
			}
			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);
			if(dist<0.03){
				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = TURN_BALL;
			}
			else
			{
				cvs->move = 1;
			}
			t++;
		break;

		case TURN_BALL:
		printf("TURN_BALL\n");
		// 	if(cvs->team)
		// 	{
		// 		cvs->enable_rotation = 1;
  //       		if(theta_slam < -2 && theta_slam > 2)
  //       		{
  //       			cvs->move = 0;
  //       			cvs->prevstate = cvs->state;
  //       			cvs->state = BALL2;
  //       			cvs->enable_rotation = 0;
  //       		}
  //       		else
  //       		{
  //       			cvs->move = 2;
  //       		}
		// 	}
		// 	else
		// 	{
		// 		cvs->enable_rotation = 1;
  //       		if(theta_slam < -2 && theta_slam > 2)
  //       		{
  //       			cvs->move = 0;
  //       			cvs->prevstate = cvs->state;
  //       			cvs->state = BALL2;
  //       			cvs->enable_rotation = 0;
  //       		}
  //       		else
  //       		{
  //       			cvs->move = 2;
  //       		}
		// 	}
		// 	t++;
		// break;



			if(cvs->team){
                cvs->enable_rotation=1;
                if(cnt>cntr3){

                    cnt=0;
                    cvs->move = 0;
                    cvs->prevstate = cvs->state;
                    cvs->state = BALL2;
                    cvs->enable_rotation=0;
                }
                else{

                    cvs->move = 2;
                }
			}
			else{
                cvs->enable_rotation=1;

                if(cnt>cntr3 ){

                    cvs->move = 0;
                    cnt=0;
                    cvs->prevstate = cvs->state;
                    cvs->state = BALL2;
				cvs->enable_rotation=0;
                }
                else{

				cvs->move = 2;
                }
			}
			cnt++;
			t++;

			break;
  //           cvs->enable_rotation=1;
  //               if(pos_theta > -85   ||  pos_theta < -95 )
  //               {
  //                   cvs->move = 0;
  //                   cvs->prevstate = cvs->state;
  //                   cvs->state = BALL2;
  //                   cvs->enable_rotation=0;
  //               }
  //               else
  //               {
  //                   cvs->move = 2;
  //               }
		// 	t++;
		// break;

		case BALL2:
		printf("BALL2\n");
			if(team)
			{
                cvs->targetX = xtaro5;
                cvs->targetY = ytaro5;
			}
			else
			{
				cvs->targetX = xtarg5;
				cvs->targetY = ytarg5;



			}


			deltaX = cvs->targetX - pos_X;
			deltaY = cvs->targetY - pos_Y;
			dist = sqrt(deltaX*deltaX + deltaY*deltaY);

			if(dist < 0.02){

				cvs->move = 0;
				cvs->prevstate = cvs->state;
				cvs->state = LOQUET;
			}
			else{

				cvs->move = 1;
			}

			cnt++;
			t++;
		break;

		case LOQUET:
		printf("LOQUET\n");


			if(cnt > cntr13)
			{
				cnt = 0;
				cvs->move=0;
				cvs->prevstate = cvs->state;
				cvs->state = BALL4;
			}
			else
			{
                if(team)
                {
                    cvs->move=4;
                }
                else
                {
                    cvs->move=3;
                }
			}
			t++;
			cnt++;
		break;


			// if(team){
   //              cvs->targetX = 0;
   //              cvs->targetY = 0;
			// }
			// else{
   //              cvs->targetX = -1.34;
   //              cvs->targetY = 0.05;
			// }
			// deltaX = cvs->targetX - pos_X;
			// deltaY = cvs->targetY - pos_Y;
			// dist = sqrt(deltaX*deltaX + deltaY*deltaY);
			// if(dist < 0.03){
			// 	cvs->move = 0;
			// 	cvs->prevstate = cvs->state;
			// 	cvs->state = GO_SHOOT;
			// }
			// else{

			// 	cvs->move = 1;
			// }
			// t++;
			// break;

        case BALL4:
        printf("BALL4\n");

			if(cnt > cntr11+cntr9)
			{
				cnt = 0;
				dyna = 0;
				cvs->prevstate = cvs->state;
				cvs->state = GO_SHOOT;
			}
			else if (cnt>cntr9)
			{
                dyna = 4;
			}
			t++;
			cnt++;
		break;

			// dyna = 4; //ball;

   //          if(feedback == 4){
   //              dyna=0;
			// 	cvs->prevstate = cvs->state;
			// 	cvs->state = GO_SHOOT;
   //          }

			// t++;

			// break;

		case GO_SHOOT:
		printf("GO_SHOOT\n");

			if(team){
                cvs->targetX = xtaro6;
                cvs->targetY = ytaro6;
			}
			else{
                cvs->targetX = xtarg6;
                cvs->targetY = ytarg6;
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
		printf("TURN_SHOOT\n");
		if(cvs->team){
			// cvs->enable_rotation = 1;
   //      		if(theta_slam < -2 && theta_slam > 2)
   //      		{
   //      			cvs->move = 0;
   //      			cvs->prevstate = cvs->state;
   //      			cvs->state = SHOOT;
   //      			cvs->enable_rotation = 0;
   //      		}
   //      		else
   //      		{
   //      			cvs->move = 2;
   //      		}
                cvs->enable_rotation=1;
                if(cnt>cntr12){

                    cnt=0;
                    cvs->move = 0;
                    cvs->prevstate = cvs->state;
                    cvs->state = SHOOT;
                    cvs->enable_rotation=0;
                }
                else{

                    cvs->move = 2;
                }
			}
			else{
				// cvs->enable_rotation = 1;
    //     		if(theta_slam < -168 && theta_slam > -172)
    //     		{
    //     			cvs->move = 0;
    //     			cvs->prevstate = cvs->state;
    //     			cvs->state = SHOOT;
    //     			cvs->enable_rotation = 0;
    //     		}
    //     		else
    //     		{
    //     			cvs->move = 2;
    //     		}
                cvs->enable_rotation=-1;

                if(cnt>cntr12){

                    cvs->move = 0;
                    cnt=0;
                    cvs->prevstate = cvs->state;
                    cvs->state = SHOOT;
				cvs->enable_rotation=0;
                }
                else{

				cvs->move = 2;
                }
			}
			cnt++;
			t++;

			break;

			// if(cvs->team){
   //              cvs->enable_rotation=0;
			// }
			// else{
   //              cvs->enable_rotation=0;
			// }
			// cvs->enable_rotation=1;
			// if(pos_theta < -248  && pos_theta > -243  ){
			// 	cvs->move = 0;
			// 	cvs->prevstate = cvs->state;
			// 	cvs->state = SHOOT;
			// }
			// else{
			// 	cvs->move = 2;
			// }
			// t++;

			// break;

		case SHOOT:
		printf("SHOOT\n");
			cvs->move = 0;

			if(cnt > cntr11+(2*cntr9)){
				cnt = 0;
				dyna = 0;
				enable_shooting = 0;
				cvs->prevstate = cvs->state;
				cvs->state = STANDBY;
			}
			else if (cnt>(2*cntr9)){

				dyna = 1; //sorting1
				enable_shooting=1;
			}
			else if (cnt>cntr9){
				enable_shooting=1;
			}


//				if(feedback == 1){
//                    dyna=0;
//                    enable_shooting=0;
//					cvs->prevstate = cvs->state;
//					cvs->state = STANDBY;
//				}
				t++;
				cnt++;


			break;


	}

}

////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv) {
    Struct* cvs;
    cvs = init_Struct();
    ros::init(argc, argv, "test_fsm");
    ros::NodeHandle n;
    //ros::Subscriber sub1 = n.subscribe("team", 1, Callback_team);
    ros::Subscriber sub1 = n.subscribe("origin_green", 1, Callback_lidar_g);
    ros::Subscriber sub5 = n.subscribe("origin_orange",1,Callback_lidar_o);
    ros::Subscriber sub2 = n.subscribe("dyna_feedback", 1, Callback_feedback);
    ros::Subscriber sub3 = n.subscribe("blackline", 1, Callback_follow);
    ros::Subscriber sub4 = n.subscribe("team", 1, Callback_team);
    ros::Subscriber sub6 = n.subscribe("start", 1, Callback_start);
    ros::Subscriber sub7 = n.subscribe("slam_out",1,Callback_slam_out);

    ros::Publisher pub1 = n.advertise<std_msgs::Int8>("move", 1);
	ros::Publisher pub2 = n.advertise<geometry_msgs::Pose2D>("target", 1);
    ros::Publisher pub3 = n.advertise<std_msgs::Int8>("enable_rotation", 1);
    ros::Publisher pub4 = n.advertise<std_msgs::Int8>("dynamixel_cmd", 1);
    ros::Publisher pub5 = n.advertise<std_msgs::Int8>("shoot_enable",1);


    ros::NodeHandle nh_private("~");
    nh_private.param<int>("cntr1", cntr1, 100);
    nh_private.param<int>("cntr2", cntr2, 100);
    nh_private.param<int>("cntr3", cntr3, 100);
    nh_private.param<int>("cntr4", cntr4, 100);
    nh_private.param<int>("cntr5", cntr5, 100);
    nh_private.param<int>("cntr6", cntr6, 100);
    nh_private.param<int>("cntr7", cntr7, 100);
    nh_private.param<int>("cntr8", cntr8, 100);
    nh_private.param<int>("cntr9", cntr9, 100);
    nh_private.param<int>("cntr10", cntr10, 100);
    nh_private.param<int>("cntr11", cntr11, 100);
    nh_private.param<int>("cntr12", cntr12, 100);
    nh_private.param<int>("cntr13", cntr13, 100);
    nh_private.param<int>("cntr14", cntr14, 100);
    nh_private.param<int>("cntr15", cntr15, 100);
    nh_private.param<double>("xtarg1", xtarg1, 0.0);
    nh_private.param<double>("xtarg2", xtarg2, 0.0);
    nh_private.param<double>("xtarg3", xtarg3, 0.0);
    nh_private.param<double>("xtarg4", xtarg4, 0.0);
    nh_private.param<double>("xtarg5", xtarg5, 0.0);
    nh_private.param<double>("xtarg6", xtarg6, 0.0);
    nh_private.param<double>("xtarg7", xtarg7, 0.0);
    nh_private.param<double>("xtarg8", xtarg8, 0.0);
    nh_private.param<double>("xtarg9", xtarg9, 0.0);
    nh_private.param<double>("xtaro1", xtaro1, 0.0);
    nh_private.param<double>("xtaro2", xtaro2, 0.0);
    nh_private.param<double>("xtaro3", xtaro3, 0.0);
    nh_private.param<double>("xtaro4", xtaro4, 0.0);
    nh_private.param<double>("xtaro5", xtaro5, 0.0);
    nh_private.param<double>("xtaro6", xtaro6, 0.0);
    nh_private.param<double>("xtaro7", xtaro7, 0.0);
    nh_private.param<double>("xtaro8", xtaro8, 0.0);
    nh_private.param<double>("xtaro9", xtaro9, 0.0);
    nh_private.param<double>("ytarg1", ytarg1, 0.0);
    nh_private.param<double>("ytarg2", ytarg2, 0.0);
    nh_private.param<double>("ytarg3", ytarg3, 0.0);
    nh_private.param<double>("ytarg4", ytarg4, 0.0);
    nh_private.param<double>("ytarg5", ytarg5, 0.0);
    nh_private.param<double>("ytarg6", ytarg6, 0.0);
    nh_private.param<double>("ytarg7", ytarg7, 0.0);
    nh_private.param<double>("ytarg8", ytarg8, 0.0);
    nh_private.param<double>("ytarg9", ytarg9, 0.0);
    nh_private.param<double>("ytaro1", ytaro1, 0.0);
    nh_private.param<double>("ytaro2", ytaro2, 0.0);
    nh_private.param<double>("ytaro3", ytaro3, 0.0);
    nh_private.param<double>("ytaro4", ytaro4, 0.0);
    nh_private.param<double>("ytaro5", ytaro5, 0.0);
    nh_private.param<double>("ytaro6", ytaro6, 0.0);
    nh_private.param<double>("ytaro7", ytaro7, 0.0);
    nh_private.param<double>("ytaro8", ytaro8, 0.0);
    nh_private.param<double>("ytaro9", ytaro9, 0.0);

    printf("FSM cntr1: %i\n", cntr1);
    printf("FSM cntr2: %i\n", cntr2);
    printf("FSM cntr3: %i\n", cntr3);
    printf("FSM cntr4: %i\n", cntr4);
    printf("FSM cntr5: %i\n", cntr5);
    printf("FSM cntr6: %i\n", cntr6);
    printf("FSM cntr7: %i\n", cntr7);
    printf("FSM cntr8: %i\n", cntr8);
    printf("FSM cntr9: %i\n", cntr9);
    printf("FSM cntr10: %i\n", cntr10);
    printf("FSM cntr11: %i\n", cntr11);
    printf("FSM cntr12: %i\n", cntr12);
    printf("FSM cntr13: %i\n", cntr13);
    printf("FSM cntr14: %i\n", cntr14);
    printf("FSM cntr15: %i\n", cntr15);
    printf("FSM targ1: %f  %f\n", xtarg1, ytarg1);
    printf("FSM targ2: %f  %f\n", xtarg2, ytarg2);
    printf("FSM targ3: %f  %f\n", xtarg3, ytarg3);
    printf("FSM targ4: %f  %f\n", xtarg4, ytarg4);
    printf("FSM targ5: %f  %f\n", xtarg5, ytarg5);
    printf("FSM targ6: %f  %f\n", xtarg6, ytarg6);
    printf("FSM targ7: %f  %f\n", xtarg7, ytarg7);
    printf("FSM targ8: %f  %f\n", xtarg8, ytarg8);
    printf("FSM targ9: %f  %f\n", xtarg9, ytarg9);
    printf("FSM taro1: %f  %f\n", xtaro1, ytaro1);
    printf("FSM taro2: %f  %f\n", xtaro2, ytaro2);
    printf("FSM taro3: %f  %f\n", xtaro3, ytaro3);
    printf("FSM taro4: %f  %f\n", xtaro4, ytaro4);
    printf("FSM taro5: %f  %f\n", xtaro5, ytaro5);
    printf("FSM taro6: %f  %f\n", xtaro6, ytaro6);
    printf("FSM taro7: %f  %f\n", xtaro7, ytaro7);
    printf("FSM taro8: %f  %f\n", xtaro8, ytaro8);
    printf("FSM taro9: %f  %f\n", xtaro9, ytaro9);
    ros::Rate loop_rate(100);

	geometry_msgs::Pose2D target;
    std_msgs::Int8 move;
    std_msgs::Int8 enable_rotation;
    std_msgs::Int8 dynamixel_cmd;
    std_msgs::Int8 shoot_enable;



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

    free_Struct(cvs);
    return 0;
}

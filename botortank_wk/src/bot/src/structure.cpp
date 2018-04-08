#include "structure.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

Struct* init_Struct()
{
	Struct *cvs;
	cvs = (Struct*)malloc(sizeof(Struct));
	cvs->int_error_1 = 0;
	cvs->int_error_2 = 0;
	cvs->int_error_3 = 0;
	cvs->int_error_4 = 0;
	cvs->wheel_commands1 = 0;
	cvs->wheel_commands2 = 0;
	cvs->wheel_commands3 = 0;
	cvs->wheel_commands4 = 0;
    return cvs;

}

void free_Struct(Struct *cvs)
{
	free(cvs);
}

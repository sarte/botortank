#include <stdlib.h>
typedef struct Struct
{
	double int_error_1,int_error_2,int_error_3,int_error_4;
	double wheel_commands1,wheel_commands2,wheel_commands3,wheel_commands4;
} Struct;

Struct* init_Struct();
void fre_Struct(Struct *cvs);
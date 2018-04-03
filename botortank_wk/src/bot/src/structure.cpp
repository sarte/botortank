#include "structure.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

Struct* init_Struct()
{
	Struct *cvs;
	cvs = (Struct*)malloc(sizeof(Struct));
	cvs->count = 0;
}

void free_Struct(Struct *cvs)
{
	free(cvs);
}

#ifndef _CTRLSTRUCT_GR5_H_
#define _CTRLSTRUCT_GR5_H_

#include "ctrl_io.h"
typedef struct UserStruct{

    double int_error_1;
    double int_error_2;
    double int_error_3;
    double int_error_4;
    double t_old;
} UserStruct;

typedef struct CtrlStruct{
	UserStruct *theUserStruct;  ///< user defined CtrlStruct
	CtrlIn *theCtrlIn;   ///< controller inputs
	CtrlOut *theCtrlOut; ///< controller outputs
} CtrlStruct;

int size_UserStruct();

#endif //ifndef

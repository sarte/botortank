from ctypes import *
import os
#retourne les fonctions C du Controller low-level
def Getc():
    thisPath, noValue = os.path.split(os.path.abspath(__file__))
    c_size_UserStruct = CDLL(thisPath + '/C-code/libCtrlStruct.so').size_UserStruct  # todo: .so if compiled for linux :) (rpi)
    c_size_UserStruct.restype = c_int
    size_userStruct = c_size_UserStruct()

    NB_U_SWITCH = 2
    NB_STORE_EDGE = 10
    ID_1=0
    ID_2=1
    ID_3=2
    ID_4=3


    class UserStruct(Structure):
        _fields_ = [("DoNotTouch", c_byte * size_userStruct)]

    class CtrlIn(Structure):
        _fields_ = [("t", c_double),
                    ("wheel_1_speed", c_double),
                    ("wheel_2_speed", c_double),
                    ("wheel_3_speed", c_double),
                    ("wheel_4_speed", c_double),
                    ("u_switch", c_int * NB_U_SWITCH),
                    ("last_rising", c_double * NB_STORE_EDGE),
                    ("last_falling", c_double * NB_STORE_EDGE),
                    ("rising_index", c_int),
                    ("falling_index", c_int),
                    ("nb_rising", c_int),
                    ("nb_falling", c_int),]

    class CtrlOut(Structure):
        _fields_ = [("wheel_commands", c_double * 4),
                    ("tower_command", c_double)]

    class CtrlStruct(Structure):
        _fields_ = [("theUserStruct", POINTER(UserStruct)),
                    ("theCtrlIn", POINTER(CtrlIn)),
                    ("theCtrlOut", POINTER(CtrlOut))]

    theCtrlStruct = CtrlStruct()
    theCtrlIn = CtrlIn()
    theCtrlOut = CtrlOut()
    theUserStruct = UserStruct()

    theCtrlStruct.theCtrlIn = pointer(theCtrlIn)
    theCtrlStruct.theCtrlOut = pointer(theCtrlOut)
    theCtrlStruct.theUserStruct = pointer(theUserStruct)

    libSpeedController = CDLL(thisPath + '/C-code/libspeed.so')  # todo: .so if compiled for linux :) (rpi)
    c_init_speedController = libSpeedController.init_speed_controller
    c_init_speedController.argtypes = [POINTER(CtrlStruct)]
    c_run_speedController = libSpeedController.run_speed_controller
    c_run_speedController.argtypes = [POINTER(CtrlStruct), c_double * 4]


    return theCtrlStruct, c_init_speedController, c_run_speedController


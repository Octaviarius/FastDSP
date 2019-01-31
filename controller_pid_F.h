#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace controller {
#endif



typedef enum{
    PID_SAT_P = 0,
    PID_SAT_I,
    PID_SAT_D,
    PID_SAT_OUT,
    PID_SAT_MIN = 0,
    PID_SAT_MAX
} pid_sat_e;


typedef enum{
    PID_KP = 0,
    PID_KI,
    PID_KD
} pid_k_e;


//! @brief PID controller struct
typedef struct{
    float32 p;          //!< Proportional value
    float32 i;          //!< Integration value
    float32 d;          //!< Differentiation value
    float32 control;    //!< Output control
    float32 k[3];       //!< Time parameters
    float32 saturation[4][2];   //!< Saturation ranges
}pid_f_t;


//! PID init function
EXTERN int pid_init_F(
        pid_f_t *pid,   //!< PID object
        float32 kp,     //!< Proportional coefficient
        float32 ki,     //!< Integration coefficient
        float32 kd      //!< Differentiation coefficient
);






/*!
 * @brief PID processing.
 * Put target value and to feedback current measured value from model
 * @return Control value
 */
EXTERN float32 pid_process_F(
        pid_f_t *pid,       //!< PID object
        float32 target,     //!< Target value
        float32 feedback    //!< Feedback value. Error = target - feedback
);





#ifdef __cplusplus
}   //namespace controller
}   //namespace fastdsp
#endif




#include "../controller_pid_F.h"


#ifdef __cplusplus
namespace fastdsp {
namespace controller {
#endif




EXTERN int pid_init_F(
        pid_f_t *pid,
        float32 kp,
        float32 ki,
        float32 kd
){
    memset(pid, 0, sizeof(*pid));
    pid->k[PID_SAT_P] = kp;
    pid->k[PID_SAT_I] = ki;
    pid->k[PID_SAT_D] = kd;

    pid->saturation[0][0] = -FLT_MAX;
    pid->saturation[1][0] = -FLT_MAX;
    pid->saturation[2][0] = -FLT_MAX;
    pid->saturation[3][0] = -FLT_MAX;

    pid->saturation[0][1] = FLT_MAX;
    pid->saturation[1][1] = FLT_MAX;
    pid->saturation[2][1] = FLT_MAX;
    pid->saturation[3][1] = FLT_MAX;
}







EXTERN float32 pid_process_F(
        pid_f_t *pid,
        float32 target,
        float32 feedback
){
    target -= feedback;

    //diffenetial
    pid->d = constrain_F(target - pid->p, pid->saturation[PID_SAT_D][0], pid->saturation[PID_SAT_D][1]);

    //integration
    pid->i = constrain_F(pid->i + target, pid->saturation[PID_SAT_I][0], pid->saturation[PID_SAT_I][1]);

    //proportional
    pid->p = constrain_F(target, pid->saturation[PID_SAT_P][0], pid->saturation[PID_SAT_P][1]);

    pid->control = constrain_F(
            pid->p * pid->k[PID_KP] +
            pid->i * pid->k[PID_KI] +
            pid->d * pid->k[PID_KD],
            pid->saturation[PID_SAT_OUT][0], pid->saturation[PID_SAT_OUT][1]);

    return pid->control;
}





#ifdef __cplusplus
}   //namespace controller
}   //namespace fastdsp
#endif


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






#ifdef __cplusplus
}   //namespace controller
}   //namespace fastdsp
#endif

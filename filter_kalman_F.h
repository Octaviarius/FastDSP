#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif





//! Struct Kalman filter, real-numeric
typedef struct {
    float32 *vec_state;         //!< State vector (n_state size)
    float32 *vec_control;       //!< Control vector (n_control size)
    float32 *vec_measure;       //!< Measuring vector (n_state size)

    float32 *op_evo;        //!< Evolution operator (n_state x n_state size)
    float32 *op_ctrl;       //!< Control operator (n_state x n_control size)
    float32 *op_measure;    //!< Measuring operator (n_state x n_state size)

    float32 *cov_state;     //!< Covariation matrix of state (n_state x n_state size)

    count_t n_state;        //!< Size of state-vector
    count_t n_control;      //!< Size of control-vector

} kalman_f_t;


//! Kalman filter init
EXTERN int kalman_init_F(
        kalman_f_t *kalman,

        float32 *vec_state,
        float32 *vec_control,
        float32 *vec_measure,

        float32 *op_state,
        float32 *op_control,
        float32 *op_measure,

        float32 *corr_state,

        count_t n_state,
        count_t n_control,
        count_t n_measure
);

//! Kalman filter
EXTERN float32 kalman_process_F(kalman_f_t *kalman);



#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif



#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace statistic {
#endif



typedef struct {
	float32 y;				//!< Input y
	float32 x;				//!< Input x
	float32 tau;			//!< Time constant parameter
	float32 c[2]; 			//!< Regression coefficients. Order growup, for example: c[0] + c[1] * t
	float32 sse;
	float32 sy;
	float32 sx;
	float32 sxx;
	float32 sxy;
} regression_signal_f_t;


typedef struct {
	float32 y;				//!< Input y
	float32 x;				//!< Input x
	float32 tau;			//!< Time constant parameter
	float32 c[3]; 			//!< Regression coefficients. Order growup, for example: c[0] + c[1] * t + c[2] * t^2
	float32 sse;
	float32 sy;
	float32 sx;
	float32 sxx;
	float32 sxy;
} regression2_signal_f_t;



EXTERN void regression_signal_init_F(regression_signal_f_t *regsig);
EXTERN void regression_signal_process_F(regression_signal_f_t *regsig);

EXTERN void regression2_signal_init_F(regression2_signal_f_t *regsig);
EXTERN void regression2_signal_process_F(regression2_signal_f_t *regsig);



#ifdef __cplusplus
};	//namespace statistic
};	//namespace fastdsp
#endif


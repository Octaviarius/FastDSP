#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace statistic {
#endif



typedef struct {
	uint32_t quants;//!Quants
	float32 min;	//!Min
	float32 max;	//!Max
	float32 mean;	//!Mean
	float32 disp;	//!Dispersion
	float32 symm;	//!Symmetry
	float32 excess;	//!Excess
	float32 tau;	//!Time const
	float32 input;	//!Input
} statsignal_f_t;




EXTERN void statsignal_init_F(statsignal_f_t *stat);

//! Statistic signal, calc mean and other central momentums
EXTERN void statsignal_process_F(statsignal_f_t *stat);





#ifdef __cplusplus
};	//namespace statistic
};	//namespace fastdsp
#endif


#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
#endif


	EXTERN float32 sqr_F(float32 value);

	EXTERN float32 random_F(float32 vmin, float32 vmax);
	EXTERN void random_FV(float32 *ov, count_t n, float32 vmin, float32 vmax);

    EXTERN float32 inc_F(float32 *value);

	EXTERN float32 pow2_F(int power);


#ifdef __cplusplus
};	//namespace fastdsp
#endif




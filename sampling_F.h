#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace sampling{
#endif


EXTERN void sampling_resample_poly1_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in);
EXTERN void sampling_resample_poly2_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in);
EXTERN void sampling_decimate_F(float32 *ov, float32 *iv, count_t n, count_t factor);



#ifdef __cplusplus
};  //namespace sampling
};  //namespace fastdsp
#endif




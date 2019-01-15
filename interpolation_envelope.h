#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace interpolation {
#endif


//! Enveloping top line 1st order
EXTERN void envelope_top_FV(float32 *ov, float32 *iv, count_t n);
//! Enveloping bottom line 1st order
EXTERN void envelope_bottom_FV(float32 *ov, float32 *iv, count_t n);
//! Enveloping center line 1st order
EXTERN void envelope_center_FV(float32 *ov, float32 *iv, count_t n);





#ifdef __cplusplus
};	//namespace fastdsp
};	//namespace interpolation
#endif


#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace sampling{
#endif

/*! @brief Resampling signal by poly a0 + a1 * x
 */
EXTERN void sampling_resample_poly1_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in);

/*! @brief Resampling signal by poly a0 + a1 * x + a2 * x^2 + a3 * x^3
 * @warning input and output vector pointers must be not equal! Maybe in latest versions it fixed :)
 */
EXTERN void sampling_resample_poly3_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in);

/*! @brief Signal decimation. Calc ov[i] = iv[i*factor]
 */
EXTERN void sampling_decimate_F(float32 *ov, float32 *iv, count_t n, count_t factor);

/*! @brief Signal oversample. Calc ov[i] = sum(iv[i*factor] + iv[i*factor + 1] + ... + iv[(i+1)*factor - 1])
 */
EXTERN void sampling_oversample_F(float32 *ov, float32 *iv, count_t n, count_t factor);


#ifdef __cplusplus
};  //namespace sampling
};  //namespace fastdsp
#endif




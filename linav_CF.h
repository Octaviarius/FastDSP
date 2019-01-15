/*!
 * changelog:
 * 15.01.2019: Added max_CFS, min CFS
 */

#pragma once

#include "base.h"





#ifdef __cplusplus
namespace fastdsp {
namespace lina {
#endif

//! Convert real to complex number
EXTERN void convert_CI16_CF32(cfloat *ov, cshort *iv, count_t n);
//! Convert real to complex number
EXTERN void convert_CI32_CF32(cfloat *ov, clong *iv, count_t n);
//! Convert real to complex number
EXTERN void convert_FV_CFV(cfloat *ov, float32 *iv, count_t n);

//! Filling vector by value
EXTERN void fill_CFV(cfloat *iv, cfloat cs, count_t n);

//! Addition operation result = lv + rv
EXTERN cfloat add_CFS_CFS(cfloat ls, cfloat rs);
//! Addition operation ov[i] = lv[i] + rs. Sameness substraction operation realized by inverse rs -> -rs
EXTERN void add_CFV_CFS(cfloat *ov, cfloat *lv, cfloat rs, count_t n);
//! Addition operation ov[i] = lv[i] + rv[i]
EXTERN void add_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n);
//! Addition operation ov[i] = lv[i] + rv[i] * rs
EXTERN void add_CFV_CFV_CFS(cfloat *ov, cfloat *lv, cfloat *rv, cfloat rs, count_t n);
//! Addition operation ov[i] = lv[i] * ls + rv[i] * rs
EXTERN void add_CFV_CFV_CFS2(cfloat *ov, cfloat *lv, cfloat *rv, cfloat ls, cfloat rs, count_t n);
//! Addition operation ov[i] = lv[i] * ls + rv[i] * rs
EXTERN void add_CFV_CFV_FS2(cfloat *ov, cfloat *lv, cfloat *rv, float32 ls, float32 rs, count_t n);

//! Substraction operation result = lv - rv
EXTERN cfloat sub_CFS_CFS(cfloat ls, cfloat rs);
//! Substraction operation ov[i] = lv[i] - rv[i]
EXTERN void sub_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n);

//! Multiplication operation result = lv * rv
EXTERN cfloat mul_CFS_CFS(cfloat ls, cfloat rs);
//! Conjugated multiplication operation result = lv * rv'
EXTERN cfloat mul_CFS_cFS(cfloat ls, cfloat rs);
//! Multiplication operation result = lv * rv
EXTERN cfloat mul_CFS_FS(cfloat ls, float32 rs);
//! Multiplication operation ov[i] = lv[i] * rv[i]
EXTERN void mul_CFV_FS(cfloat *ov, cfloat *lv, float32 rs, count_t n);
//! Multiplication operation ov[i] = lv[i] * rv[i]
EXTERN void mul_CFV_FV(cfloat *ov, cfloat *lv, float32 *rv, count_t n);
//! Multiplication operation ov[i] = lv[i] * rv[i]
EXTERN void mul_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n);
//! Conjugated multiplication operation ov[i] = lv[i] * rv'[i]
EXTERN void mul_CFV_cFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n);
//! Multiplication operation ov[i] = iv[i] * rs
EXTERN void mul_CFV_CFS(cfloat *ov, cfloat *iv, cfloat rs, count_t n);
//! Scalar multiplication operation result = sum(lv[i] * rv[i])
EXTERN cfloat smul_CFV_CFV(cfloat *lv, cfloat *rv, count_t n);
//! Scalar multiplication with conjugated vector, operation result = sum(lv[i] * rv'[i])
EXTERN cfloat smul_CFV_cFV(cfloat *lv, cfloat *rv, count_t n);

//! Division operation result = lv / rv
EXTERN cfloat div_CFS_CFS(cfloat ls, cfloat rs);
//! Division operation ov[i] = lv[i] * rv[i]
EXTERN void div_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n);

//! Inverse operation ov[i] = 1 / lv[i]
EXTERN void inv_CFV(cfloat *ov, cfloat *iv, count_t n);

//! Summ operation result = sum(iv[i])
EXTERN cfloat sum_CFV(cfloat *iv, count_t n);

//! Absolute operation ov[i] = abs(iv[i])
EXTERN void abs_CFV(float32 *ov, cfloat *iv, count_t n);
//! Square absolute operation ov[i] = iv[i]^2
EXTERN void abs2_CFV(float32 *ov, cfloat *iv, count_t n);

//! Conjugate operation ov = iv'
EXTERN cfloat conjugate_CFS(cfloat is);
//! Conjugate operation ov[i] = iv'[i]
EXTERN void conjugate_CFV(cfloat *ov, cfloat *iv, count_t n);


//! Return magnitude of complex value
EXTERN float32 mag_CFS(cfloat is);
//! Return square magnitude of complex value
EXTERN float32 mag2_CFS(cfloat is);
//! Return magnitude of complex vector, element-wise
EXTERN void mag_CFV(float32 *ov, cfloat *iv, count_t n);
//! Return phase of complex value
EXTERN float32 phase_CFS(cfloat is);
//! Return phase of complex value
EXTERN void phase_CFV(float32 *ov, cfloat *iv, count_t n);

//! Return max cfloat value
EXTERN cfloat max_CFS(cfloat cs1, cfloat cs2);
//! Return min cfloat value
EXTERN cfloat min_CFS(cfloat cs1, cfloat cs2);
//! Find max idx complex-vector
EXTERN count_t max_CFV(cfloat *cs_max, cfloat *iv, count_t n);
//! Find min idx complex-vector
EXTERN count_t min_CFV(cfloat *cs_min, cfloat *iv, count_t n);


//! Compute mean value
EXTERN cfloat mean_CFV(cfloat *iv, count_t n);

//! Circle convolution
EXTERN void conv_circle_CFV(cfloat *ov, cfloat *iv, cfloat *kern, count_t n, count_t kern_size);

EXTERN void traverse_CFV(cfloat *ov, cfloat *iv, count_t n, pfunc_cf_t func);
EXTERN void traverse_CFV_CFV(cfloat *ov, cfloat *iv1, cfloat *iv2, count_t n, pfunc2_cf_t func);



#ifdef __cplusplus
};//namespace lina
};//namespace fastdsp
#endif


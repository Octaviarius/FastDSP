#pragma once

#include "base.h"
#include "base_cpp.h"






#ifdef __cplusplus
namespace fastdsp {
namespace lina {
#endif




//! Filling vector by value
EXTERN void fill_FV(float32 *iv, float32 cs, count_t n);


//! Addition operation ov[i] = lv[i] + rs. Sameness substraction operation realized by inverse rs -> -rs
EXTERN void add_FV_FS(float32 *ov, float32 *lv, float32 rs, count_t n);
//! Addition operation ov[i] = lv[i] + rv[i]
EXTERN void add_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);
//! Addition operation ov[i] = lv[i] + rv[i] * rs
EXTERN void add_FV_FV_FS(float32 *ov, float32 *lv, float32 *rv, float32 rs, count_t n);
//! Addition operation ov[i] = lv[i] * ls + rv[i] * rs
EXTERN void add_FV_FV_FS2(float32 *ov, float32 *lv, float32 *rv, float32 ls, float32 rs, count_t n);

//! Substraction operation ov[i] = lv[i] - rv[i]
EXTERN void sub_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);

//! Multiplication operation ov[i] = lv[i] * rv[i]
EXTERN void mul_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);
//! Multiplication operation ov[i] = iv[i] * rs
EXTERN void mul_FV_FS(float32 *ov, float32 *lv, float32 rs, count_t n);
//! Scalar multiplication operation result = sqrt( sum(lv[i] * rv[i]) )
EXTERN float32 smul_FV_FV(float32 *lv, float32 *rv, count_t n);

//! Division operation ov[i] = lv[i] * rv[i]
EXTERN void div_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);

//! Inverse operation ov[i] = 1 / lv[i]
EXTERN void inv_FV(float32 *ov, float32 *iv, count_t n);

//! Summ operation result = sum(iv[i])
EXTERN float32 sum_FV(float32 *iv, count_t n);

//! Absolute operation ov[i] = abs(iv[i])
EXTERN void abs_FV(float32 *ov, float32 *iv, count_t n);
//! Square absolute operation ov[i] = iv[i]^2
EXTERN void abs2_FV(float32 *ov, float32 *iv, count_t n);

//! Norm Euclid result = sqrt( sum( iv[i]^2 ) )
EXTERN float32 norm_euclid_FV(float32 *iv, count_t n);
//! Norm Manhatten result = sum( |iv[i]| )
EXTERN float32 norm_manh_FV(float32 *iv, count_t n);

//! Distance Euclid result = norm_euclid( lv - rv )
EXTERN float32 dist_euclid_FV(float32 *lv, float32 *rv, count_t n);
//! Distance Manhatten result = norm_manh( lv - rv )
EXTERN float32 dist_manh_FV(float32 *lv, float32 *rv, count_t n);

//! Normalize operation ov[i] = iv[i] / norm_euclid(iv)
EXTERN void normalize_FV(float32 *ov, float32 *iv, count_t n);



//! Find max idx real-vector
EXTERN count_t max_FV(float32 *cs_max, float32 *iv, count_t n);
//! Find min idx real-vector
EXTERN count_t min_FV(float32 *cs_min, float32 *iv, count_t n);

//! Max of two real-vector, element-wise
EXTERN void max_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);
//! Min of two real-vector, element-wise
EXTERN void min_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);

//! Constrain real value
EXTERN float32 constrain_FS(float32 is, float32 cs_min, float32 cs_max);
//! Constrain real-vector, element-wise
EXTERN void constrain_FV(float32 *ov, float32 *iv, float32 cs_min, float32 cs_max, count_t n);

//! Compute mean of real-vector
EXTERN float32 mean_FV(float32 *iv, count_t n);
//! Compute mean of square elements real-vector
EXTERN float32 mean2_FV(float32 *iv, count_t n);
//! Compute mean of square elements real-vector
EXTERN float32 mean3_FV(float32 *iv, count_t n);

//! Circle convolution
EXTERN void conv_circle_FV(float32 *ov, float32 *iv, float32 *kern, count_t n, count_t kern_size);

EXTERN float32 horner_FV(float32 ic, float32 *iv, count_t n);

EXTERN void traverse_FV(float32 *ov, float32 *iv, count_t n, pfunc_f_t func);
EXTERN void traverse_FV_FV(float32 *ov, float32 *iv1, float32 *iv2, count_t n, pfunc2_f_t func);


#ifdef __cplusplus
};	//namespace lina
};	//namespace fastdsp
#endif











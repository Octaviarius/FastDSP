#pragma once

#include "base.h"
#include "base_cpp.h"






#ifdef __cplusplus
namespace fastdsp {
namespace lina {
#endif




//! Filling vector by value
EXTERN void fill_FV(float32 *iv, float32 cs, count_t n);


//! Addition operation \f$ ov_{i} = lv_{i} + rs \f$ . Sameness substraction operation realized by inverse rs -> -rs
EXTERN void add_FV_FS(float32 *ov, float32 *lv, float32 rs, count_t n);
//! Addition operation  \f$ \vec{ov} = \vec{lv} + \vec{rv} \f$
EXTERN void add_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);
//! Addition operation  \f$ \vec{ov} = \vec{lv} + \vec{rv} * rs \f$
EXTERN void add_FV_FV_FS(float32 *ov, float32 *lv, float32 *rv, float32 rs, count_t n);
//! Addition operation  \f$ \vec{ov} = \vec{lv} * ls + \vec{rv} * rs \f$
EXTERN void add_FV_FV_FS2(float32 *ov, float32 *lv, float32 *rv, float32 ls, float32 rs, count_t n);

//! Substraction operation  \f$ \vec{ov} = \vec{lv} - \vec{rv} \f$
EXTERN void sub_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);

//! Multiplication operation  \f$ ov_{i} = lv_{i} * rv_{i} \f$
EXTERN void mul_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);
//! Multiplication operation  \f$ ov_{i} = iv_{i} * rs \f$
EXTERN void mul_FV_FS(float32 *ov, float32 *lv, float32 rs, count_t n);
//! Scalar multiplication operation  \f$ res = \vec{lv} \cdot \vec{rv} \f$
EXTERN float32 smul_FV_FV(float32 *lv, float32 *rv, count_t n);

//! Division operation  \f$ ov_{i} = lv_{i} * rv_{i} \f$
EXTERN void div_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);

//! Inverse operation  \f$ ov_{i} = \frac{1}{lv_{i}} \f$
EXTERN void inv_FV(float32 *ov, float32 *iv, count_t n);

//! Summ operation \f$ res = \sum_{i=0}^{n-1}{iv_{i}} \f$
EXTERN float32 sum_FV(float32 *iv, count_t n);

//! Absolute operation  \f$ ov_{i} = |iv_{i}| \f$
EXTERN void abs_FV(float32 *ov, float32 *iv, count_t n);
//! Square absolute operation  \f$ ov_{i} = iv_{i}^2 \f$
EXTERN void abs2_FV(float32 *ov, float32 *iv, count_t n);

//! Norm Euclid  \f$ res = \sqrt{ \sum_{i=0}^{n-1}{ iv_{i}^2 }} \f$
EXTERN float32 norm_euclid_FV(float32 *iv, count_t n);
//! Norm Manhatten \f$ res = \sum_{i=0}^{n-1}{ |iv_{i}| } \f$
EXTERN float32 norm_manh_FV(float32 *iv, count_t n);

//! Distance Euclid  \f$ res = EuclidNorm( \vec{lv} - \vec{rv} ) \f$
EXTERN float32 dist_euclid_FV(float32 *lv, float32 *rv, count_t n);
//! Distance Manhatten  \f$ res = ManhattenNorm( \vec{lv} - \vec{rv} ) \f$
EXTERN float32 dist_manh_FV(float32 *lv, float32 *rv, count_t n);

//! Normalize operation  \f$ \vec{ov} = \frac{\vec{iv}}{EuclidNorm(\vec{iv})} \f$
EXTERN void normalize_FV(float32 *ov, float32 *iv, count_t n);



//! Find max idx real-vector \f$ cs_{max} = \max{iv_i}, res = k : \exists cs_{max} = iv_{k} \f$
EXTERN count_t max_FV(float32 *cs_max, float32 *iv, count_t n);
//! Find min idx real-vector \f$ cs_{min} = \min{iv_i}, res = k : \exists cs_{min} = iv_{k} \f$
EXTERN count_t min_FV(float32 *cs_min, float32 *iv, count_t n);

//! Max of two real-vector, element-wise \f$ ov_{i} = \max{lv_{i}, rv_{i}} \f$
EXTERN void max_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n);
//! Min of two real-vector, element-wise \f$ ov_{i} = \min{lv_{i}, rv_{i}} \f$
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

//! Circle convolution \f$ ov_{i} = \sum_{k=0}^{kern\_size-1}{iv_{(i+k) \, mod \, n} * kern_{k}} \f$
EXTERN void conv_circle_FV(float32 *ov, float32 *iv, float32 *kern, count_t n, count_t kern_size);

//! Circle shift
EXTERN void circ_shift_FV(float32 *ov, float32 *iv, count_t n, count_t shift);

//! Horner polynom representation
EXTERN float32 horner_FV(float32 ic, float32 *iv, count_t n);

EXTERN void traverse_FV(float32 *ov, float32 *iv, count_t n, pfunc_f_t func);
EXTERN void traverse_FV_FV(float32 *ov, float32 *iv1, float32 *iv2, count_t n, pfunc2_f_t func);


#ifdef __cplusplus
};	//namespace lina
};	//namespace fastdsp
#endif











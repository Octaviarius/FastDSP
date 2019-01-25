#pragma once


/*!
 * Functions naming:
 *
 * function_{C,Q}[F,D][S,V,M,T](args...)
 * C,c,Q,q - complex, complex-conjugated, quaternion, quaternion-conjugated
 * F,D - float, double
 * S,V,M,T - scalar, vector, matrix, tensor
 *
 * Arguments naming
 *
 * {o,i,l,r,c}[s,v,m,t]
 * o,l,r,c - output, left-side, right-side, constant
 * s,v,m,t - scalar, vector, matrix, tensor
 * c - constant
 * M,N - size of dimension
 *
 */


#include "linav_F.h"
#include "linav_CF.h"
#include "linam_F.h"

#include "ext_math.h"

#include "filter_fir_F.h"
#include "filter_fir_CF.h"
#include "filter_iir_F.h"
#include "filter_iir_CF.h"
#include "filter_median_F.h"

#include "sampling_F.h"

#include "spectrum_fft_CF.h"
#include "spectrum_peaks.h"
#include "spectrum_window.h"

#include "statistic_statsignal_F.h"
#include "interpolation_envelope.h"
#include "statistic_regonfly_F.h"





#ifdef __cplusplus
namespace fastdsp {
#endif


EXTERN void memswap(void *s1, void *s2, size_t size);



#ifdef __cplusplus
}; //namespace fastdsp
#endif


#pragma once



#include "controller_pid_F.h"
#include "linav_F.h"
#include "linav_CF.h"
#include "linam_F.h"

#include "ext_math.h"

#include "filter_fir_F.h"
#include "filter_fir_CF.h"
#include "filter_iir_F.h"
#include "filter_iir_CF.h"
#include "filter_median_F.h"
#include "filter_kalman_F.h"

#include "sampling_F.h"

#include "spectrum_fft_CF.h"
#include "spectrum_peaks.h"
#include "spectrum_window.h"

#include "statistic_statsignal_F.h"
#include "statistic_regonfly_F.h"







#ifdef __cplusplus
namespace fastdsp {
#endif


EXTERN void memswap(void *s1, void *s2, size_t size);



#ifdef __cplusplus
}; //namespace fastdsp
#endif


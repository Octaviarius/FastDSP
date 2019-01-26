#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif





//! Struct Median filter, real-numeric
typedef struct {
	float32 		*buffer;
	count_t 		*idx_buffer;
	count_t			cb_index;
	count_t 		size;
	float32 		input;
	float32 		output;
} median_f_t;


//! Median filter init
EXTERN int median_init_F(
        median_f_t *median,
        float32 *buffer,
        count_t *idx_buffer,
        count_t size
);

//! Median filter
EXTERN float32 median_process_FS(median_f_t *median, float32 is, count_t quantile);

//! Median filter on vector
EXTERN void median_process_FV(float32 *ov, float32 *iv, count_t n, median_f_t *med, count_t quantile, count_t kern_center);




#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif



#pragma once


#include "base.h"


#ifdef __cplusplus
namespace fastdsp{
namespace spectrum{
#endif


typedef struct {
	float32 *weights;
	count_t size;
} window_f_t;



//! Window processing for real vectors
EXTERN void window_process_F(window_f_t *window, float32 *ov, float32 *iv, count_t n);
//! Window processing for complex vectors
EXTERN void window_process_CF(window_f_t *window, cfloat *ov, cfloat *iv, count_t n);

//! Rectangle window
EXTERN void window_rectangle_init_F(window_f_t *window);
//! Sinus window
EXTERN void window_sinus_init_F(window_f_t *window);
//! Lanczos window
EXTERN void window_lanczos_init_F(window_f_t *window);
//! Triangle(Bartlett) window
EXTERN void window_triangle_init_F(window_f_t *window);
//! Hann window
EXTERN void window_hann_init_F(window_f_t *window);
//! Bartlett-Hann window
EXTERN void window_bartlett_hann_init_F(window_f_t *window);
//! Hamming window
EXTERN void window_hamming_init_F(window_f_t *window);
//! Nuttall window
EXTERN void window_nuttall_init_F(window_f_t *window);
//! Blackman window
EXTERN void window_blackman_init_F(window_f_t *window);
//! Blackman-Harris window
EXTERN void window_blackman_harris_init_F(window_f_t *window);
//! Blackman-Nuttall window
EXTERN void window_blackman_nuttall_init_F(window_f_t *window);
//! Flat top window
EXTERN void window_flattop_init_F(window_f_t *window);
//! Gaussian window
EXTERN void window_gaussian_init_F(window_f_t *window, float32 sigma);


#ifdef __cplusplus
};
};
#endif





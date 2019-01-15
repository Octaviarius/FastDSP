#include "../spectrum_window.h"
#include "../linav_F.h"
#include "../linav_CF.h"


#ifdef __cplusplus
using namespace fastdsp::lina
namespace fastdsp{
namespace spectrum{
#endif


EXTERN void window_process_F(window_f_t *window, float32 *ov, float32 *iv, count_t n){
	if(window->size == n)
		mul_FV_FV(ov, iv, window->weights, window->size);
	else if(window->size < n){
		mul_FV_FV(ov, iv, window->weights, window->size);
		mul_FV_FS(&ov[n], &iv[n], window->weights[window->size-1], n - window->size);
	}else if(window->size > n){
		float32 k = (float32)(window->size-1) / (float32)(n-1);
		for(count_t i=0; i<n; i++){
			count_t j = (count_t)(k * i);
			*(ov++) = *(iv++) * window->weights[j];
		}
	}
}

EXTERN void window_process_CF(window_f_t *window, cfloat *ov, cfloat *iv, count_t n){
	if(window->size == n)
		mul_CFV_FV(ov, iv, window->weights, window->size);
	else if(window->size < n){
		mul_CFV_FV(ov, iv, window->weights, window->size);
		mul_CFV_FS(&ov[n], &iv[n], window->weights[window->size-1], n - window->size);
	}else if(window->size > n){
		float32 k = (float32)(window->size-1) / (float32)(n-1);
		for(count_t i=0; i<n; i++){
			count_t j = (count_t)(k * i);
			ov->re = iv->re * window->weights[j];
			(ov++)->im = (iv++)->im * window->weights[j];
		}
	}
}



EXTERN void window_rectangle_init_F(window_f_t *window){
	fill_FV(window->weights, 1.0, window->size);
}

EXTERN void window_sinus_init_F(window_f_t *window){
	float32 A = M_PI / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		window->weights[i] = sinf(A * i);
	}
}

EXTERN void window_lanczos_init_F(window_f_t *window){
	float32 A = 2.0 / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		float32 x = M_PI * (A * i - 1);
		if(x == 0)
			window->weights[i] = 1.0;
		else
			window->weights[i] = sinf(x) / (x);
	}
}

EXTERN void window_triangle_init_F(window_f_t *window){
	float32 A = 2.0 / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		window->weights[i] = 1 - fabsf(A * i - 1);
	}
}

EXTERN void window_hann_init_F(window_f_t *window){
	float32 A = 2.0 * M_PI / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		window->weights[i] = 0.5 - 0.5 * cosf(A * i);
	}
}

EXTERN void window_bartlett_hann_init_F(window_f_t *window){
	float32 A = 1.0 / (float32)(window->size - 1);
	float32 B = 2.0 * M_PI * A;
	for(count_t i=0; i<window->size; i++){
		window->weights[i] = 0.62 - 0.48 * (A*i-0.5) + 0.38 * cosf(B * i);
	}
}

EXTERN void window_hamming_init_F(window_f_t *window){
	float32 A = 2.0 * M_PI / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		window->weights[i] = 0.54 - 0.46 * cosf(A * i);
	}
}

EXTERN void window_nuttall_init_F(window_f_t *window){
	float32 A = 2.0 * M_PI / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		float32 tmp = A * i;
		window->weights[i] = 0.355768 - 0.4891775 * cosf(tmp) + 0.1365995 * cosf(2.0 * tmp) - 0.0106411 * cosf(3.0 * tmp);
	}
}

EXTERN void window_blackman_init_F(window_f_t *window){
	float32 A = 2.0 * M_PI / (float32)(window->size - 1);
	float32 B = 2*A;
	for(count_t i=0; i<window->size; i++){
		window->weights[i] = 0.42 - 0.5 * cosf(A * i) + 0.08 * cosf(B * i);
	}
}

EXTERN void window_blackman_harris_init_F(window_f_t *window){
	float32 A = 2.0 * M_PI / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		float32 tmp = A * i;
		window->weights[i] = 0.35875 - 0.48829 * cosf(tmp) + 0.14128 * cosf(2.0 * tmp) - 0.012604 * cosf(3.0 * tmp);
	}
}

EXTERN void window_blackman_nuttall_init_F(window_f_t *window){
	float32 A = 2.0 * M_PI / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		float32 tmp = A * i;
		window->weights[i] = 0.3635819 - 0.4891775 * cosf(tmp) + 0.1365995 * cosf(2.0 * tmp) - 0.0106411 * cosf(3.0 * tmp);
	}
}

EXTERN void window_flattop_init_F(window_f_t *window){
	float32 A = 2.0 * M_PI / (float32)(window->size - 1);
	for(count_t i=0; i<window->size; i++){
		float32 tmp = A * i;
		window->weights[i] = 1.0 - 1.93 * cosf(tmp) + 0.129 * cosf(2.0 * tmp) - 0.388 * cosf(3.0 * tmp) + 0.032 * cosf(4.0 * tmp);
	}
}

EXTERN void window_gaussian_init_F(window_f_t *window, float32 sigma){
	float32 A = 0.5 * (float32)(window->size - 1);
	float32 B = 1.0 / (sigma * A);
	for(count_t i=0; i<window->size; i++){
		float32 tmp = (i - A) * B;
		window->weights[i] = expf(-0.5 * tmp * tmp);
	}
}





#ifdef __cplusplus
};
};
#endif



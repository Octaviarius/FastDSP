#include "../ext_math.h"





#ifdef __cplusplus
namespace fastdsp {
#endif


EXTERN float32 sqr_F(float32 value){
	return value * value;
}





EXTERN float32 random_F(float32 vmin, float32 vmax){
	return vmin + ((float32)(unsigned)rand() * (0.5 / (float32)RAND_MAX)) * (vmax - vmin);
}


EXTERN void random_FV(float32 *ov, count_t n, float32 vmin, float32 vmax){
	while(n-->0)
		*(ov++) = random_F(vmin, vmax);
}




/*
EXTERN float32 pow2_F(int power){
	union{
		struct {
			uint32_t mantissa : 23;
			uint32_t exponent : 8;
			uint32_t sign : 1;
		}bit;
		//! тип float32
		float Vf32;
		uint32_t Vui32;
	} fb;
	fb.Vui32 = 0;
	fb.bit.exponent = 127+power;
	return fb.Vf32;
}
*/


#ifdef __cplusplus
};	//namespace fastdsp
#endif




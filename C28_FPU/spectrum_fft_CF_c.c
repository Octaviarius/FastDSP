#include <fastDSP/spectrum_fft_CF.h>






#ifdef __cplusplus
namespace fastdsp{
namespace spectrum{
#endif


EXTERN void fft_init_CF(fft_cf_t * cfft){
	count_t	i;
	count_t	TableSize;
	float	Rad;
	float	RadStep;

	RadStep = 1.57079632795f;	// RadStep = pi/2

	Rad = 0.0f;

	for(i=0; i < (cfft->Stages - 2); i++){
		RadStep = RadStep * 0.5f;
	}

	TableSize = (1 << (cfft->Stages - 1));
	TableSize = TableSize + (TableSize >> 1);

	for(i=0; i < TableSize; i++){
		cfft->CoefPtr[i] = sin(Rad);
		Rad = Rad + RadStep;
	}

}




#ifdef __cplusplus
};
};
#endif



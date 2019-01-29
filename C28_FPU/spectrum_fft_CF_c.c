#include "../spectrum_fft_CF.h"
#include "../linav_CF.h"





#ifdef __cplusplus
namespace fastdsp{
namespace spectrum{
#endif


EXTERN void fft_transform_CF_helper(fft_cf_t *cfft);



EXTERN int fft_init_CF(
        fft_cf_t *cfft,
        float32 *twiddles,
        count_t stages
){
    count_t	i;
    count_t	TableSize;
    float	Rad;
    float	RadStep;

	if(stages < 6)
		return -1;

    cfft->InPtr = NULL;
    cfft->OutPtr = NULL;
    cfft->CurrentInPtr = NULL;
    cfft->CurrentOutPtr = NULL;
    cfft->Stages = stages;
    cfft->FFTSize = 1UL<<stages;
    cfft->CoefPtr = twiddles;

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
	
	return 0;
}




EXTERN cfloat *fft_transform_CF(
        fft_cf_t *cfft,
        cfloat *in_buffer,
        cfloat *aux_buffer
){
	cfft->InPtr = in_buffer;
	cfft->OutPtr = aux_buffer;
	fft_transform_CF_helper(cfft);
	if(cfft->Stages & 1)
		return in_buffer;
	else
		return aux_buffer;
}





EXTERN cfloat *fft_itransform_CF(
        fft_cf_t *cfft,
        cfloat *in_buffer,
        cfloat *aux_buffer
){
	conjugate_CFV(in_buffer, in_buffer, cfft->FFTSize);
	cfft->InPtr = in_buffer;
	cfft->OutPtr = aux_buffer;
	fft_transform_CF_helper(cfft);
	if(cfft->Stages & 1)
		return in_buffer;
	else
		return aux_buffer;
}




#ifdef __cplusplus
};
};
#endif



#include "../spectrum_fft_CF.h"
#include "../linav_CF.h"





#ifdef __cplusplus
namespace fastdsp{
namespace spectrum{
#endif





count_t reverseBits(count_t x, count_t n) {
    count_t result = 0;
    count_t i;
    for (i = 0; i < n; i++, x >>= 1)
        result = (result << 1) | (x & 1);
    return result;
}









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
    (void)aux_buffer;
    cfft->InPtr = cfft->OutPtr = in_buffer;

    cfloat *pcomp = in_buffer;
    cfloat tmp;
    count_t n = cfft->FFTSize;
    count_t stages = cfft->Stages;

    float *tab_cos = &cfft->CoefPtr[0];
    float *tab_sin = &cfft->CoefPtr[n>>2];

    // Bit-reversed addressing permutation
    for (count_t i = 0; i < n; i++) {
        count_t j = reverseBits(i, stages);
        if (j > i) {
            tmp = pcomp[i];
            pcomp[i] = pcomp[j];
            pcomp[j] = tmp;
        }
    }


    // Cooley-Tukey decimation-in-time radix-2 FFT
    for (count_t size = 2; size <= n; size <<= 1) {
        count_t halfsize = size >> 1;
        count_t tablestep = n / size;
        for (count_t i = 0; i < n; i += size) {
            for (count_t j = i, k = 0; j < i + halfsize; j++, k += tablestep) {
                tmp.re = pcomp[j+halfsize].re * tab_cos[k] + pcomp[j+halfsize].im * tab_sin[k];
                tmp.im = -pcomp[j+halfsize].re * tab_sin[k] + pcomp[j+halfsize].im * tab_cos[k];
                pcomp[j + halfsize].re = pcomp[j].re - tmp.re;
                pcomp[j + halfsize].im = pcomp[j].im - tmp.im;
                pcomp[j].re += tmp.re;
                pcomp[j].im += tmp.im;
            }
        }
        if (size == n)  // Prevent overflow in 'size *= 2'
            break;
    }

    return in_buffer;
}






EXTERN cfloat *fft_itransform_CF(
        fft_cf_t *cfft,
        cfloat *in_buffer,
        cfloat *aux_buffer
){
    conjugate_CFV(in_buffer, in_buffer, cfft->FFTSize);
    return fft_transform_CF(cfft, in_buffer, aux_buffer);
}










#ifdef __cplusplus
}
}
#endif



#include "../filter_fir_CF.h"






#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif



EXTERN void fir_init_CF(
        fir_cf_t *fir,
        cfloat *weights,
        cfloat *buffer,
        count_t size
){
    cfloat v;

    fir->weights = weights;
    fir->buffer = buffer;
    fir->size = size;
    fir->cb_index = 0;
    v.im = v.re = 0.0;
    fir->input = v;
    fir->output = v;

    fill_CFV(buffer, v, size);
    v.re = 1.0 / (float32)size;
    fill_CFV(weights, v, size);
}




#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

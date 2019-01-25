#include "../filter_iir_CF.h"




#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif


EXTERN void iir_init_CF(
        iir_cf_t *iir,
        cfloat *weights_a,
        cfloat *weights_b,
        cfloat *buffer,
        count_t size_a,
        count_t size_b
){
    iir->weights_a = weights_a;
    iir->weights_b = weights_b;
    iir->buffer = buffer;
    iir->size_a = size_a;
    iir->size_b = size_b;
    iir->cb_index = 0;

    cfloat v;
    v.im = v.re = 0.0;
    iir->input = v;
    iir->output = v;

    fill_CFV(buffer, v, size_b);
    fill_CFV(weights_a, v, size_a);
    v.re = 1.0 / (float32)size_b;
    fill_CFV(weights_b, v, size_b);
}





#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

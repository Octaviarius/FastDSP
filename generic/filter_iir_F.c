#include "../filter_iir_F.h"




#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif

EXTERN void iir_init_F(
        iir_f_t *iir,
        float32 *weights_a,
        float32 *weights_b,
        float32 *buffer,
        count_t size_a,
        count_t size_b
){
    iir->weights_a = weights_a;
    iir->weights_b = weights_b;
    iir->buffer = buffer;
    iir->size_a = size_a;
    iir->size_b = size_b;
    iir->cb_index = 0;
    iir->input = 0.0;
    iir->output = 0.0;

    fill_FV(buffer, 0.0, size_b);
    fill_FV(weights_b, 1.0 / (float32)size_b, size_b);
    fill_FV(weights_a, 0.0, size_a);

}





#ifdef __cplusplus
}//namespace fastdsp
}//namespace filter
#endif



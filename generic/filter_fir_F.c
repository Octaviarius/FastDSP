#include "../filter_fir_F.h"




#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif


EXTERN void fir_init_F(
        fir_f_t *fir,
        float32 *weights,
        float32 *buffer,
        count_t size
){
    fir->weights = weights;
    fir->buffer = buffer;
    fir->size = size;
    fir->cb_index = 0;
    fir->input = 0.0;
    fir->output = 0.0;

    fill_FV(buffer, 0.0, size);
    fill_FV(weights, 1.0 / (float32)size, size);
}





#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

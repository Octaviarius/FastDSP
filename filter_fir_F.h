#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif



typedef struct {
    float32         *weights;
    float32         *buffer;
    count_t         cb_index;
    count_t         size;
    float32         input;
    float32         output;
} fir_f_t;



EXTERN void fir_init_F(
        fir_f_t *fir,
        float32 *weights,
        float32 *buffer,
        count_t size
);




#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif




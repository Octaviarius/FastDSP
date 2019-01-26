#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif



typedef struct {
    float32         *weights;	//!< Weights
    float32         *buffer;	//!< Circular buffer
    count_t         cb_index;	//!< Circular index of buffer 
    count_t         size;		//!< Weights and buffer sizes
    float32         input;		//!< Current input value
    float32         output;		//!< Current output value
} fir_f_t;



EXTERN int fir_init_F(
        fir_f_t *fir,
        float32 *weights,
        float32 *buffer,
        count_t size
);

EXTERN float32 fir_process_F(
        fir_f_t *fir,
        float32 input
);



#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif




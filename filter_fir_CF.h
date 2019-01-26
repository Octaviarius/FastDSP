#pragma once

#include "base.h"



#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif



//! FIR filter structure
typedef struct {
    cfloat          *weights;   //!< Weights
    cfloat          *buffer;    //!< Circular buffer
    count_t         cb_index;   //!< Circular index of buffer 
    count_t         size;       //!< Weights and buffer sizes
    cfloat          input;      //!< Current input value
    cfloat          output;     //!< Current output value
} fir_cf_t;




EXTERN int fir_init_CF(
        fir_cf_t *fir,
        cfloat *weights,
        cfloat *buffer,
        count_t size
);


EXTERN cfloat fir_process_CF(
        fir_cf_t *fir,
		cfloat input
);



#ifdef __cplusplus
}	//namespace filter
}	//namespace fastdsp
#endif


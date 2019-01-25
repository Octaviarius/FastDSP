#pragma once

#include "base.h"



#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif



//! FIR structure
typedef struct {
    cfloat          *weights;   //!< Weights
    cfloat          *buffer;    //!< Circular buffer
    count_t         cb_index;   //!< Circular index
    count_t         size;       //!< Weights and buffer sizes
    cfloat          input;      //!< Input value
    cfloat          output;     //!< Output filtered value
} fir_cf_t;




EXTERN void fir_init_CF(
        fir_cf_t *fir,
        cfloat *weights,
        cfloat *buffer,
        count_t size
);





#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif


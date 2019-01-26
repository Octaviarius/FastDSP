#pragma once

#include "base.h"



#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif



//! IIR canonical form
typedef struct {
    cfloat          *weights_a;     //!< Recursive coefficients
    cfloat          *weights_b;     //!< FIR coefficients
    cfloat          *buffer;        //!< Circular buffer
    count_t         cb_index;       //!< Circular buffer index
    count_t         size;       	//!< Circular buffer size. Size = max(size_a, size_b)
    count_t         size_a;         //!< Recursive weights count. Must size_a <= size_b
    count_t         size_b;         //!< FIR weghts count. Count same as circular buffer elements count
    cfloat          input;          //!< Input value
    cfloat          output;         //!< Output filtred value
} iir_cf_t;


EXTERN int iir_init_CF(
        iir_cf_t *iir,
        cfloat *weights_a,
        cfloat *weights_b,
        cfloat *buffer,
        count_t size_a,
        count_t size_b
);



EXTERN cfloat iir_process_CF(
        iir_cf_t *iir,
		cfloat input
);



#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif


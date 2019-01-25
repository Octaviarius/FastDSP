#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace filter {
#endif


//! IIR canonical form
typedef struct {
    float32         *weights_a;     //!< Recursive coefficients
    float32         *weights_b;     //!< FIR coefficients
    float32         *buffer;        //!< Circular buffer
    count_t         cb_index;       //!< Circular buffer index
    count_t         size_a;         //!< Recursive weights count
    count_t         size_b;         //!< FIR weghts count. Count same as circular buffer elements count
    float32         input;          //!< Input value
    float32         output;         //!< Output filtred value
} iir_f_t;



EXTERN void iir_init_F(
        iir_f_t *iir,
        float32 *weights_a,
        float32 *weights_b,
        float32 *buffer,
        count_t size_a,
        count_t size_b
);





#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif




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
    float32         *cbuffer;       //!< Circular buffer
    count_t         cb_index;       //!< Circular buffer index
    count_t         cb_size;       	//!< Circular buffer size. Size = max(size_a, size_b)
    count_t         size_a;         //!< Recursive weights count
    count_t         size_b;         //!< FIR weghts count. Count same as circular buffer elements count
    float32         input;          //!< Input value
    float32         output;         //!< Output filtred value
} iir_f_t;



EXTERN int iir_init_F(
        iir_f_t *iir,
        float32 *weights_a,
        float32 *weights_b,
        float32 *buffer,
        count_t size,
        count_t size_a,
        count_t size_b
);


EXTERN float32 iir_process_F(
        iir_f_t *iir,
		float32 input
);





#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif




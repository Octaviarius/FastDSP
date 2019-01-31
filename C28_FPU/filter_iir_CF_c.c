#include "../filter_iir_CF.h"
#include <string.h>



#ifdef __cplusplus
using namespace std;
namespace fastdsp {
namespace filter {
#endif


EXTERN int iir_init_CF(
        iir_cf_t *iir,
        cfloat *weights_a,
        cfloat *weights_b,
        cfloat *cbuffer,
        count_t cb_size,
        count_t size_a,
        count_t size_b
){
    if(cb_size < __max(size_a, size_b))
        return -1;
    iir->weights_a = weights_a;
    iir->weights_b = weights_b;
    iir->cbuffer = cbuffer;
    iir->cb_size = cb_size;
    iir->size_a = size_a;
    iir->size_b = size_b;
    iir->cb_index = 0;

    cfloat v;
    v.im = v.re = 0.0;
    iir->input = v;
    iir->output = v;

	memset(iir->cbuffer, 0, iir->cb_size * sizeof(*iir->cbuffer));
	memset(iir->weights_b, 0, iir->size_b * sizeof(*iir->weights_b));
	memset(iir->weights_a, 0, iir->size_a * sizeof(*iir->weights_a));
    iir->weights_b[0].re = 1.0;
	
	return 0;
}




#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

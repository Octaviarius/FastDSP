#include "../filter_fir_CF.h"
#include <string.h>

#ifdef __cplusplus
using namespace std;
namespace fastdsp {
namespace filter {
#endif



EXTERN int fir_init_CF(
        fir_cf_t *fir,
        cfloat *weights,
        cfloat *buffer,
        count_t size
){    	
    cfloat v = {.re = 0.0, .im = 0.0};
	fir->weights = weights;
    fir->buffer = buffer;
    fir->size = size;
    fir->cb_index = 0;
    fir->input = v;
    fir->output = v;

	memset(fir->buffer, 0, fir->size * sizeof(*fir->buffer));
	memset(fir->weights, 0, fir->size * sizeof(*fir->weights));
	fir->weights[0].re = 1.0;
	return 0;
}



#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

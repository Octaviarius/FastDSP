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






EXTERN cfloat fir_process_CF(
        fir_cf_t *fir,
		cfloat input
){
	cfloat *buff = fir->buffer;
	cfloat *weights = fir->weights;
    cfloat out = {.re = 0.0, .im = 0.0};
	count_t cidx = fir->cb_index;
	count_t sz = fir->size;
	count_t k;
	
	fir->input = input;
	//add new element in circled buffer
	if(cidx == 0)
		cidx = sz - 1;
	else
		cidx--;	
	fir->cb_index = cidx;
	buff[cidx] = input;
	
	//convolve
	buff += cidx;
	for(k=0; k<sz; k++){		
		out.re += weights->re * buff->re - weights->im * buff->im;
        out.im += weights->re * buff->im + weights->im * buff->re;
        weights++;
        buff++;
		if(++cidx == sz)
			buff = fir->buffer;		
	}
	
	return (fir->output = out);			
}




#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

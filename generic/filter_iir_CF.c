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
        cfloat *buffer,
        count_t size_a,
        count_t size_b
){

    iir->weights_a = weights_a;
    iir->weights_b = weights_b;
    iir->buffer = buffer;
    iir->size_a = size_a;
    iir->size_b = size_b;
    iir->size = __max(size_a, size_b);
    iir->cb_index = 0;

    cfloat v;
    v.im = v.re = 0.0;
    iir->input = v;
    iir->output = v;

	memset(iir->buffer, 0, iir->size * sizeof(*iir->buffer));
	memset(iir->weights_b, 0, iir->size_b * sizeof(*iir->weights_b));
	memset(iir->weights_a, 0, iir->size_a * sizeof(*iir->weights_a));
    iir->weights_b[0].re = 1.0;
	
	return 0;
}






EXTERN cfloat iir_process_CF(
        iir_cf_t *iir,
		cfloat input
){
	cfloat *buff;
	cfloat *weights;
	cfloat out;
	count_t cidx;
	count_t sz;
	count_t buff_sz = iir->size;
	count_t k;
	
	iir->input = out = input;
	
	//recursive part convolve
	sz = iir->size_a;	
	cidx = iir->cb_index;
	buff = &iir->buffer[cidx];
	weights = iir->weights_a;
	for(k=0; k<sz; k++){
        out.re -= weights->re * buff->re - weights->im * buff->im;
        out.re -= weights->re * buff->im - weights->im * buff->re;
        weights++;
        buff++;
		if(++cidx == buff_sz)
			buff = iir->buffer;		
	}
	
	//add value in circled buffer
	cidx = iir->cb_index;
	if(cidx == 0)
		cidx = buff_sz - 1;
	else
		cidx--;
	iir->cb_index = cidx;
	buff = &iir->buffer[cidx];
	*buff = out;
	
	//convolve 	
	sz = iir->size_b;	
	weights = iir->weights_b;
    out.re = out.im = 0.0;
    for(k=0; k<sz; k++){
        out.re += weights->re * buff->re - weights->im * buff->im;
        out.re += weights->re * buff->im - weights->im * buff->re;
        weights++;
        buff++;
		if(++cidx == buff_sz)
			buff = iir->buffer;		
	}		
	
	return (iir->output = out);	
}




#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

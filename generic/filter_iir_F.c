#include "../filter_iir_F.h"
#include <string.h>



#ifdef __cplusplus
using namespace std;
namespace fastdsp {
namespace filter {
#endif

EXTERN int iir_init_F(
        iir_f_t *iir,
        float32 *weights_a,
        float32 *weights_b,
        float32 *buffer,
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
    iir->input = 0.0;
    iir->output = 0.0;

	memset(iir->buffer, 0, iir->size * sizeof(*iir->buffer));
	memset(iir->weights_b, 0, iir->size_b * sizeof(*iir->weights_b));
	memset(iir->weights_a, 0, iir->size_a * sizeof(*iir->weights_a));
	iir->weights_b[0] = 1.0;
	
	return 0;
}







EXTERN float32 iir_process_F(
        iir_f_t *iir,
		float32 input
){
	float32 *buff;
	float32 *weights;
	float32 out;
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
        out -= *weights * *buff;
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
	out = 0.0;
    weights = iir->weights_b;
	for(k=0; k<sz; k++){
        out += *weights * *buff;
        weights++;
        buff++;
		if(++cidx == buff_sz)
			buff = iir->buffer;		
	}		
	
	return (iir->output = out);	
}





#ifdef __cplusplus
}//namespace fastdsp
}//namespace filter
#endif



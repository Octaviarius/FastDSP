#include "../filter_fir_F.h"
#include <string.h>



#ifdef __cplusplus
using namespace std;
namespace fastdsp {
namespace filter {
#endif


EXTERN int fir_init_F(
        fir_f_t *fir,
        float32 *weights,
        float32 *buffer,
        count_t size
){
    fir->weights = weights;
    fir->buffer = buffer;
    fir->size = size;
    fir->cb_index = 0;
    fir->input = 0.0;
    fir->output = 0.0;

	memset(fir->buffer, 0, fir->size * sizeof(*fir->buffer));
	memset(fir->weights, 0, fir->size * sizeof(*fir->weights));
	fir->weights[0] = 1.0;
	
	return 0;
}






EXTERN float32 fir_process_F(
        fir_f_t *fir,
		float32 input
){
	float32 *buff = fir->buffer;
	float32 *weights = fir->weights;
	float32 out = 0.0;
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
        out += *weights * *buff;
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

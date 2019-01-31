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




#ifdef __cplusplus
} //namespace fastdsp
} //namespace filter
#endif

#include "../filter_median_F.h"







#ifdef __cplusplus
namespace fastdsp {	//namespace fastdsp
namespace filter {	//namespace filter
#endif




EXTERN int median_init_F(
        median_f_t *median,
        float32 *buffer,
        count_t *idx_buffer,
        count_t size
){
    median->size = size;
    median->buffer = buffer;
    median->idx_buffer = idx_buffer;
    for(count_t i=0; i<size; i++){
        buffer[i] = 0.0;
        idx_buffer[i] = i;
	}
	median->input = median->output = 0;
	median->cb_index = 0;

    return 0;
}



EXTERN float32 median_process_FS(median_f_t *median, float32 is, count_t quantile) {
	count_t *idx = median->idx_buffer;
	float32 *buff = median->buffer;
	count_t size = median->size;
    count_t cidx = median->cb_index;
    count_t i;

	median->input = is;

	// handling circled buffer
    if(cidx == 0)
        cidx = size - 1;
    else
        cidx--;
    median->cb_index = cidx;

    buff[cidx] = is;

	idx = median->idx_buffer;
	for(i=0; i<size; i++){
        if(*(idx++) == cidx){
            cidx = i;
			break;
		}
	}

	idx = median->idx_buffer;
	count_t maxidx = 0;

    for(i=0; i<cidx; i++){
		if(buff[*(idx++)] > is){
			goto __found_max;
		}
	}

	idx++;
	i++;

	for( ; i<size; i++){
		if(buff[*(idx++)] >= is){
			i--;
			goto __found_max;
		}
	}

	i--;

__found_max:
	maxidx = i;



	count_t tmp_ui16;
    if(maxidx < cidx){

        idx = median->idx_buffer + cidx;
		tmp_ui16 = *idx;
        for(i=cidx-maxidx; i>0; i--){
			idx[0] = idx[-1];
			idx--;
		}

		*idx = tmp_ui16;

    }else if(maxidx > cidx){

        idx = median->idx_buffer + cidx;
		tmp_ui16 = *idx;

        for(i=maxidx-cidx; i>0; i--){
			idx[0] = idx[1];
			idx++;
		}

		*idx = tmp_ui16;
	}

	return median->output = buff[median->idx_buffer[quantile]];

}






//! Median filter handler function, real-vector
EXTERN void median_process_FV(float32 *ov, float32 *iv, count_t n, median_f_t *med, count_t quantile, count_t kern_center){
	if(kern_center > 0){
		count_t nn = n;
		float32 *iv_last = iv + n;
		iv = iv_last - kern_center;
		while(n-->0){
			if(iv >= iv_last)
				iv -= nn;
			*(ov++) = median_process_FS(med, *(iv++), quantile);
		}
	}else{
		while(n-->0){
			*(ov++) = median_process_FS(med, *(iv++), quantile);
		}
	}
}





#ifdef __cplusplus
};	//namespace filter
};	//namespace fastdsp
#endif


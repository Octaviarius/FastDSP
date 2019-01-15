#include "../spectrum_peaks.h"


#ifdef __cplusplus
namespace fastdsp {
namespace spectrum {
#endif


EXTERN count_t peaks_find_all_FV(
		count_t *idxbuffer,
		float32 *spectrum,
		count_t n
){
	uint16_t i;
	uint16_t pcount = 0;

	//first
	i=0;
	if( (spectrum[0] >= spectrum[n-1]) && (spectrum[0] >= spectrum[1]) ){
		idxbuffer[pcount++] = i;
	}
	i++;

	//medium
	for( ; i<n-1; i++){
		if( (spectrum[i] >= spectrum[i-1]) && (spectrum[i] >= spectrum[i+1]) ){
			idxbuffer[pcount++] = i;
		}
	}


	//last
	if( (spectrum[i] >= spectrum[i-1]) && (spectrum[i] >= spectrum[0]) ){
		idxbuffer[pcount++] = i;
	}

	return pcount;
}



EXTERN count_t peaks_find_nearest_FV(
		float32 *spectrum,
		float32 *app_apectrum,
		count_t start,
		count_t n
){

	return 0;
}







EXTERN peak_f_t peaks_find_max_IV(
		count_t *idxbuffer,
		count_t idxbuffer_size,
		float32 *spectrum,
		float32 *corr_profile,
		float32 threshold,
		count_t n
){
	register peak_f_t p;
	register uint16_t i,idx;

	p.value = 0.0;
	p.idx = -1;

	for(i=0; i<idxbuffer_size; i++){
		idx = idxbuffer[i];
		float32 corr_level = spectrum[idx] * corr_profile[idx];
		if( (corr_level > p.value) && (corr_level >= threshold) ){
			p.value = corr_level;
			p.idx = idx;
		}
	}

	if(p.idx > 0)
		p.value = spectrum[p.idx];
	return p;
}








EXTERN peak_f_t peaks_find_max_FV(
		float32 *spectrum,
		float32 *app_spectrum,
		float32 treshold,
		count_t n
){
	count_t i;
	peak_f_t result;
	float32 tmp;
	result.value = treshold;
	result.idx = -1;

	//begin
	tmp = spectrum[0] * app_spectrum[0];
	if( (spectrum[0] >= spectrum[n-1]) && (spectrum[0] >= spectrum[1]) && (tmp > result.value) ){
		result.value = tmp;
		result.idx = 0;
	}

	//middle
	for(i=1; i<n-1; i++){
		tmp = spectrum[i] * app_spectrum[i];
		if( (spectrum[i] >= spectrum[i-1]) && (spectrum[i] >= spectrum[i+1]) && (tmp > result.value) ){
			result.value = tmp;
			result.idx = i;
		}
	}

	tmp = spectrum[i] * app_spectrum[i];
	if( (spectrum[i] >= spectrum[i-1]) && (spectrum[i] >= spectrum[0]) && (tmp > result.value) ){
		result.value = tmp;
		result.idx = i;
	}

	if(result.idx != (count_t)-1)
		result.value = spectrum[result.idx];
	return result;
}







EXTERN float32 peaks_get_index_FS(float32 left_cs, float32 center_cs, float32 right_cs){
	return 0.5 * (left_cs - right_cs) / (left_cs - 2*center_cs + right_cs);
}



EXTERN float32 peaks_get_index_FV(float32 *spectrum, count_t n, count_t coarse_index){
	if(coarse_index == 0){
		return peaks_get_index_FS(spectrum[n-1], spectrum[coarse_index], spectrum[coarse_index+1]) + coarse_index;
	}else if(coarse_index == n-1){
		return peaks_get_index_FS(spectrum[coarse_index-1], spectrum[coarse_index], spectrum[0]) + coarse_index;
	}else{
		return peaks_get_index_FS(spectrum[coarse_index-1], spectrum[coarse_index], spectrum[coarse_index+1]) + coarse_index;
	}
}



EXTERN void peaks_retouch_zone_FV(float32 *spectrum, count_t n, count_t center, count_t span){
	count_t x1 = center - span;
	count_t x2 = center + span;
	count_t l = center - 2*span;
	count_t r = center + 2*span;

	for(count_t p = x1; p<=x2; p++){
		spectrum[p] = 0.5 * (spectrum[l++] + spectrum[r++]);
	}
}


EXTERN void peaks_retouch_zone_CFV(cfloat *spectrum, count_t n, count_t center, count_t span){
	count_t x1 = center - span;
	count_t x2 = center + span;
	count_t l = center - 2*span;
	count_t r = center + 2*span;

	for(count_t p = x1; p<=x2; p++){
		spectrum[p].re = 0.5 * (spectrum[l].re + spectrum[r].re);
		spectrum[p].im = 0.5 * (spectrum[l++].im + spectrum[r++].im);
	}
}




#ifdef __cplusplus
};	//namespace spectrum
};	//namespace fastdsp
#endif



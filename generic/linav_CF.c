#include "../linav_CF.h"
#include <math.h>





#ifdef __cplusplus
namespace fastdsp {	//namespace fastdsp
namespace lina {	//namespace lina
#endif



EXTERN void convert_CI16_CF32(cfloat *ov, cshort *iv, count_t n){
	register cfloat tmp;
	ov += n;
	iv += n;
	while(n-->0){
		iv--;
		ov--;
		tmp.im = (float32)iv->im * (float32)(1.0 / (float32)(1UL<<15));
		tmp.re = (float32)iv->re * (float32)(1.0 / (float32)(1UL<<15));
		ov->im = tmp.im;
		ov->re = tmp.re;
	}
}


EXTERN void convert_CI32_CF32(cfloat *ov, clong *iv, count_t n){
	ov += n;
	iv += n;
	while(n-->0){
		iv--;
		ov--;
		ov->re = (float32)iv->re * (float32)(1.0 / (float32)(1UL<<15));
		ov->im = (float32)iv->im * (float32)(1.0 / (float32)(1UL<<15));
	}
}


EXTERN void convert_FV_CFV(cfloat *ov, float32 *iv, count_t n){
	while(n-->0){
		ov->re = *iv;
		ov->im = 0.0;
		iv++;
		ov++;
	}
}


EXTERN void fill_CFV(cfloat *iv, cfloat cs, count_t n){
	while(n-->0){
		*(iv++) = cs;
	}
}


EXTERN cfloat add_CFS_CFS(cfloat lv, cfloat rv){
	lv.re += rv.re;
	lv.im += rv.im;
	return lv;
}

EXTERN void add_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n){
	while(n-->0){
		ov->re = lv->re + rv->re;
		ov->im = lv->im + rv->im;
		lv++;
		rv++;
		ov++;
	}
}

EXTERN void add_CFV_CFS(cfloat *ov, cfloat *lv, cfloat rs, count_t n){
	while(n-->0){
		ov->re = lv->re + rs.re;
		ov->im = lv->im + rs.im;
		lv++;
		ov++;
	}
}

EXTERN void add_CFV_CFV_CFS(cfloat *ov, cfloat *lv, cfloat *rv, cfloat rs, count_t n){
	while(n-->0){
		ov->re = lv->re + rv->re * rs.re - rv->im * rs.im;
		ov->im = lv->im + rv->re * rs.im - rv->im * rs.re;
		lv++;
		rv++;
		ov++;
	}
}

EXTERN void add_CFV_CFV_CFS2(cfloat *ov, cfloat *lv, cfloat *rv, cfloat ls, cfloat rs, count_t n){
	while(n-->0){
		ov->re = lv->re * ls.re - lv->im * ls.im + rv->re * rs.re - rv->im * rs.im;
		ov->im = lv->re * ls.im + lv->im * ls.re + rv->re * rs.im + rv->im * rs.re;
		lv++;
		rv++;
		ov++;
	}
}


EXTERN void add_CFV_CFV_FS2(cfloat *ov, cfloat *lv, cfloat *rv, float32 ls, float32 rs, count_t n){
	while(n-->0){
		ov->re = lv->re * ls + rv->re * rs;
		ov->im = lv->im * ls + rv->im * rs;
		lv++;
		rv++;
		ov++;
	}
}


EXTERN cfloat sub_CFS_CFS(cfloat lv, cfloat rv){
	lv.re -= rv.re;
	lv.im -= rv.im;
	return lv;
}

EXTERN void sub_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n){
	while(n-->0){
		ov->re = lv->re - rv->re;
		ov->im = lv->im - rv->im;
		lv++;
		rv++;
		ov++;
	}
}



EXTERN cfloat mul_CFS_CFS(cfloat lv, cfloat rv){
	cfloat result;
	result.re = lv.re * rv.re - lv.im * rv.im;
	result.im = lv.re * rv.im + lv.im * rv.re;
	return result;
}


EXTERN cfloat mul_CFS_cFS(cfloat lv, cfloat rv){
	cfloat result;
	result.re = lv.re * rv.re + lv.im * rv.im;
	result.im = lv.im * rv.re - lv.re * rv.im;
	return result;
}


EXTERN cfloat mul_CFS_FS(cfloat lv, float32 rv){
	lv.re += lv.re * rv;
	lv.im += lv.im * rv;
	return lv;
}



EXTERN void mul_CFV_FS(cfloat *ov, cfloat *lv, float32 rs, count_t n){
	while(n-->0){
		ov->re = lv->re * rs;
		ov->im = lv->im * rs;
		lv++;
		ov++;
	}
}


EXTERN void mul_CFV_FV(cfloat *ov, cfloat *lv, float32 *rv, count_t n){
	while(n-->0){
		ov->re = lv->re * rv[0];
		ov->im = lv->im * rv[0];
		lv++;
		rv++;
		ov++;
	}
}


EXTERN void mul_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n){
	while(n-->0){
		ov->re = lv->re * rv->re - lv->im * rv->im;
		ov->im = lv->re * rv->im + lv->im * rv->re;
		lv++;
		rv++;
		ov++;
	}
}

EXTERN void mul_CFV_cFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n){
	while(n-->0){
		ov->re = lv->re * rv->re + lv->im * rv->im;
		ov->im = lv->im * rv->re - lv->re * rv->im;
		lv++;
		rv++;
		ov++;
	}
}

EXTERN void mul_CFV_CFS(cfloat *ov, cfloat *lv, cfloat rs, count_t n){
	while(n-->0){
		ov->re = lv->re * rs.re - lv->im * rs.im;
		ov->im = lv->re * rs.im + lv->im * rs.re;
		lv++;
		ov++;
	}
}

EXTERN cfloat smul_CFV_CFV(cfloat *lv, cfloat *rv, count_t n){
	cfloat result = {.re = 0, .im = 0};
	while(n-->0){
		result.re += lv->re * rv->re - lv->im * rv->im;
		result.im += lv->re * rv->im + lv->im * rv->re;
		lv++;
		rv++;
	}
	return result;
}

EXTERN cfloat smul_CFV_cFV(cfloat *lv, cfloat *rv, count_t n){
	cfloat result = {.re = 0, .im = 0};
	while(n-->0){
		result.re += lv->re * rv->re + lv->im * rv->im;
		result.im += lv->im * rv->re - lv->re * rv->im;
		lv++;
		rv++;
	}
	return result;
}

EXTERN cfloat div_CFS_CFS(cfloat lv, cfloat rv){
	cfloat result;
	float32 div_coeff = 1.0 / (rv.re * rv.re + rv.im * rv.im);
	result.re = (lv.re * rv.re + lv.im * rv.im) * div_coeff;
	result.im = (lv.im * rv.re - lv.re * rv.im) * div_coeff;
	return result;
}

EXTERN void div_CFV_CFV(cfloat *ov, cfloat *lv, cfloat *rv, count_t n){
	float32 div_coeff; 
	while(n-->0){
		div_coeff = 1.0 / (rv->re * rv->re + rv->im * rv->im);
		ov->re = (lv->re * rv->re + lv->im * rv->im) * div_coeff;
		ov->im = (lv->im * rv->re - lv->re * rv->im) * div_coeff;
		lv++;
		rv++;
		ov++;
	}
}


EXTERN void inv_CFV(cfloat *ov, cfloat *iv, count_t n){
	float32 div_coeff; 
	while(n-->0){
		div_coeff = 1.0 / (iv->re * iv->re + iv->im * iv->im);
		ov->re = iv->re * div_coeff;
		ov->im = -iv->im * div_coeff;
		iv++;
		ov++;
	}
}


EXTERN cfloat sum_CFV(cfloat *iv, count_t n){
	cfloat result = {.re = 0.0, .im = 0.0};
	while(n-->0){
		result.re += iv->re;
		result.im += iv->im;
		iv++;
	}
	return result;
}


EXTERN void abs_CFV(float32 *ov, cfloat *iv, count_t n){
	while(n-->0){
		ov[0] = sqrt(iv->re * iv->re + iv->im * iv->im);
		iv++;
		ov++;
	}
}

EXTERN void abs2_CFV(float32 *ov, cfloat *iv, count_t n){
	while(n-->0){
		ov[0] = iv->re * iv->re + iv->im * iv->im;
		iv++;
		ov++;
	}
}



EXTERN cfloat conjugate_CFS(cfloat iv){
	iv.im = -iv.im;
	return iv;
}


EXTERN void conjugate_CFV(cfloat *ov, cfloat *iv, count_t n){
	while(n-->0){
		ov->re = iv->re;
		ov->im = -iv->im;
		iv++;
		ov++;
	}
}










EXTERN float32 mag_CFS(cfloat is){
	return sqrt(is.re * is.re + is.im * is.im);
}

EXTERN float32 mag2_CFS(cfloat is){
	return is.re * is.re + is.im * is.im;
}

EXTERN void mag_CFV(float32 *ov, cfloat *iv, count_t n){
	abs_CFV(ov, iv, n);
}


EXTERN float32 phase_CFS(cfloat is){
	return atan2(is.im, is.re);
}


EXTERN void phase_CFV(float32 *ov, cfloat *iv, count_t n){
	while(n-->0){
		*(ov++) = atan2((iv++)->im, iv->re);
	}
}



EXTERN count_t max_CFV(cfloat *cs_max, cfloat *iv, count_t n){
	count_t imax = 0;
	float32 vmax = mag2_CFS(iv[imax]);
	for(count_t i=1; i<n; i++){
		float32 tmp = mag2_CFS(iv[i]);
		if(tmp > vmax){
			vmax = tmp;
			imax = i;
		}
	}
	*cs_max = iv[imax];
	return imax;
}

EXTERN count_t min_CFV(cfloat *cs_min, cfloat *iv, count_t n){
	count_t imin = 0;
	float32 vmin = mag2_CFS(iv[imin]);
	for(count_t i=1; i<n; i++){
		float32 tmp = mag2_CFS(iv[i]);
		if(tmp < vmin){
			vmin = tmp;
			imin = i;
		}
	}
	*cs_min = iv[imin];
	return imin;
}





EXTERN cfloat mean_CFV(cfloat *iv, count_t n){
	register cfloat result = {.re = 0.0, .im = 0.0};
	while(n-->0){
		result.re += (iv++)->re;
		result.im += (iv++)->im;
	}
	register float32 coeff = 1.0 / (float32)n;
	result.re *= coeff;
	result.im *= coeff;
	return result;
}




EXTERN void conv_circle_CFV(cfloat *ov, cfloat *iv, cfloat *kern, count_t n, count_t kern_size){
	register int k;
	register cfloat
		*arr,
		*arr_end = iv + n-1,
		*arr_beg = iv;

	while(n-->0){
		ov->re = 0.0;
		ov->im = 0.0;
		arr = arr_beg;
		for(k=0; k<kern_size; k++){
			ov->re += arr->re * kern[k].re - arr->im * kern[k].im;
			ov->im += arr->re * kern[k].im + arr->im * kern[k].re;
			if(arr > arr_end)	arr = iv;
		}
		if(++arr_beg > arr_end)	arr_beg = iv;
		ov++;
	}
}



EXTERN void traverse_CFV(cfloat *ov, cfloat *iv, count_t n, pfunc_cf_t func){
	while(n-->0)
		*(ov++) = func(*(iv++));
}


EXTERN void traverse_CFV_CFV(cfloat *ov, cfloat *iv1, cfloat *iv2, count_t n, pfunc2_cf_t func){
	while(n-->0)
		*(ov++) = func(*(iv1++), *(iv2++));
}





#ifdef __cplusplus
}	//namespace lina
}	//namespace fastdsp
#endif











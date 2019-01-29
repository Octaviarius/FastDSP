#include "../linav_F.h"
#include <math.h>






#ifdef __cplusplus
namespace fastdsp {	//namespace fastdsp
namespace lina {	//namespace lina
#endif


EXTERN void fill_FV(float32 *iv, float32 cs, count_t n){
	while(n-->0)
		*(iv++) = cs;
}



EXTERN void add_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) + *(rv++);
}

EXTERN void add_FV_FS(float32 *ov, float32 *lv, float32 rs, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) + rs;
}

EXTERN void add_FV_FV_FS(float32 *ov, float32 *lv, float32 *rv, float32 rs, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) + *(rv++) * rs;
}

EXTERN void add_FV_FV_FS2(float32 *ov, float32 *lv, float32 *rv, float32 ls, float32 rs, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) * ls + *(rv++) * rs;
}



EXTERN void sub_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) - *(rv++);
}



EXTERN void mul_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) * *(rv++);
}

EXTERN void mul_FV_FS(float32 *ov, float32 *lv, float32 rs, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) * rs;
}

EXTERN float32 smul_FV_FV(float32 *lv, float32 *rv, count_t n){
	float32 result = 0;
	while(n-->0)
		result += *(lv++) * *(rv++);
	return result;
}


EXTERN void div_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n){
	while(n-->0)
		*(ov++) = *(lv++) / *(rv++);
}


EXTERN void inv_FV(float32 *ov, float32 *iv, count_t n){
	while(n-->0)
		*(ov++) = 1.0 / *(iv++);
}


EXTERN float32 sum_FV(float32 *iv, count_t n){
	float32 result = 0;
	while(n-->0)
		result += *(iv++);
	return result;
}


EXTERN void abs_FV(float32 *ov, float32 *iv, count_t n){
	while(n-->0)
		*(ov++) = fabs(*(iv++));
}

EXTERN void abs2_FV(float32 *ov, float32 *iv, count_t n){
	while(n-->0)
		*(ov++) = *iv * *(iv++);
}


EXTERN float32 norm_euclid_FV(float32 *iv, count_t n){
	return sqrt(smul_FV_FV(iv, iv, n));
}

EXTERN float32 norm_manh_FV(float32 *iv, count_t n){
	float32 result = 0;
	while(n-->0)
		result += fabs(*(iv++));
	return result;
}


EXTERN float32 dist_euclid_FV(float32 *lv, float32 *rv, count_t n){
	float32 result = 0;
	while(n-->0)
		result += (*lv - *rv) * (*(lv++) - *(rv++));
	return sqrt(result);
}

EXTERN float32 dist_manh_FV(float32 *lv, float32 *rv, count_t n){
	float32 result = 0;
	while(n-->0)
		result += fabs(*(lv++) - *(rv++));
	return result;
}


EXTERN void normalize_FV(float32 *ov, float32 *iv, count_t n){
	float32 norm_coeff = 1.0 / norm_euclid_FV(iv, n);
	while(n-->0)
		*(ov++) = *(iv++) * norm_coeff;
}





EXTERN count_t max_FV(float32 *cs_max, float32 *iv, count_t n){
	count_t result;
	*cs_max = -FLT_MAX;
	while(n-->0){
		if(*cs_max < iv[n]){
			result = n;
			*cs_max = iv[n];
		}
	}
	return result;
}

EXTERN count_t min_FV(float32 *cs_min, float32 *iv, count_t n){
	count_t result;
	*cs_min = FLT_MAX;
	while(n-->0){
		if(*cs_min > iv[n]){
			result = n;
			*cs_min = iv[n];
		}
	}
	return result;
}



EXTERN void max_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n){
	while(n-->0){
		ov[n] = lv[n] > rv[n] ? lv[n] : rv[n];
	}
}


EXTERN void min_FV_FV(float32 *ov, float32 *lv, float32 *rv, count_t n){
	while(n-->0){
		ov[n] = lv[n] < rv[n] ? lv[n] : rv[n];
	}
}



EXTERN float32 amplitude_max_FV(float32 *iv, count_t n){
	float32 result = -FLT_MAX;
	while(n-->0){
		float32 tmp = fabs(iv[n]);
		if(result < tmp)
			result = tmp;
	}
	return result;
}





EXTERN float32 constrain_FS(float32 is, float32 cs_min, float32 cs_max){
	return is > cs_max ? cs_max : is < cs_min ? cs_min : is;
}


EXTERN void constrain_FV(float32 *ov, float32 *iv, float32 cs_min, float32 cs_max, count_t n){
	while(n-->0){
		ov[n] = iv[n] < cs_min ? cs_min : iv[n] > cs_max ? cs_max : iv[n];
	}
}



EXTERN float32 mean_FV(float32 *iv, count_t n){
	return sum_FV(iv, n) / (float32)n;
}


EXTERN float32 mean2_FV(float32 *iv, count_t n){
	float32 result = 0.0;
	while(n-->0){
		result += iv[n] * iv[n];
	}
	return result;
}


EXTERN float32 mean3_FV(float32 *iv, count_t n){
	float32 result = 0.0;
	while(n-->0){
		result += iv[n] * iv[n] * iv[n];
	}
	return result;
}




EXTERN void conv_circle_FV(float32 *ov, float32 *iv, float32 *kern, count_t n, count_t kern_size){
	register int k;
	register float32
		*arr,
		*arr_end = iv + n-1,
		*arr_beg = iv;

	while(n-->0){
		*ov = 0;
		arr = arr_beg;
		for(k=0; k<kern_size; k++){
			*ov += (*arr++) * kern[k];
			if(arr > arr_end)	arr = iv;
		}
		if(++arr_beg > arr_end)	arr_beg = iv;
		ov++;
	}

}



EXTERN void circ_shift_FV(float32 *ov, float32 *iv, count_t n, count_t shift){
    if(ov == iv){
        float32  *lptr = iv,
                *rptr = iv,
                *last = &iv[n - 1];

        float32 lval, rval;

        lval = *lptr;
        for(count_t i=n; i>0; i--){
            if(++rptr > last)
                rptr -= n;

            rval = *rptr;
            *rptr = lval;
            lval = rval;

            lptr = rptr;
        }

    }else{
        memcpy(ov + shift, iv, sizeof(*ov)*(n - shift));
        memcpy(ov, iv + (n - shift), sizeof(*ov)*shift);
    }
}






EXTERN void traverse_FV(float32 *ov, float32 *iv, count_t n, pfunc_f_t func){
	while(n-->0)
		*(ov++) = func(*(iv++));
}


EXTERN void traverse_FV_FV(float32 *ov, float32 *iv1, float32 *iv2, count_t n, pfunc2_f_t func){
	while(n-->0)
		*(ov++) = func(*(iv1++), *(iv2++));
}








#ifdef __cplusplus
}	//namespace lina
}	//namespace fastdsp
#endif

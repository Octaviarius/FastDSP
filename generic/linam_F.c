#include "../linam_F.h"
#include "../linav_F.h"

#include <math.h>
#include <string.h>





#ifdef __cplusplus
namespace fastdsp {	//namespace fastdsp
namespace lina {	//namespace lina
#endif




EXTERN void create_matrix_unity(float32 *om, count_t n){
	count_t n2 = n;
	memset(om, 0, n*n*sizeof(*om));	
	while(n2-->0){
		*om = 1.0;
		om += n + 1;
	};
};

EXTERN void create_matrix_diag(float32 *om, float32 *iv, count_t n){
	count_t n2 = n;
	memset(om, 0, n*n*sizeof(*om));	
	while(n2-->0){
		*om = *(iv++);
		om += n + 1;
	};
};


EXTERN void create_matrix_FV(float32 *om, float32 **iv, count_t n){
	count_t n2;
	float32 *vec;

	while(n-->0){
		vec = *(iv++);
		n2 = n;
		while(n2-->0){
			*(om++) = *(vec++);
		}
	}
}





EXTERN void row_FM_FV(float32 *ov, float32 *im, count_t row, count_t n[2]){
	count_t i;
	im += n[0] * row;
	for(i=0; i<n[1]; i++){
		ov[i] = *(im++);
	}
};


EXTERN void col_FM_FV(float32 *ov, float32 *im, count_t col, count_t n[2]){	
	count_t i;
	im += col;
	for(i=0; i<n[0]; i++){
		ov[i] = *im;
		im += n[0];
	}
};


EXTERN void row_FV_FM(float32 *im, float32 *iv, count_t row, count_t n[2]){
	count_t i;
	im = &im[n[0] * row];
	for(i=0; i<n[1]; i++){
		*(im++) = iv[i];
	}
};


EXTERN void col_FV_FM(float32 *im, float32 *iv, count_t col, count_t n[2]){
	count_t i;
	im = &im[col];
	for(i=0; i<n[0]; i++){
		*im = iv[i];
		im += n[0];
	}
};


EXTERN void row_perm_FM(float32 *im, count_t row1, count_t row2, count_t n[2]){
	count_t i;
	float32 *im2 = &im[row2 * n[0]];
	im = &im[n[0] * row1];
	for(i=0; i<n[1]; i++){
		float32 tmp = *im;
		*im = *im2;
		*im2 = tmp;
		im++;
		im2++;
	}
};


EXTERN void col_perm_FM(float32 *im, count_t col1, count_t col2, count_t n[2]){
	count_t i;
	float32 *im2 = &im[col2];
	im = &im[col1];
	for(i=0; i<n[1]; i++){
		float32 tmp = *im;
		*im = *im2;
		*im2 = tmp;
		im += n[0];
		im2 += n[0];
	}
};








EXTERN void add_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]){
	add_FV_FV(om, lm, rm, n[0] * n[1]);
};

EXTERN void add_FM_FM_FS(float32 *om, float32 *lm, float32 *rm, float32 rs, count_t n[2]){
	add_FV_FV_FS(om, lm, rm, rs, n[0] * n[1]);
};

EXTERN void add_FM_FM_FS2(float32 *om, float32 *lm, float32 *rm, float32 ls, float32 rs, count_t n[2]){
	add_FV_FV_FS2(om, lm, rm, ls, rs, n[0] * n[1]);
};


EXTERN void sub_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]){
	sub_FV_FV(om, lm, rm, n[0] * n[1]);
};


EXTERN void mul_FM_FS(float32 *om, float32 *lm, float32 rs, count_t n[2]){
	mul_FV_FS(om, lm, rs, n[0] * n[1]);
};

EXTERN void mul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]){
	mul_FV_FV(om, lm, rm, n[0] * n[1]);
};

EXTERN void mmul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]){
	count_t i,j,k;
	float32 cell_value;
	for(i=0; i<n[0]; i++){
		for(j=0; j<n[1]; j++){
			cell_value = 0.0;
			for(k=0; k<n[1]; k++){
				cell_value += lm[i*n[1]+k] * rm[k*n[1]+j];
			};
			om[i*n[1]+j] = cell_value;
		};
	};
};

EXTERN void mmul_FM_FV(float32 *ov, float32 *lm, float32 *rv, count_t n[2]){
	count_t i,j;
	memset(ov, 0, n[1]*sizeof(*ov));
	for(i=0; i<n[0]; i++){
		for(j=0; j<n[1]; j++){
			ov[i] += lm[i*n[1]+j] * rv[j];
		};
	};
};

EXTERN void mmul_FV_FM(float32 *ov, float32 *lm, float32 *rv, count_t n[2]){
	count_t i,j;
	memset(ov, 0, n[1]*sizeof(*ov));
	for(j=0; j<n[1]; j++){
		for(i=0; i<n[0]; i++){
			ov[i] += lm[i*n[1]+j] * rv[i];
		};
	};
};

EXTERN void tmul_FV_FM(float32 *ov, float32 *lm, float32 *rv, count_t n[2]){
	count_t i,j;
	for(i=0; i<n[0]; i++){
		for(j=0; j<n[1]; j++){
			ov[i*n[1]+j] += lm[i] * rv[j];
		}		
	}
};


EXTERN float32 track_FM(float32 *im, count_t n){
	float32 result = 0.0;
	count_t i, cnt = n;
	
	while(cnt-->0){
		result += im[i];
		i += n+1;
	}
	return result;
};


EXTERN float32 det_FM(float32 *im, count_t n){
	count_t i,j,k;
	float32 result, mult_value;
	
	for(i=0; i<n; i++){
		mult_value = 1.0;
		k = i;
		for(j=0; j<n; j++){			
			if(k > n)
				k = 0;
			mult_value *= im[j*n+k];
			k++;
		}	
		result += mult_value;
	}
	return result;
};


EXTERN float32 det2_FM(mat2_f_t *im, count_t n){
	return im->m00 * im->m11 - im->m01 * im->m10;
}

EXTERN float32 det3_FM(mat3_f_t *im, count_t n){
	return 	im->m00 * im->m11 * im->m22 +
			im->m01 * im->m12 * im->m20 +
			im->m02 * im->m10 * im->m21 -

			im->m02 * im->m11 * im->m20 -
			im->m01 * im->m10 * im->m22 -
			im->m00 * im->m12 * im->m21;
}

EXTERN float32 det4_FM(mat4_f_t *im, count_t n){
	return 	im->m00 * im->m11 * im->m22 * im->m33 +
			im->m01 * im->m12 * im->m23 * im->m30 +
			im->m02 * im->m13 * im->m20 * im->m31 +
			im->m03 * im->m10 * im->m21 * im->m32 -

			im->m03 * im->m12 * im->m21 * im->m30 -
			im->m02 * im->m11 * im->m20 * im->m33 -
			im->m01 * im->m10 * im->m23 * im->m32 -
			im->m00 * im->m13 * im->m22 * im->m31;
}

EXTERN float32 det5_FM(mat5_f_t *im, count_t n){
	return 	im->m00 * im->m11 * im->m22 * im->m33 * im->m44 +
			im->m01 * im->m12 * im->m23 * im->m34 * im->m40 +
			im->m02 * im->m13 * im->m24 * im->m30 * im->m41 +
			im->m03 * im->m14 * im->m20 * im->m31 * im->m42 +
			im->m04 * im->m10 * im->m21 * im->m32 * im->m43 -

			im->m04 * im->m13 * im->m22 * im->m31 * im->m40 -
			im->m03 * im->m12 * im->m21 * im->m30 * im->m44 -
			im->m02 * im->m11 * im->m20 * im->m34 * im->m43 -
			im->m01 * im->m10 * im->m24 * im->m33 * im->m42 -
			im->m00 * im->m14 * im->m23 * im->m32 * im->m41;
}




EXTERN void transpose_FM(float32 *om, float32 *im, count_t n[2]){
	count_t i,j;
	
	for(i=0; i<n[0]; i++){
		for(j=0; j<n[1]; j++){			
			om[i*n[1]+j] = im[j*n[1]+i];
		}	
	}
};


EXTERN void inv_FM(float32 *om, float32 *im, count_t n){
	count_t nn[] = {n, n};
	transpose_FM(om, im, nn);
	normalize_FM(om, om, n);
};


EXTERN void normalize_FM(float32 *om, float32 *im, count_t n){
	count_t nn[] = {n, n};
	mul_FM_FS(om, im, 1.0 / det_FM(im, n), nn);
};


EXTERN void symmetrify_FM(float32 *om, float32 *im, count_t n[2]){

};

EXTERN void antisymmetrify_FM(float32 *om, float32 *im, count_t n[2]){

};


EXTERN void diagonalization_FM(float32 *om, float32 *im, count_t n[2]){

};



#ifdef __cplusplus
};	//namespace lina
};	//namespace fastdsp
#endif











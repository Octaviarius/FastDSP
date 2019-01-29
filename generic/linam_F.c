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
	for(i=0; i<n[0]; i++){
	    ov[i] = 0.0;
		for(j=0; j<n[1]; j++){
			ov[i] += lm[i*n[1]+j] * rv[j];
		};
	};
};

EXTERN void mmul_FV_FM(float32 *ov, float32 *lv, float32 *rm, count_t n[2]){
	count_t i,j;
	memset(ov, 0, n[1]*sizeof(*ov));
	for(i=0; i<n[1]; i++){
	    ov[i] = 0.0;
	    for(j=0; j<n[0]; j++){
			ov[i] += rm[j*n[1]+i] * lv[j];
		};
	};
};

EXTERN void tmul_FV_FV(float32 *om, float32 *lv, float32 *rv, count_t n[2]){
	count_t i,j;
	for(i=0; i<n[0]; i++){
		for(j=0; j<n[1]; j++){
			om[i*n[1]+j] += lv[i] * rv[j];
		}		
	}
};


EXTERN float32 track_FM(float32 *im, count_t n){
	float32 result = 0.0;
	count_t cnt = n;
	
	while(cnt-->0){
	    im += n + 1;
		result += *im;
	}
	return result;
};


EXTERN float32 det_FM(float32 *im, float32 *aux_mat, count_t n){
    if(aux_mat != NULL){
        if(aux_mat != im)
            memcpy(aux_mat, im, n * n * sizeof(*im));
    }else
        aux_mat = im;

    // triangulate by Gauss method
    float32 coeff;
    float32 det = 1.0;
    float32 *str1, *str_base, *str2;
    count_t i,j,k;

    str_base = aux_mat;

    for(i=0; i<n; i++){

        // find row which i-col not equal 0.0
        if( (*str_base) == 0.0){
            str1 = str_base + n;
            for(j=i+1; j<n; j++){
                // find not-zero head and exchange rows
                if( (*str1) != 0.0){
                    str2 = str_base;
                    for(k=i; k<n; k++){
                        coeff = *str1;
                        *(str1++) = *str2;
                        *(str2++) = coeff;
                    }
                    break;
                }
                str1 += n;
            }
        }

        det *= (*str_base);
        //for each row
        for(j=i+1; j<n; j++){
            str1 = str_base;
            str2 = &aux_mat[j * n + i];     // pointer to relative row
            coeff = *str2 / *str1;          // calc relate coefficient

            //for each column of the row
            *(str2++) = 0.0;
            for(k=i+1; k<n; k++)
                *(str2++) -= *(str1++) * coeff;
        }//for j

        str_base += n + 1;  // update pointer to base row

    }//for i

    return det;
};


EXTERN float32 det2_FM(mat2_f_t *im){
	return im->m00 * im->m11 - im->m01 * im->m10;
}

EXTERN float32 det3_FM(mat3_f_t *im){
	return 	im->m00 * im->m11 * im->m22 +
			im->m01 * im->m12 * im->m20 +
			im->m02 * im->m10 * im->m21 -

			im->m02 * im->m11 * im->m20 -
			im->m01 * im->m10 * im->m22 -
			im->m00 * im->m12 * im->m21;
}




EXTERN void transpose_FM(float32 *om, float32 *im, count_t n[2]){
	count_t i,j;
	
	for(i=0; i<n[0]; i++){
		for(j=0; j<n[1]; j++){			
			om[i*n[1]+j] = im[j*n[1]+i];
		}	
	}
	count_t tmp = n[0];
	n[0] = n[1];
	n[1] = tmp;
};


EXTERN void inv_FM(float32 *om, float32 *im, count_t n){
	count_t nn[] = {n, n};
    normalize_FM(om, im, n);
	transpose_FM(om, om, nn);
};


EXTERN void normalize_FM(float32 *om, float32 *im, count_t n){
	count_t nn[] = {n, n};
	float32 det = det_FM(im, om, n);
	mul_FM_FS(om, im, 1.0 / det, nn);
};


EXTERN void symmetrify_FM(float32 *om, float32 *im, count_t n, matrix_symmetry_e symm){
    count_t i,j,ii,jj;

    if(symm == MATRIX_SYMMETRY){
        for(i=0; i<n-1; i++){
            for(j=i+1; j<n; j++){
                ii = j + n * i;
                jj = i + n * j;
                float32 tmp = 0.5 * (im[ii] + im[jj]);
                om[ii] = tmp;
                om[jj] = tmp;
            }
        }
    }else {

        for(i=0; i<n; i++){
            for(j=i; j<n; j++){
                ii = j + n * i;
                jj = i + n * j;
                float32 tmp = 0.5 * (im[ii] - im[jj]);
                om[ii] = tmp;
                om[jj] = -tmp;
             }
        }

    }
};



EXTERN void diagonalization_FM(float32 *om, float32 *im, count_t n){
    float32 coeff;
    float32 *str1, *str_base, *str2;
    if(om != im)
        memcpy(om, im, sizeof(*im) * n * n);

    count_t i,j,k;

    // left-side diagonalization
    for(i=0; i<n; i++){
        str_base = &om[i * (n + 1)];  // pointer to base row

        //for each row
        for(j=i+1; j<n; j++){
            str1 = str_base;
            str2 = &om[j * n + i];      // pointer to relative row
            coeff = *str2 / *str1;          // calc relate coefficient

            //for each column of the row
            *(str2++) = 0.0;
            for(k=i+1; k<n; k++)
                *(str2++) -= *(str1++) * coeff;
        }//for j
    }//for i

    // right-side diagonalization
    // all values, which not lay in diagonal will be assigned to zero
    for(i=0; i<n-1; i++){
        str_base = &om[i * n + i + 1];  // pointer to base row
        for(j=n-1; j>i; j--){
            *(str_base++) = 0.0;
        }
    }//for i

};



#ifdef __cplusplus
};	//namespace lina
};	//namespace fastdsp
#endif











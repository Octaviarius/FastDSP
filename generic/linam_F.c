#include "../fastdsp.h"

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
		*om = 1.0f;
		om += n + 1;
    }
}

EXTERN void create_matrix_diag(float32 *om, float32 *iv, count_t n){
	count_t n2 = n;
	memset(om, 0, n*n*sizeof(*om));	
	while(n2-->0){
		*om = *(iv++);
		om += n + 1;
    }
}


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





EXTERN void row_get_FM(float32 *ov, float32 *im, count_t row, count_t n[2]){
	count_t i;
	im += n[1] * row;
	for(i=n[1]; i>0; i--){
		*(ov++) = *(im++);
	}
}


EXTERN void col_get_FM(float32 *ov, float32 *im, count_t col, count_t n[2]){
	count_t i;
	im += col;
	for(i=n[0]; i>0; i--){
		*(ov++) = *im;
		im += n[1];
	}
}


EXTERN void row_set_FM(float32 *im, float32 *iv, count_t row, count_t n[2]){
    count_t i;
    im += n[1] * row;
    for(i=n[1]; i>0; i--){
        *(im++) = *(iv++);
    }
}


EXTERN void col_set_FM(float32 *im, float32 *iv, count_t col, count_t n[2]){
    count_t i;
    im += col;
    for(i=n[0]; i>0; i--){
        *im = *(iv++);
        im += n[1];
    }
}


EXTERN void row_perm_FM(float32 *im, count_t row1, count_t row2, count_t n[2]){
	count_t i;
    float32 *im2 = &im[row2 * n[1]];
    im = &im[n[1] * row1];
    for(i=n[1]; i>0; i--){
		float32 tmp = *im;
		*im = *im2;
		*im2 = tmp;
		im++;
		im2++;
	}
}


EXTERN void col_perm_FM(float32 *im, count_t col1, count_t col2, count_t n[2]){
	count_t i;
	float32 *im2 = &im[col2];
	im = &im[col1];
    for(i=n[1]; i>0; i--){
		float32 tmp = *im;
		*im = *im2;
		*im2 = tmp;
        im += n[1];
        im2 += n[1];
	}
}








EXTERN void add_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]){
	add_FV_FV(om, lm, rm, n[0] * n[1]);
}

EXTERN void add_FM_FM_FS(float32 *om, float32 *lm, float32 *rm, float32 rs, count_t n[2]){
	add_FV_FV_FS(om, lm, rm, rs, n[0] * n[1]);
}

EXTERN void add_FM_FM_FS2(float32 *om, float32 *lm, float32 *rm, float32 ls, float32 rs, count_t n[2]){
	add_FV_FV_FS2(om, lm, rm, ls, rs, n[0] * n[1]);
}


EXTERN void sub_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]){
	sub_FV_FV(om, lm, rm, n[0] * n[1]);
}


EXTERN void mul_FM_FS(float32 *om, float32 *lm, float32 rs, count_t n[2]){
	mul_FV_FS(om, lm, rs, n[0] * n[1]);
}

EXTERN void mul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]){
	mul_FV_FV(om, lm, rm, n[0] * n[1]);
}

EXTERN void mmul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t ln[2], count_t rn[2]){
	count_t i,j,k;
	float32 cell_value;
    float32 *row, *col;

    if(ln[1] != rn[0])
        return;

    for(i=0; i<ln[0]; i++){
        for(j=0; j<rn[1]; j++){
            row = &lm[i * ln[1]];       //pointer to row left matrix
            col = &rm[j];               //pointer to column right matrix
            cell_value = 0.0f;
            //convolve
            for(k=ln[1]; k>0; k--){
                cell_value += *(row++) * (*col);
                col += rn[1];
            }
            *(om++) = cell_value;
        }
    }
}

EXTERN void mmul_FM_FV(float32 *ov, float32 *lm, float32 *rv, count_t n[2]){
	count_t i,j;
    float32 *vec = rv;

    for(i=n[0]; i>0; i--){
        *ov = 0.0f;
        vec = rv;
        for(j=n[1]; j>0; j--)
            *ov += *(lm++) * *(vec++);
        ov++;
    }
}

EXTERN void mmul_FV_FM(float32 *ov, float32 *lv, float32 *rm, count_t n[2]){
    count_t i,j;
    float32 *vec_out;

    memset(ov, 0, n[1] * sizeof(float32));
    for(i=n[0]; i>0; i--){
        vec_out = ov;
        for(j=n[1]; j>0; j--)
            *(vec_out++) += *(rm++) * (*lv);
        lv++;
    }
}

EXTERN void tmul_FV_FV(float32 *om, float32 *lv, float32 *rv, count_t n[2]){
	count_t i,j;
    float32 *vec_l;
    for(i=n[0]; i>0; i--){
        vec_l = lv;
        for(j=n[1]; j>0; j--)
            *(om++) = *(vec_l++) * (*rv);
        rv++;
	}
}


EXTERN float32 track_FM(float32 *im, count_t n){
    float32 result = *im;
    count_t cnt = n-1;

    n++;
	while(cnt-->0){
        im += n;
		result += *im;
	}
	return result;
}


EXTERN float32 det_FM(float32 *im, float32 *aux_mat, count_t n){
    if(aux_mat == NULL)
        aux_mat = im;

    triangulation_FM(aux_mat, im, n);
    float32 det = 1.0f;
    count_t np1 = n+1;

    while(n-->0){
        det *= (*aux_mat);
        aux_mat += np1;
    }

    return det;
}


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
}


EXTERN void inv_FM(float32 *om, float32 *im, count_t n){
    count_t nn[] = {n, n};
    normalize_FM(om, im, n);
	transpose_FM(om, om, nn);
}


EXTERN void normalize_FM(float32 *om, float32 *im, count_t n){
    count_t nn[] = {n, n};
	float32 det = det_FM(im, om, n);
	mul_FM_FS(om, im, 1.0f / det, nn);
}


EXTERN void symmetrify_FM(float32 *om, float32 *im, count_t n, matrix_symmetry_e symm){
    count_t i,j,ii,jj;

    if(symm == MATRIX_SYMMETRY){
        for(i=0; i<n-1; i++){
            for(j=i+1; j<n; j++){
                ii = j + n * i;
                jj = i + n * j;
                float32 tmp = 0.5f * (im[ii] + im[jj]);
                om[ii] = tmp;
                om[jj] = tmp;
            }
        }
    }else {

        for(i=0; i<n; i++){
            for(j=i; j<n; j++){
                ii = j + n * i;
                jj = i + n * j;
                float32 tmp = 0.5f * (im[ii] - im[jj]);
                om[ii] = tmp;
                om[jj] = -tmp;
             }
        }

    }
}




EXTERN void triangulation_FM(float32 *om, float32 *im, count_t n){
    if(om != im)
        memcpy(om, im, n * n * sizeof(*im));

    // triangulate by Gauss method
    float32 coeff;
    float32 *row1, *row2, *row_base, vmax;
    count_t i,j,k;

    row_base = om;

    for(i=0; i<n-1; i++){

        // find row which i-col not max by module
        row2 = row_base;
        vmax = fabsf(*row_base);
        row1 = row_base + n;
        for(j=i+1; j<n; j++){
            if(vmax < fabsf(*row1)){
                vmax = fabsf(*row1);
                row2 = row1;
            }
            row1 += n;
        }

        //swap rows
        if(row2 != row_base)
            memswap(row_base, row2, (n-i)*sizeof(float32));

        //rows substruction
        row2 = row_base + n;
        for(j=i+1; j<n; j++){
            row1 = row_base;
            coeff = (*row2) / (*row1);
            for(k=i; k<n; k++){
                *(row2++) -= coeff * *(row1++);
            }
            row2 += i;
        }

        // update pointer to base row
        row_base += n + 1;

    }//for i

}


EXTERN void diagonalization_FM(float32 *om, float32 *im, count_t n){
    count_t i,j;

    // left-side diagonalization
    triangulation_FM(om, im, n);

    // right-side diagonalization
    // all values, which not lay in diagonal will be assigned to zero
    for(i=0; i<n; i++){
        for(j=0; j>n; j++){
            if(i == j)
                continue;
            *(om++) = 0.0f;
        }
    }//for i

}



#ifdef __cplusplus
}	//namespace lina
}	//namespace fastdsp
#endif











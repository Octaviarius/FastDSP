#pragma once

#include "base.h"






#ifdef __cplusplus
namespace fastdsp {
namespace lina {
#endif


typedef enum {
    MATRIX_SYMMETRY = 0,
    MATRIX_ANTISYMMETRY
} matrix_symmetry_e;



typedef struct {
	union{
		float32 m[2][2];
		struct{
			float32 m00; float32 m01;
			float32 m10; float32 m11;
		};
	};
} mat2_f_t;

typedef struct {
	union{
		float32 m[3][3];
		struct{
			float32 m00; float32 m01; float32 m02;
			float32 m10; float32 m11; float32 m12;
			float32 m20; float32 m21; float32 m22;
		};
	};
} mat3_f_t;

typedef struct {
	union{
		float32 m[4][4];
		struct{
			float32 m00; float32 m01; float32 m02; float32 m03;
			float32 m10; float32 m11; float32 m12; float32 m13;
			float32 m20; float32 m21; float32 m22; float32 m23;
			float32 m30; float32 m31; float32 m32; float32 m33;
		};
	};
} mat4_f_t;

typedef struct {
	union{
		float32 m[5][5];
		struct{
			float32 m00; float32 m01; float32 m02; float32 m03; float32 m04;
			float32 m10; float32 m11; float32 m12; float32 m13; float32 m14;
			float32 m20; float32 m21; float32 m22; float32 m23; float32 m24;
			float32 m30; float32 m31; float32 m32; float32 m33; float32 m34;
			float32 m40; float32 m41; float32 m42; float32 m43; float32 m44;
		};
	};
} mat5_f_t;





//! Creation unity matrix om[i,j] = (i == j) ? 1 : 0
EXTERN void create_matrix_unity(float32 *om, count_t n);
//! Creation diagonal matrix om[i,i] = iv[i]
EXTERN void create_matrix_diag(float32 *om, float32 *iv, count_t n);
//! Creation matrix from n-vectors with n-size
EXTERN void create_matrix_FV(float32 *om, float32 **iv, count_t n);


//! Create vector from matrix row
EXTERN void row_FM_FV(float32 *ov, float32 *im, count_t row, count_t n[2]);
//! Create vector from matrix column
EXTERN void col_FM_FV(float32 *ov, float32 *im, count_t col, count_t n[2]);

//! Assign vector to matrix row
EXTERN void row_FV_FM(float32 *im, float32 *iv, count_t row, count_t n[2]);
//! Assign vector to matrix col
EXTERN void col_FV_FM(float32 *im, float32 *iv, count_t col, count_t n[2]);

//! Row permutation
EXTERN void row_perm_FM(float32 *im, count_t row1, count_t row2, count_t n[2]);
//! Column permutation
EXTERN void col_perm_FM(float32 *im, count_t col1, count_t col2, count_t n[2]);

//! Addition operation om[i,j] = lm[i,j] + rm[i,j]
EXTERN void add_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]);
//! Addition operation om[i,j] = lm[i,j] + rm[i,j] * rs
EXTERN void add_FM_FM_FS(float32 *om, float32 *lm, float32 *rm, float32 rs, count_t n[2]);
//! Addition operation om[i,j] = lm[i,j] * ls + rm[i,j] * rs
EXTERN void add_FM_FM_FS2(float32 *om, float32 *lm, float32 *rm, float32 ls, float32 rs, count_t n[2]);

//! Substraction operation om[i,j] = lm[i,j] - rm[i,j]
EXTERN void sub_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]);

//! Multiplication matrix by scalar om[i,j] = im[i,j] * rs
EXTERN void mul_FM_FS(float32 *om, float32 *lm, float32 rs, count_t n[2]);
//! Multiplication matrixes element-wise operation om[i,j] = im[i,j] * rm[i,j]
EXTERN void mul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]);
//! Multiplication matrixes operation om[i,j] = lm[i,k] * rm[k,j]
EXTERN void mmul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]);
//! Multiplication matrix by vector, result is vector operation ov[i] = lm[i,k] * rv[k]
EXTERN void mmul_FM_FV(float32 *ov, float32 *lm, float32 *rv, count_t n[2]);
//! Multiplication vector by matrix, result is vector operation ov[j] = lv[k] * rm[k,j]
EXTERN void mmul_FV_FM(float32 *ov, float32 *lv, float32 *rm, count_t n[2]);
//! Tensor multiplication vector by vector, result is matrix  om[i,j] = lv[i] * rv[j]
EXTERN void tmul_FV_FV(float32 *om, float32 *lv, float32 *rv, count_t n[2]);

//! Get track result = im[i,i]
EXTERN float32 track_FM(float32 *im, count_t n);

/*! Get determinant of matrix result = im[i,i]
 * As a bonus after call function variable aux_mat will be triangulated
 * @warning If aux_mat == NULL or aux_mat == im, then 'im' matrix will be destroy by triangulation algorithm.
 */
EXTERN float32 det_FM(float32 *im, float32 *aux_mat, count_t n);
EXTERN float32 det2_FM(mat2_f_t *im);
EXTERN float32 det3_FM(mat3_f_t *im);

//! Get track om[i,j] = im[j,i]
EXTERN void transpose_FM(float32 *om, float32 *im, count_t n[2]);

/*! Inverse matrix om[i,j] = im[j,i] / det(im)
 * @warning 'om' must be not equal 'im', because @see det_FM
 */
EXTERN void inv_FM(float32 *om, float32 *im, count_t n);

/*! Normalize operation om[i,j] = im[i,j] / det(im)
 * @warning 'om' must be not equal 'im', because @see det_FM
 */
EXTERN void normalize_FM(float32 *om, float32 *im, count_t n);

//! Operation symmetrification om[i,j] == +-im[j,i]
EXTERN void symmetrify_FM(float32 *om, float32 *im, count_t n, matrix_symmetry_e symm);

//! Diagonalization om[i,i] = (i != j) 0 : im[i,j]
EXTERN void diagonalization_FM(float32 *om, float32 *im, count_t n);



#ifdef __cplusplus
}	//namespace lina
}	//namespace fastdsp
#endif











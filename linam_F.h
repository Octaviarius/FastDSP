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





//! Creation unity matrix \f$ om_{i,j} = (i == j) ? 1 : 0 \f$
EXTERN void create_matrix_unity(float32 *om, count_t n);
//! Creation diagonal matrix \f$ om_{i,i} = iv_{i} \f$
EXTERN void create_matrix_diag(float32 *om, float32 *iv, count_t n);
//! Creation matrix from n-vectors with n-size
EXTERN void create_matrix_FV(float32 *om, float32 **iv, count_t n);


//! Create vector from matrix row
EXTERN void row_get_FM(float32 *ov, float32 *im, count_t row, count_t n[2]);
//! Create vector from matrix column
EXTERN void col_get_FM(float32 *ov, float32 *im, count_t col, count_t n[2]);

//! Assign vector to matrix row
EXTERN void row_set_FM(float32 *im, float32 *iv, count_t row, count_t n[2]);
//! Assign vector to matrix col
EXTERN void col_set_FM(float32 *im, float32 *iv, count_t col, count_t n[2]);

//! Row permutation
EXTERN void row_perm_FM(float32 *im, count_t row1, count_t row2, count_t n[2]);
//! Column permutation
EXTERN void col_perm_FM(float32 *im, count_t col1, count_t col2, count_t n[2]);

//! Addition operation  \f$ om_{i,j} = lm_{i,j} + rm_{i,j} \f$
EXTERN void add_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]);
//! Addition operation  \f$ om_{i,j} = lm_{i,j} + rm_{i,j} * rs \f$
EXTERN void add_FM_FM_FS(float32 *om, float32 *lm, float32 *rm, float32 rs, count_t n[2]);
//! Addition operation om_{i,j} =  \f$ lm_{i,j} * ls + rm_{i,j} * rs \f$
EXTERN void add_FM_FM_FS2(float32 *om, float32 *lm, float32 *rm, float32 ls, float32 rs, count_t n[2]);

//! Substraction operation  \f$ om_{i,j} = lm_{i,j} - rm_{i,j} \f$
EXTERN void sub_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]);

//! Multiplication matrix by scalar  \f$ om_{i,j} = im_{i,j} * rs \f$
EXTERN void mul_FM_FS(float32 *om, float32 *lm, float32 rs, count_t n[2]);
//! Multiplication matrixes element-wise operation  \f$ om_{i,j} = im_{i,j} * rm_{i,j} \f$
EXTERN void mul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t n[2]);
//! Multiplication matrixes operation  \f$ om_{i,j} = lm_{i,k} * rm_{k,j} \f$
EXTERN void mmul_FM_FM(float32 *om, float32 *lm, float32 *rm, count_t ln[2], count_t rn[2]);
//! Multiplication matrix by col-vector, result is col-vector operation \f$ ov_{i} = lm_{i,k} * rv_{k} \f$
EXTERN void mmul_FM_FV(float32 *ov, float32 *lm, float32 *rv, count_t n[2]);
//! Multiplication row-vector by matrix, result is row-vector operation  \f$ ov_{j} = lv_{k} * rm_{k,j} \f$
EXTERN void mmul_FV_FM(float32 *ov, float32 *lv, float32 *rm, count_t n[2]);
//! Tensor multiplication row-vector by col-vector, result is matrix   \f$ om_{i,j} = lv_{i} * rv_{j} \f$
EXTERN void tmul_FV_FV(float32 *om, float32 *lv, float32 *rv, count_t n[2]);

//! Get track \f$ res = \sum_{i=0}^{n-1}{im_{i,i}} \f$
EXTERN float32 track_FM(float32 *im, count_t n);

/*! Get determinant of matrix \f$ rest = \det{im} \f$
 * As a bonus after call function variable aux_mat will be triangulated
 * @warning If aux_mat == NULL or aux_mat == im, then 'im' matrix will be destroy by triangulation algorithm.
 */
EXTERN float32 det_FM(float32 *im, float32 *aux_mat, count_t n);
EXTERN float32 det2_FM(mat2_f_t *im);
EXTERN float32 det3_FM(mat3_f_t *im);

//! Transpose \f$ om_{i,j} = im_{j,i} \f$
EXTERN void transpose_FM(float32 *om, float32 *im, count_t n[2]);

/*! Inverse matrix  \f$ om_{i,j} = im_{j,i} / \det{im} \f$
 * @warning 'om' must be not equal 'im', because @see det_FM
 */
EXTERN void inv_FM(float32 *om, float32 *im, count_t n);

/*! Normalize operation \f$ om_{i,j} = \frac{im_{i,j}}{\det{im}} \f$
 * @warning 'om' must be not equal 'im', because @see det_FM
 */
EXTERN void normalize_FM(float32 *om, float32 *im, count_t n);

//! Operation symmetrification \f$ om_{i,j} = im_{j,i} \f$
EXTERN void symmetrify_FM(float32 *om, float32 *im, count_t n, matrix_symmetry_e symm);

//! Triangulation matrix to  \f$ om_{i,i} = (i > j) ? 0 : matrix_{i,j} \f$
EXTERN void triangulation_FM(float32 *om, float32 *im, count_t n);

//! Diagonalization \f$ om_{i,i} = (i != j) ? 0 : matrix_{i,j} \f$
EXTERN void diagonalization_FM(float32 *om, float32 *im, count_t n);



#ifdef __cplusplus
}	//namespace lina
}	//namespace fastdsp
#endif











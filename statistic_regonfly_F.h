#pragma once

#include "base.h"

/*!
 * Regonfly - regression on fly. For most performance in realtime use this.
 */


#ifdef __cplusplus
namespace fastdsp {
namespace statistic {
#endif


typedef enum {
    REGONFLY_SUM = (1U<<0),             //!< Allow summation
    REGONFLY_CALC = (1U<<1),            //!< Allow calculation
    REGONFLY_MAINPASS= REGONFLY_SUM | REGONFLY_CALC,
} regonfly_e;


typedef struct {
    float32 y;              //!< Input y
    float32 x;              //!< Input x
    float32 tau;            //!< Time constant parameter
    float32 c[2];           //!< Regression coefficients y = c[0] + c[1] * x
    float32 m_y;
    float32 m_yx;
    float32 m_x;
    float32 m_x2;
} regonfly_poly1_f_t;


typedef struct {
    float32 y;              //!< Input y
    float32 x;              //!< Input x
    float32 tau;            //!< Time constant parameter
    float32 c[3];           //!< Regression coefficients y = c[0] + c[1] * x + c[2] * x^2
    float32 m_y;
    float32 m_yx;
    float32 m_yx2;
    float32 m_x;
    float32 m_x2;
    float32 m_x3;
    float32 m_x4;
} regonfly_poly2_f_t;


//! Init function for regression_onfly_poly1_f_t
EXTERN void regonfly_poly1_init_F(
        regonfly_poly1_f_t *obj
);

//! Regression on fly with polynome 1-order
EXTERN void regonfly_poly1_process_F(
        regonfly_poly1_f_t *obj,
        regonfly_e flags
);


//! Init function for regression_onfly_poly2_f_t
EXTERN void regonfly_poly2_init_F(
        regonfly_poly2_f_t *obj
);

//! Regression on fly with polynome 1-order
EXTERN void regonfly_poly2_process_F(
        regonfly_poly2_f_t *obj,
        regonfly_e flags
);



#ifdef __cplusplus
};  //namespace statistic
};  //namespace fastdsp
#endif

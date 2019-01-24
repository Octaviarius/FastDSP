#include "../statistic_regonfly_F.h"
#include "../ext_math.h"
#include "../linav_F.h"



#ifdef __cplusplus
namespace fastdsp {
namespace statistic {
#endif



EXTERN void regonfly_poly1_init_F(
    regonfly_poly1_f_t *obj
){
    memset(obj, 0, sizeof(*obj));
}


EXTERN void regonfly_poly1_process_F(
    regonfly_poly1_f_t *obj,
    regonfly_e flags
){
    float32 tau = obj->tau;

    if(flags & REGONFLY_SUM){
        obj->m_x += (obj->x - obj->m_x) * tau;
        obj->m_x2 += (obj->x*obj->x - obj->m_x2) * tau;
        obj->m_y += (obj->y - obj->m_y) * tau;
        obj->m_yx += (obj->x * obj->y - obj->m_yx) * tau;
    }

    if(flags & REGONFLY_CALC){
        obj->c[1] = (obj->m_yx - obj->m_x * obj->m_y) / (obj->m_x2 - sqr_F(obj->m_x));
        obj->c[0] = obj->m_y - obj->c[1] * obj->m_x;
    }

}







EXTERN void regonfly_poly2_init_F(
    regonfly_poly2_f_t *obj
){
    memset(obj, 0, sizeof(*obj));
}


EXTERN void regonfly_poly2_process_F(
        regonfly_poly2_f_t *obj,
        regonfly_e flags
){
    float32 tau = obj->tau;
    if(flags & REGONFLY_SUM){
        float xn, yxn;

        xn = obj->x; //x
        yxn = obj->y;//y
        obj->m_x += (xn - obj->m_x) * tau;
        obj->m_y += (yxn - obj->m_y) * tau;

        xn *= obj->x; //x^2
        yxn *= obj->x;//yx
        obj->m_x2 += (xn - obj->m_x2) * tau;
        obj->m_yx += (yxn - obj->m_yx) * tau;

        xn *= obj->x; //x^3
        yxn *= obj->x;//yx^2
        obj->m_x3 += (xn - obj->m_x3) * tau;
        obj->m_yx2 += (yxn - obj->m_yx2) * tau;

        xn *= obj->x; //x^4
        obj->m_x4 += (xn - obj->m_x4) * tau;
    }

    if(flags & REGONFLY_CALC){
        // SLAE: M * A = B
        float32 M[3][3];
        float32 B[3];

        M[0][0] = 1.0;
        M[0][1] = M[1][0] = obj->m_x;
        M[0][2] = M[2][0] = M[1][1] = obj->m_x2;
        M[1][2] = M[2][1] = obj->m_x3;
        M[2][2] = obj->m_x4;

        B[0] = obj->m_y;
        B[1] = obj->m_yx;
        B[2] = obj->m_yx2;
// this code is bugged, I don't know what happend
        // solve by Gauss method
        float32 k;
        // 1 stage
        k = M[1][0];
        M[1][0] = 0.0;
        M[1][1] -= M[0][1] * k;
        M[1][2] -= M[0][2] * k;
        B[1] -= B[0] * k;
        k = M[2][0];
        M[2][0] = 0.0;
        M[2][1] -= M[0][1] * k;
        M[2][2] -= M[0][2] * k;
        B[2] -= B[0] * k;
        // 2 stage
        k = M[2][1] / M[1][1];
        M[2][1] = 0.0;
        M[2][2] -= M[1][2] * k;
        B[2] -= B[1] * k;

        // reverse stage
        obj->c[2] = B[2] / M[2][2];
        obj->c[1] = (B[1] - M[1][2] * obj->c[2]) / M[1][1];
        obj->c[0] = (B[0] - M[0][2] * obj->c[2] - M[0][1] * obj->c[1]); // and div by M[0][0], but it equal 1.0;


/*
        //solve by Kramer method
        float32 detM =  M[0][0] * M[1][1] * M[2][2] +
                        M[1][0] * M[2][1] * M[0][2] +
                        M[2][0] * M[0][1] * M[1][2] -
                        M[2][0] * M[1][1] * M[0][2] -
                        M[1][0] * M[0][1] * M[2][2] -
                        M[0][0] * M[2][1] * M[1][2];

        float32 det0 =  B[0] * M[1][1] * M[2][2] +
                        B[1] * M[2][1] * M[0][2] +
                        B[2] * M[0][1] * M[1][2] -
                        B[2] * M[1][1] * M[0][2] -
                        B[1] * M[0][1] * M[2][2] -
                        B[0] * M[2][1] * M[1][2];

        float32 det1 =  M[0][0] * B[1] * M[2][2] +
                        M[1][0] * B[2] * M[0][2] +
                        M[2][0] * B[0] * M[1][2] -
                        M[2][0] * B[1] * M[0][2] -
                        M[1][0] * B[0] * M[2][2] -
                        M[0][0] * B[2] * M[1][2];

        float32 det2 =  M[0][0] * M[1][1] * B[2] +
                        M[1][0] * M[2][1] * B[0] +
                        M[2][0] * M[0][1] * B[1] -
                        M[2][0] * M[1][1] * B[0] -
                        M[1][0] * M[0][1] * B[2] -
                        M[0][0] * M[2][1] * B[1];
        obj->c[0] = det0 / detM;
        obj->c[1] = det1 / detM;
        obj->c[2] = det2 / detM;
*/
    }
}






#ifdef __cplusplus
};  //namespace statistic
};  //namespace fastdsp
#endif

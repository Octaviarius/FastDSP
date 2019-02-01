#include "../sampling_F.h"




#ifdef __cplusplus
namespace fastdsp { //namespace fastdsp
namespace lina {    //namespace lina
#endif




EXTERN void sampling_resample_poly1_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in){

    if(n_in == n_out){
        if(ov == iv)
            return;
        memcpy(ov, iv, n_in);
    }

    register count_t k;
    count_t i;
    float32 coeff = (float32)(--n_in) / (float32)(--n_out); //calc reduction coefficient and count convert to max index
    float32 fidx, tau;

    ov[0] = iv[0];
    ov[n_out] = iv[n_in];

    // downsampling
    if(n_in > n_out){

        for(i=1; i<n_out; i++){
            fidx = i * coeff;
            k = (count_t)fidx;
            tau = fidx - (float32)k;
            ov[i] = (1.0 - tau) * iv[k] + tau * iv[k+1];
        }

    // upsampling
    }else{

        for(i=n_out-1; i>0; i--){
            fidx = i * coeff;
            k = (count_t)fidx;
            tau = fidx - (float32)k;
            ov[i] = (1.0 - tau) * iv[k] + tau * iv[k+1];
        }

    }

}












// y[1] - left point, y[2] - right point. Other points for calc tangents. Left point relatively
static inline void cubic_lcoeffs(float32 a[4], const float32 y[4]){
    a[1] = 0.5 * (y[2] - y[0]);         // calc left tangent k0 and this equal a[1]
    a[0] = 0.5 * (y[3] - y[1]);         // calc right tangent k1
    a[3] = a[1] + a[0] + 2.0 * (y[1] - y[2]);
    a[2] = 0.5 * (a[0] - a[1] - 3.0 * a[3]);
    a[0] = y[1];
}
/*
// y[1] - left point, y[2] - right point. Other points for calc tangents. Right point relatively
static inline void cubic_rcoeffs(float32 a[4], const float32 y[4]){
    a[1] = 0.5 * (y[1] - y[3]);         // calc left tangent k0 and this equal a[1]
    a[0] = 0.5 * (y[0] - y[2]);         // calc right tangent k1
    a[3] = a[1] + a[0] + 2.0 * (y[2] - y[1]);
    a[2] = 0.5 * (a[0] - a[1] - 3.0 * a[3]);
    a[0] = y[2];
}
*/



static void resample3_helper(float32 *ov, float32 *iv, count_t n_out, count_t n_in){
    register count_t k;
    count_t i, last_k;
    float32 coeff = (float32)(--n_in) / (float32)(--n_out); //calc reduction coefficient and count convert to max index
    float32 fidx, a[4];
    float32 y[4];

    ov[0] = iv[0];
    ov[n_out] = iv[n_in];
    memcpy(&y[1], iv, 3*sizeof(float32));
    y[0] = 3.0 * y[1] - 3.0 * y[2] + y[3];
    cubic_lcoeffs(a, y);

    last_k = 0;
    for(i=1; i<n_out; i++){
        fidx = i * coeff;
        k = (count_t)fidx;

        if(last_k != k){
            if(k >= n_in - 1){
                memcpy(y, &iv[n_in-2], 3*sizeof(float32));
                y[3] = y[0] - 3.0 * y[1] + 3.0 * y[2];
                cubic_lcoeffs(a, y);
            }else
                cubic_lcoeffs(a, &iv[k-1]);
            last_k = k;
        }

        fidx = fidx - (float32)k;
        ov[i] = a[0] + fidx * (a[1] + fidx * (a[2] + fidx * a[3]));
    }
}


/*
static void resample3_overlaped_helper(float32 *ov, float32 *iv, count_t n_out, count_t n_in){
    register count_t k;
    count_t i, last_k;
    float32 coeff = (float32)(--n_in) / (float32)(--n_out); //calc reduction coefficient and count convert to max index
    float32 fidx, a[4], y[4], buff[2];


    // downsampling
    if(n_in > n_out){

        y[1] = iv[0];
        y[2] = iv[1];
        y[3] = iv[2];
        y[0] = 3.0 * y[1] - 3.0 * y[2] + y[3];

        buff[0] = iv[0];
        ov[n_out] = iv[n_in];

        cubic_lcoeffs(a, y);

        last_k = 0;

        for(i=1; i<n_out; i++){
            fidx = i * coeff;
            k = (count_t)fidx;

            if(last_k != k){
                if(k < n_in-1)
                    cubic_lcoeffs(a, &iv[k-1]);
                else{
                    memcpy(y, &iv[n_in-2], 3*sizeof(float32));
                    y[3] = y[0] - 3.0 * y[1] + 3.0 * y[2];
                    cubic_lcoeffs(a, y);
                }
                last_k = k;
            }

            fidx = fidx - (float32)k;
            buff[1] = buff[0];
            buff[0] = a[0] + fidx * (a[1] + fidx * (a[2] + fidx * a[3]));

            ov[i-1] = buff[1];
        }
        ov[i-1] = buff[0];

    // upsampling
    }else{

        y[0] = iv[n_in-2];
        y[1] = iv[n_in-1];
        y[2] = iv[n_in];
        y[3] = y[0] - 3.0 * y[1] + 3.0 * y[2];

        buff[0] = y[2];
        ov[0] = iv[0];

        cubic_lcoeffs(a, y);

        last_k = n_in-1;

        for(i=n_out-1; i>=1; i--){
            fidx = i * coeff;
            k = (count_t)(fidx + 0.99999999999999);
            if(k < n_in-1)
                cubic_lcoeffs(a, &iv[k-1]);
            else{
                y[0] = iv[n_in-2];
                y[1] = iv[n_in-1];
                y[2] = iv[n_in];
                y[3] = 3.0 * y[2] - 2.0 * y[1];
                cubic_lcoeffs(a, y);
            }

            if(last_k != k){
                y[3] = y[2];
                y[2] = y[1];
                y[1] = y[0];

                if(k == 0)
                    y[0] = 1.5 * (y[2] - y[1]);
                else
                    y[0] = iv[k-1];

                cubic_lcoeffs(a, y);
                last_k = k;
            }

            fidx = fidx - (float32)k;
            buff[2] = buff[1];
            buff[1] = buff[0];
            buff[0] = a[0] + fidx * (a[1] + fidx * (a[2] + fidx * a[3]));
            if(i+2 < n_out)
            ov[i+2] = buff[2];
        }
        ov[2] = buff[1];
        ov[1] = buff[0];

    }
}
*/

EXTERN void sampling_resample_poly3_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in){

    if(n_in == n_out){
        if(ov == iv)
            return;
        memcpy(ov, iv, n_in);
    }else{
       resample3_helper(ov, iv, n_out, n_in);
    }

}



EXTERN void sampling_decimate_F(float32 *ov, float32 *iv, count_t n, count_t factor){
    register count_t i;
    for(i=0; i<n; i+=factor){
        *(ov++) = *(iv);
        iv += factor;
    }
}

EXTERN void sampling_oversample_F(float32 *ov, float32 *iv, count_t n, count_t factor){
    register count_t i;
    register float32 summ = 0.0;

    while(n-- > 0){
        summ += *(iv++);
        if(++i >= factor){
            *(ov++) = summ;
            summ = 0.0;
            i = 0;
        }
    }
}



#ifdef __cplusplus
} //namespace fastdsp
}    //namespace lina
#endif






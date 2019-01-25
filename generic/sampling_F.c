#include "../sampling_F.h"




#ifdef __cplusplus
namespace fastdsp { //namespace fastdsp
namespace lina {    //namespace lina
#endif




EXTERN void sampling_resample_poly1_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in){

    if(n_in == n_out){
        memcpy(ov, iv, n_in);
        return;
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



EXTERN void sampling_resample_poly2_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in){

    if(n_in == n_out){
        memcpy(ov, iv, n_in);
        return;
    }

    register count_t k;
    count_t i, last_k = (count_t)-1;
    float32 coeff = (float32)(--n_in) / (float32)(--n_out); //calc reduction coefficient and count convert to max index
    float32 fidx, y[3], a[3];

    ov[0] = iv[0];
    ov[n_out] = iv[n_in];

    // downsampling
    if(n_in > n_out){

        for(i=1; i<n_out; i++){
            fidx = i * coeff;
            k = roundf(fidx);
            k += (k == 0) - (k == n_in);    //check borders

            ///// Here must save  nearby input vector

            if(last_k != k){
                y[0] = iv[k-1];
                y[1] = iv[k];
                y[2] = iv[k+1];

                a[0] = y[1];
                a[1] = (y[2] - y[0]) * 0.5;
                a[2] = y[2] - a[1] - a[0];

                last_k = k;
            }

            fidx = fidx - (float32)k;
            ov[i] = a[0] + fidx * (a[1] + fidx * a[2]);
        }

    // upsampling
    }else{

        for(i=n_out-1; i>0; i--){
            fidx = i * coeff;
            k = roundf(fidx);
            k += (k == 0) - (k == n_in);    //check borders

            ///// Here must save  nearby input vector

            if(last_k != k){
                y[0] = iv[k-1];
                y[1] = iv[k];
                y[2] = iv[k+1];

                a[0] = y[1];
                a[1] = (y[2] - y[0]) * 0.5;
                a[2] = y[2] - a[1] - a[0];

                last_k = k;
            }

            fidx = fidx - (float32)k;
            ov[i] = a[0] + fidx * (a[1] + fidx * a[2]);
        }


    }

}



EXTERN void sampling_decimate_F(float32 *ov, float32 *iv, count_t n, count_t factor){
    register count_t i,j;
    for(i=0, j=0; i<n; i+=factor, j++)
        ov[j] = iv[i];
}





#ifdef __cplusplus
} //namespace fastdsp
}    //namespace lina
#endif






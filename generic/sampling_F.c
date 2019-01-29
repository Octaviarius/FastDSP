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



EXTERN void sampling_resample_poly3_F(float32 *ov, float32 *iv, count_t n_out, count_t n_in){

    if(n_in == n_out){
        if(ov == iv)
            return;
        memcpy(ov, iv, n_in);
    }

    register count_t k;
    count_t i, last_k = (count_t)-1;
    float32 coeff = (float32)(--n_in) / (float32)(--n_out); //calc reduction coefficient and count convert to max index
    float32 fidx, a[4], b[2];
    float32 tmp_iv;


    ov[0] = iv[0];
    ov[n_out] = iv[n_in];

    // downsampling
    if(n_in > n_out){

        tmp_iv = iv[0];
        for(i=1; i<n_out; i++){
            fidx = i * coeff;
            k = (count_t)fidx;

            if(last_k != k){

                if(k == 0){
                    b[0] = 1.5 * (iv[1] - iv[0]);
                    b[1] = 0.5 * (iv[2] - iv[0]);
                }else if(k >= n_in){
                    b[0] = 0.5 * (iv[k+1] - iv[k-1]);
                    b[1] = 1.5 * (iv[k+1] - iv[k]);
                }else{
                    if(k > i + 1){
                        b[0] = 0.5 * (iv[k+1] - iv[k-1]);
                        b[1] = 0.5 * (iv[k+2] - iv[k]);
                    }else{
                        b[0] = 0.5 * (iv[k+1] - tmp_iv);
                        b[1] = 0.5 * (iv[k+2] - iv[k]);
                        tmp_iv = iv[k];
                    }
                }

                a[0] = iv[k];
                a[1] = b[0];
                a[3] = b[0] + b[1] + 2.0 * (iv[k] - iv[k+1]);
                a[2] = 0.5 * (b[1] - b[0] - 3.0 * a[3]);

                last_k = k;
            }

            fidx = fidx - (float32)k;
            ov[i] = a[0] + fidx * (a[1] + fidx * (a[2] + fidx * a[3]));
        }

    // upsampling
    }else{

        tmp_iv = iv[0];
        for(i=n_out-1; i>=1; i--){
            fidx = i * coeff;
            k = (count_t)fidx;

            if(last_k != k){

                if(k == 0){
                    b[0] = 1.5 * (iv[1] - iv[0]);
                    b[1] = 0.5 * (iv[2] - iv[0]);
                }else if(k >= n_in){
                    b[0] = 0.5 * (iv[k+1] - iv[k-1]);
                    b[1] = 1.5 * (iv[k+1] - iv[k]);
                }else{
                    if(k + 1 < i){
                        b[0] = 0.5 * (iv[k+1] - iv[k-1]);
                        b[1] = 0.5 * (iv[k+2] - iv[k]);
                    }else{
                        b[0] = 0.5 * (iv[k+1] - iv[k-1]);
                        b[1] = 0.5 * (tmp_iv - iv[k]);
                        tmp_iv = iv[k+1];
                    }
                }

                a[0] = iv[k];
                a[1] = b[0];
                a[3] = b[0] + b[1] + 2.0 * (iv[k] - iv[k+1]);
                a[2] = 0.5 * (b[1] - b[0] - 3.0 * a[3]);

                last_k = k;
            }

            fidx = fidx - (float32)k;
            ov[i] = a[0] + fidx * (a[1] + fidx * (a[2] + fidx * a[3]));
        }


    }

}



EXTERN void sampling_decimate_F(float32 *ov, float32 *iv, count_t n, count_t factor){
    register count_t i;
    for(i=0; i<n; i+=factor){
        *(ov++) = *(iv);
        iv += factor;
    }
}





#ifdef __cplusplus
} //namespace fastdsp
}    //namespace lina
#endif






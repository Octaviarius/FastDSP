#include "../linav_CF.h"
#include <math.h>





#ifdef __cplusplus
namespace fastdsp {	//namespace fastdsp
namespace lina {	//namespace lina
#endif




EXTERN void circ_shift_CFV(cfloat *ov, cfloat *iv, count_t n, count_t shift){
    if(ov == iv){
        cfloat  *lptr = iv,
                *rptr = iv,
                *last = &iv[n - 1];

        cfloat lval, rval;

        lval = *lptr;
        for(count_t i=n; i>0; i--){
            rptr += shift;
            if(rptr > last)
                rptr -= n;

            rval = *rptr;
            *rptr = lval;
            lval = rval;

            lptr = rptr;
        }

    }else{
        memcpy(ov + shift, iv, sizeof(*ov)*(n - shift));
        memcpy(ov, iv + (n - shift), sizeof(*ov)*shift);
    }
}





#ifdef __cplusplus
}	//namespace lina
}	//namespace fastdsp
#endif











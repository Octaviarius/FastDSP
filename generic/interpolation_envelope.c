#include "../interpolation_envelope.h"






#ifdef __cplusplus
namespace fastdsp {
namespace interpolation {
#endif


EXTERN void envelope_top_FV(float32 *ov, float32 *iv, count_t n){
	count_t i, j, extrem_p[] = {0, 0};

	ov[0] = iv[0];
	for(i=1;i<n-1; i++){
		//maxes
		if( (iv[i-1] <= iv[i]) && (iv[i+1] <= iv[i]) ){
			extrem_p[0] = extrem_p[1];
			extrem_p[1] = i;
			//line interpolation
			if(extrem_p[0] != 0){
				float32 a = (iv[extrem_p[1]] - iv[extrem_p[0]]) / (float32)(extrem_p[1] - extrem_p[0]);
				float32 b = iv[extrem_p[0]] - a * (float32)extrem_p[0];

				for(j=extrem_p[0]+1; j<extrem_p[1]; j++)
					ov[j] = a * (float)j + b;
			}else
				ov[i] = iv[i];
		}else
			ov[i] = iv[i];
	}
	ov[i] = iv[i];
}


EXTERN void envelope_bottom_FV(float32 *ov, float32 *iv, count_t n){
	count_t i, j, extrem_p[] = {0, 0};

	ov[0] = iv[0];
	for(i=1;i<n-1; i++){
		//maxes
		if( (iv[i-1] >= iv[i]) && (iv[i+1] >= iv[i]) ){
			extrem_p[0] = extrem_p[1];
			extrem_p[1] = i;
			//line interpolation
			if(extrem_p[0] != 0){
				float32 a = (iv[extrem_p[1]] - iv[extrem_p[0]]) / (float32)(extrem_p[1] - extrem_p[0]);
				float32 b = iv[extrem_p[0]] - a * (float32)extrem_p[0];

				for(j=extrem_p[0]+1; j<extrem_p[1]; j++)
					ov[j] = a * (float)j + b;
			}else
				ov[i] = iv[i];
		}else
			ov[i] = iv[i];
	}
	ov[i] = iv[i];
}


EXTERN void envelope_center_FV(float32 *ov, float32 *iv, count_t n){

}







#ifdef __cplusplus
};	//namespace fastdsp
};	//namespace interpolation
#endif


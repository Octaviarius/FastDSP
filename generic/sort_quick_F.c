#include <fastDSP/sort_quick_F.h>
#include "../linav_F.h"





#ifdef __cplusplus
namespace fastdsp {
namespace sort {
#endif


static count_t partition(float32 *iv, count_t ls, count_t rs){
	register float32 pivot = mean_FV(iv + ls, rs - ls);
	while(ls <= rs){

		while(iv[ls] < pivot)
			ls++;
		while(iv[rs] > pivot)
			rs--;

		if(ls <= rs){
			register float32 tmp = iv[ls];
			iv[ls] = iv[rs];
			iv[rs] = tmp;
			ls++;
			rs--;
		}
	}
	return ls;
}


static void step_sort(float32 *iv, count_t ls, count_t rs){
	if(ls < rs){
		register count_t p = partition(iv, ls, rs);
		step_sort(iv, ls, p-1);
		step_sort(iv, p, rs);
	}
}




EXTERN void sort_quick_F(float32 *ov, float32 *iv, count_t n){
	if(ov != iv)
		memcpy(ov, iv, n * sizeof(*ov));
	step_sort(ov, 0, n-1);
}





#ifdef __cplusplus
};	//namespace sort
};	//namespace fastdsp
#endif


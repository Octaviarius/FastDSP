
#include "../base.h"





#ifdef __cplusplus
namespace fastdsp {
#endif


EXTERN void memswap(void *s1, void *s2, size_t size){
	register char *mem1 = (char*)s1;
	register char *mem2 = (char*)s2;

	while(size-->0){
		char tmp = *mem1;
		*(mem1++) = *(mem2);
		*(mem2++) = tmp;
	}
}




#ifdef __cplusplus
}; //namespace fastdsp
#endif




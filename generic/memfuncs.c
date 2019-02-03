
#include "../base.h"





#ifdef __cplusplus
namespace fastdsp {
#endif


EXTERN void memswap(void *s1, void *s2, size_t size){
    while(size-->0){
        char tmp = *(*(char**)&s1);
        *((*(char**)&s1)++) = *(*(char**)&s2);
        *((*(char**)&s2)++) = tmp;
	}
}




#ifdef __cplusplus
}; //namespace fastdsp
#endif




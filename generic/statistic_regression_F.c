#include "../statistic_regression_F.h"
#include "../ext_math.h"
#include "../linav_F.h"



#ifdef __cplusplus
namespace fastdsp {
namespace statistic {
#endif



EXTERN void regression_signal_init_F(regression_signal_f_t *regsig){
	regsig->c[0] = 0.0;
	regsig->c[1] = 0.0;
	regsig->y = 0.0;
	regsig->x = 0.0;
	regsig->sse = 0.0;
	regsig->sy = 0.0;
	regsig->sx = 0.0;
	regsig->sxx = 0.0;
	regsig->sxy = 0.0;
}


EXTERN void regression_signal_process_F(regression_signal_f_t *regsig){
	float32 tau = regsig->tau;

	regsig->sy += (regsig->y - regsig->sy) * tau;
	regsig->sx += (regsig->x - regsig->sx) * tau;
	regsig->sxx += (regsig->x*regsig->x - regsig->sxx) * tau;
	regsig->sxy += (regsig->x * regsig->y - regsig->sxy) * tau;

	regsig->c[1] = (regsig->sxy - regsig->sx * regsig->sy) / (regsig->sxx - sqr_F(regsig->sx));
	regsig->c[0] = regsig->sy - regsig->c[1] * regsig->sx;

	float32 tmp = regsig->y - (regsig->c[0] + regsig->x * regsig->c[1]);
	regsig->sse += (tmp*tmp - regsig->sse) * tau;
	regsig->sse = constrain_FS(regsig->sse, -FLT_MAX, FLT_MAX);
}







EXTERN void regression2_signal_init_F(regression2_signal_f_t *regsig){
/*	regsig->c[0] = 0.0;
	regsig->c[1] = 0.0;
	regsig->y = 0.0;
	regsig->x = 0.0;
	regsig->sse = 0.0;
	regsig->sy = 0.0;
	regsig->sx = 0.0;
	regsig->sxx = 0.0;
	regsig->sxy = 0.0;*/
}


EXTERN void regression2_signal_process_F(regression2_signal_f_t *regsig){
/*	float32 tau = regsig->tau;

	regsig->sy += (regsig->y - regsig->sy) * tau;
	regsig->sx += (regsig->x - regsig->sx) * tau;
	regsig->sxx += (sqr_F(regsig->x) - regsig->sxx) * tau;
	regsig->sxy += (regsig->x * regsig->y - regsig->sxy) * tau;

	regsig->c[1] = (regsig->sxy - regsig->sx * regsig->sy) / (regsig->sxx - sqr_F(regsig->sx));
	regsig->c[0] = regsig->sy - regsig->c[1] * regsig->sx;

	regsig->sse += sqr_F(regsig->y - (regsig->c[0] + regsig->x * regsig->c[1])) * tau;*/
}






#ifdef __cplusplus
};	//namespace statistic
};	//namespace fastdsp
#endif


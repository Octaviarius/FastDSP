#include "../statistic_statsignal_F.h"





#ifdef __cplusplus
namespace fastdsp {
namespace statistic {
#endif





	EXTERN void statsignal_init_F(statsignal_f_t *stat){
		stat->quants = 0;
		stat->min = 0;
		stat->max = 0;
		stat->mean = 0;
		stat->input = 0;
		stat->tau = 1;
	}

	//! Statistic signal, calc mean and dispersion
	EXTERN void statsignal_process_F(statsignal_f_t *stat){
		register float32 tau = stat->tau;
		register float32 input = stat->input;

		input = (input < -FLT_MAX) ? -FLT_MAX : (input > FLT_MAX) ? FLT_MAX : input;

		if(stat->quants == 0){
			stat->max = stat->min = input;
		}else{
			if(stat->min > input)		stat->min = input;
			else						stat->min += (input - stat->min) * tau;
			if(stat->max < input)		stat->max = input;
			else						stat->max += (input - stat->max) * tau;
		}
		float32 d = input - stat->mean, mx;

		mx = d;
		stat->mean += mx * tau;
		mx *= d;
		stat->disp += (mx - stat->disp) * tau;
		mx *= d;
		stat->symm += (mx - stat->symm) * tau;
		mx *= d;
		stat->excess += (mx - stat->excess) * tau;

		stat->quants++;
	}



#ifdef __cplusplus
};	//namespace statistic
};	//namespace fastdsp
#endif


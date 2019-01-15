#pragma once


#include "base.h"
#include "base_cpp.h"




#ifdef __cplusplus
namespace fastdsp {
namespace spectrum {
#endif




#ifdef __cplusplus
	typedef peak_t<float32> peak_f_t;

#else

	typedef struct {
		float32 value;
		icount_t idx;
	} peak_f_t;


#endif


	//! Find all peaks. Forming index buffer for light-weighted working
	//! @return Count of found peaks in index buffer
	EXTERN count_t peaks_find_all_FV(
			count_t *idxbuffer, 	//!< Index buffer
			float32 *spectrum, 		//!< Input spectrum
			count_t n				//!< Vector size
	);

	//! Find nearest peak from start index
	//! @return Found peak index
	EXTERN count_t peaks_find_nearest_FV(
			float32 *spectrum,		//!< Input spectrum
			float32 *app_apectrum,	//!< Apparatus function. Maybe pointer NULL
			count_t start,			//!< Start index
			count_t n				//!< Vector size
	);

	//! Find max peak
	//! @return Found peak index
	EXTERN peak_f_t peaks_find_max_IV(
			count_t *idxbuffer,
			count_t idxbuffer_size,
			float32 *spectrum,
			float32 *corr_profile,
			float32 threshold,
			count_t n
	);

	//! Find max peak
	//! @return Found peak index
	EXTERN peak_f_t peaks_find_max_FV(
			float32 *spectrum, 		//!< Input spectrum
			float32 *app_spectrum,	//!< Apparatus function. Maybe pointer NULL
			float32 treshold,		//!< Treshold
			count_t n				//!< Vector size
	);


	//! Get parabolic interpolated peak with three equidistance points
	//! @return Parabolic interpolated peak index
	EXTERN float32 peaks_get_index_FS(float32 left_cs, float32 center_cs, float32 right_cs);


	//! Get parabolic interpolated peak about coarse index
	//! @return Parabolic interpolated peak index
	EXTERN float32 peaks_get_index_FV(
			float32 *spectrum, 		//!< Input spectrum
			count_t n, 				//!< Spectrum size
			count_t coarse_index	//!< Coarse nearest index
	);

	//! Retouch zone. Use for disappear unity peak splashes
	//! @return Parabolic interpolated peak index
	//! @warning center >= 2*span and center + 2*span < n
	EXTERN void peaks_retouch_zone_FV(
			float32 *spectrum, 		//!< Input spectrum
			count_t n, 				//!< Spectrum size
			count_t center,			//!< Center of zone
			count_t span			//!< Left and right bins count. Zone width = 2*span + 1
	);

	//! Retouch zone. Use for disappear unity peak splashes
	//! @return Parabolic interpolated peak index
	//! @warning center >= 2*span and center + 2*span < n
	EXTERN void peaks_retouch_zone_CFV(
			cfloat *spectrum, 		//!< Input spectrum
			count_t n, 				//!< Spectrum size
			count_t center,			//!< Center of zone
			count_t span			//!< Left and right bins count. Zone width = 2*span + 1
	);



#ifdef __cplusplus
};	//namespace spectrum
};	//namespace fastdsp
#endif


#pragma once


#include "base.h"


#ifdef __cplusplus
namespace fastdsp{
namespace spectrum{
#endif


//! Complex FFT structure
typedef struct {
	cfloat	*InPtr;				//!< Pointer to the input buffer
	cfloat	*OutPtr;			//!< Pointer to the output buffer
	float	*CoefPtr;			//!< Pointer to the twiddle factors
	cfloat	*CurrentInPtr;      //!< Points to input buffer at each FFT stage
	cfloat	*CurrentOutPtr;     //!< Points to output buffer at each FFT stage
	count_t	Stages;         	//!< Number of FFT stages
	count_t	FFTSize;       		//!< Size of the FFT (number of complex data points)
}fft_cf_t;



//! \brief Complex Fast Fourier Transform (Unaligned).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt (\f$ N = 2^{n}, n = 5 : 10\f$)
//! complex input. This function will reorder the input in bit-reversed format before proceeding with
//! the FFT. The routine uses two buffers in ping-pong fashion i.e. after each FFT stage the output and
//! input buffers become the input and output buffers respectively for the next stage. The CFFT_F32 object
//! uses two pointers, CurrentInPtr and CurrentOutPtr to keep track of the switching. The user can determine
//! the address of the final output by looking at the CurrentOutPtr.
//! \param cfft Pointer to the CFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N (32-bit), for computation; the input
//! buffer need not be aligned to any boundary.
//! -# If alignment is possible the user can use the faster routine, CFFT_f32
//! \warning This function is not re-entrant as it uses global variables to store certain parameters
EXTERN void fft_transform_CF(fft_cf_t * cfft);

//! Inverse transform
EXTERN void fft_itransform_CF(fft_cf_t *cfft);

//! \brief Generate twiddle factors for the Complex FFT
//!
//! \param cfft Pointer to the CFFT_F32 object
//! \attention This function is written in C and compiled without optimization turned on.
EXTERN void fft_init_CF(fft_cf_t * cfft);




#ifdef __cplusplus
};
};
#endif





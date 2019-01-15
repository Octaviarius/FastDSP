#pragma once

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
#	define EXTERN extern "C"
#else
#	define EXTERN extern
#endif






#ifdef __cplusplus
namespace fastdsp {	//namespace fastdsp
#endif


typedef float float32;

#if DBL_MANT_DIG == 53
	typedef double float64;
#elif LDBL_MANT_DIG == 53
	typedef long double float64;
#endif


//! Type of count
typedef unsigned int count_t;
//! Type of count
typedef int icount_t;




#ifdef __cplusplus

	template<class T>
	class complex_t{
	public:
	  //! Real part
	  T re;
	  //! Imaginary part
	  T im;

	  complex_t(T re = 0.0, T im = 0.0){
		  this->re = re;
		  this->im = im;
	  };

	  complex_t(T a, T b, bool is_euler){
		  if(is_euler){
			  this->re = a * cos(b);
			  this->im = a * sin(b);
		  }else{
			  this->re = a;
			  this->im = b;
		  }
	  };

	};



	//! Complex short
	typedef complex_t<short> cshort;

	//! Complex long
	typedef complex_t<long> clong;

	//! Complex float
	typedef complex_t<float32> cfloat;

	//! Complex double
	typedef complex_t<float64> cdouble;


	//! Quaternion float
	typedef struct {
		float32 re;
		float32 im[3];
	} qfloat;


	//! Quaternion double
	typedef struct {
		float64 re;
		float64 im[3];
	} qdouble;


#else

	//! Complex float
	typedef struct {
		short re;
		short im;
	} cshort;


	//! Complex float
	typedef struct {
		long re;
		long im;
	} clong;

	//! Complex float
	typedef struct {
		float32 re;
		float32 im;
	} cfloat;


	//! Complex double
	typedef struct {
		float64 re;
		float64 im;
	} cdouble;


	//! Quaternion float
	typedef struct {
		float32 re;
		float32 im[3];
	} qfloat;


	//! Quaternion double
	typedef struct {
		float64 re;
		float64 im[3];
	} qdouble;


#endif


	typedef float32 (*pfunc_f_t)(float32);
	typedef float32 (*pfunc2_f_t)(float32, float32);

	typedef cfloat (*pfunc_cf_t)(cfloat);
	typedef cfloat (*pfunc2_cf_t)(cfloat, cfloat);





#ifdef __cplusplus
};	//namespace fastdsp
#endif



#pragma once

#include "base.h"



#ifdef __cplusplus


namespace fastdsp{

namespace lina{

	template<class T, count_t n>
	struct vec_t {
		T v[n];
	};


	template<class T>
	struct vec2_t{
		union{
			T v[2];
			struct{
				T x;
				T y;
			};
		};
	} ;

	template<class T>
	struct vec3_t{
		union{
			T v[3];
			struct{
				T x;
				T y;
				T z;
			};
		};
	};

	template<class T>
	struct vec4_t {
		union{
			T v[4];
			struct{
				T x;
				T y;
				T z;
				T t;
			};
		};
	};

	template<class T>
	struct vec5_t{
		union{
			T v[5];
			struct{
				T x;
				T y;
				T z;
				T t;
				T u;
			};
		};
	};





	template<class T, count_t rows, count_t cols>
	struct mat_t{
		T m[rows][cols];
	};


	template<class T>
	struct mat2_t{
		union{
			T m[2][2];
			struct{
				T m00; T m01;
				T m10; T m11;
			};
		};
	} ;

	template<class T>
	struct mat3_t{
		union{
			T m[3][3];
			struct{
				T m00; T m01; T m02;
				T m10; T m11; T m12;
				T m20; T m21; T m22;
			};
		};
	};

	template<class T>
	struct mat4_t{
		union{
			T m[4][4];
			struct{
				T m00; T m01; T m02; T m03;
				T m10; T m11; T m12; T m13;
				T m20; T m21; T m22; T m23;
				T m30; T m31; T m32; T m33;
			};
		};
	};

	template<class T>
	struct mat5_t{
		union{
			T m[5][5];
			struct{
				T m00; T m01; T m02; T m03; T m04;
				T m10; T m11; T m12; T m13; T m14;
				T m20; T m21; T m22; T m23; T m24;
				T m30; T m31; T m32; T m33; T m34;
				T m40; T m41; T m42; T m43; T m44;
			};
		};
	};




}//namespace lina










namespace spectrum {

	template<class T>
	class peak_t {
	public:
		T value;
		icount_t idx;

		peak_t(T value = 0.0, icount_t idx = 0){
			this->value = value;
			this->idx = idx;
		}
	};

};








};	//namespace fastdsp

#endif



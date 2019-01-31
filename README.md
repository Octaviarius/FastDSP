# FastDSP
Library for optimized fast computation linear algebra operations, filtering, statistical and other for many arches

***

# Naming
For more readable and systematic API using special naming by module, data type and data dimension. Library oriented at FPU and all operations uses floating point single and double precision, real and complex. Also using scalars, vectors and matrixes. Double precision not realized for now, also fourth (long double) precision maybe realized in future ;-)

## *Functions*
Functions have a postfix, which show what type/types function uses.
Definition short names for types:<br>
- **F** - real number single precision sclar
- **D** - real number double precision sclar
- **CF** - complex number signle precision sclar
- **CD** - complex number double precision sclar

Definition postfixes for dimensions:<br>
- **S** - scalar
- **V** - vector
- **M** - matrix
For common naming function dimension postfix maybe missing.

For show conjugate value use small letter **c** for complex number. If we need show what dimension using then add dimension letter at ending . For example: **FS** - single scalar, **DV** - double vector, **CFS** - complex single scalar, **cDV** - conjugated double vector, **FM** - single matrix, **DS** - double scalar, **CFV** - complex single vector, **CDM** - complex double matrix.

Common form for function naming:
	**function_name_\[C,c\]\[F,D\]\[S,V,M\](args...)**
 
## *Arguments*
In general arguments use next notation:
- **o** - output
- **i** - input
- **l** - left operand
- **r** - right operand
- **c** - constant value

+ **n** - usually size of dimensions (maybe a vector if you input matrix n-by-m)

Dimension postfixes:
- **s** - scalar
- **v** - vector
- **m** - matrix

But you may use any variables, long-names or standart variables, such as **x**, **y**, **z**, **t** and other.


***

# Modules
## Lina (linear algebra) 
Basics linear algebra API. 

Typical function names:
- **add** - addition
- **sub** - substraction
- **mul** - element-wise multiplication
- **smul** - scalar multiplication
- **mmul** - matrix-by-matrix or matrix-by-vector multiplication
- **norm** - norm of vector or calc determinant of matrix
- **abs** - absolute value
- **min** - min value in vector
- **max** - max value in vector
- **inv** - inverse data. Vectors are inverse element-wise, matrixes are find inverse matrix
- **dist_\{method\}** - distance beetween vectors
- **norm_\{method\}** - norm of vector
- **normalize** - normalization 
- **det** - determinant of matrix
- **conjugate** - conjugate object for input object
- **convert** - converting beetween two types, for example real vector to complex real vector, or double vector to float vector
- **generate** - generate any structure, such as unity matrix or null-vector

More functions see in documentation.

## Filter 
Module consist some submodules:
- **fir** - finit impulse response filter *(realized for real and complex numbers)*
- **iir** - infinit impulse response filter *(realized for real and complex numbers)*
- **median** - median filtering on fly, may selected any quantile
- **kalman** - kalman filtering (comming soon...) 
- **tdlms** - LMS filter in time-domain (comming soon...) 
- **fdlms** - LMS filter in frequency domain (comming soon...) 
	
## Statistic 
Consist statistical mehtods in submodules:
- **regonfly** - regression on fly. Realized for linear and square polynoms
- **statsignal** - calculating min, max and central momentums: mean, dispersion, symmetry, excess
	
## Spectrum 
Submodules:
- **fft** - fast Fourier transform *(realized only for complex numbers)*
- **window** - generate many types of windows: rectangle, triangle, hamming, hann, blackman and other
- **peaks** - many operations on peaks, such as find local peaks, find nearest peak, retouch zones. All operations use cyclic spectrum

	
## Extmath 
Extended math operations use as utilities for other functions.

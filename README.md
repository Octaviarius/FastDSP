# FastDSP
Library for optimized fast computation linear algebra operations, filtering, statistical and other for many arches

It's started!



## Functions naming 
 
	function_name_{C,Q}[F,D][S,V,M,T](args...)
	C,c,Q,q - complex, complex-conjugated, quaternion, quaternion-conjugated
	F,D - float, double
	S,V,M,T - scalar, vector, matrix, tensor
 
## Arguments naming 
  
	{o,i,l,r,c}[s,v,m,t]
	o,l,r,c - output, left-side, right-side, constant
	s,v,m,t - scalar, vector, matrix, tensor
	c - constant
	n - size of dimensions (maybe a vector)

## Lina (linear algebra) 

	add - addition
	sub - substraction
	mul - element-wise multiplication
	smul - scalar multiplication
	mmul - matrix-by-matrix or matrix-by-vector multiplication
	norm - norm of vector
	dist - distance beetween vectors
	normalize - vector normalization 
	det - determinant of matrix
	conjugate - conjugate object for input object
	convert - converting beetween two types, for example real vector to complex real vector, or double vector to float vector
	generate - generate any structure, such as unity matrix or null-vector
 	
	
## Filter 

	FIR - finit impulse response filter
	IIR - infinit impulse response filter
	median - median filtering
	kalman - kalman filtering (comming soon...) 
	
## Extmath 
	
	Extended math operations
	
	
## Statistic 
	
	regression
	statsignal
	
	
## Spectrum 
	
	fft
	window
	peaks
	
	

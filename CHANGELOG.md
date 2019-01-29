30.10.2017:
	1. Start realization idea about fast DSP lib.
	2. Declaration and implementation(generic, for all platforms) common vector functions
28.01.2019:
	1. interpolation: Delete envelope functions
	2. filter: Change IIR interface, add buffer size variable and check condition if size < max(size_a, size_b)
	3. lina: Add circle shift for F and CF vectors
	4. lina: Reshape matrix symmetrify function
	5. lina: Delete fatality code of matrix determinant. New code matrix determinant placed
	6. memfuncs: optimized memswap C28_FPU
	7. sampling: Realized resampling by 3rd order polynom. But upsampling algorithm need rework
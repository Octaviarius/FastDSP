# Changelog
Here will be illustrated work progress


## [0.5.0] - 2019-02-01
### Added
- lina: triangulation matrix operation by [Gauss matrix eliminating](https://en.wikipedia.org/wiki/Gaussian_elimination)
### Changed
- lina: rename get and set col and row of matrix
- lina: reuse triangulation in determinant of matrix
### Fixed 
- lina: get and set row and column of matrix
- lina: matrix multiplication now use different agreed matrix: NxM \* MxP = NxP
- lina: multiplication matrix by vector and vector by matrix
- lina: tensor multiplication row-vector by col-vector


## [0.4.0] - 2019-02-01
### Added 
- sampling: sample_oversample_F for **generic**


## [0.3.1] - 2019-02-01
### Fixed 
- controller: PID critical pipeline delay for **C28_FPU** 
### Removed
- extmath: function inc_F


## [0.3.0] - 2019-01-31
### Added
- filter: IIR complex float realization for **C28_FPU**
- controller: PID interface and realization for **generic** and **C28_FPU**
### Changed
- filter: For FIR and IIR filters C files with added for **C28_FPU**
### Fixed
- sampling: sampling_resample_poly3_F now input and output vector pointers must be different
- lina: constrain_FS for **C28_FPU** error with load vmax value

## [0.2.0] - 2019-01-28
### Added
- lina: Add circle shift for F and CF vectors
- sampling: API and realization of resampling linear, resampling cubic, decimation. But upsampling algorithm in resampling cubic need rework
### Changed
- lina: Reshape matrix symmetrify function
- filter: IIR interface, add buffer size variable and check condition if size < max(size_a, size_b)
- memfuncs: optimized memswap **C28_FPU**
### Removed
- interpolation: Envelope functions
### Fixed
- lina: Fatality code of matrix determinant was replaced new variant [Gauss matrix eliminating](https://en.wikipedia.org/wiki/Gaussian_elimination)

	
## [0.1.0] - 2017-10-30
### Added
- Start realization idea about fast DSP lib.
- Common types, float32, cfloat, etc.
- lina: vector and matrixes API and realization for **generic** and **C28_FPU** 
- filter: FIR, IIR, median API and realization for **generic** and **C28_FPU**
- statistic: statsignal API and realization for **generic** 
- sort: bubble, quick API and realisation for **generic** 
- spectrum: CFFT API and realisation for **C28_FPU** 
- Any extended functions
- Memfuncs for **generic** and **C28_FPU** 
- Stdlib funcеions optimized for **C28_FPU** 
	
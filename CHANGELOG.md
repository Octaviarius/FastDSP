# Changelog
Here will be illustrated work progress


## [0.2.0] - 28-01-2019	
### Added
- lina: Add circle shift for F and CF vectors
- sampling: API and realization of resampling linear, resampling cubic, decimation. But upsampling algorithm in resampling cubic need rework
### Changed
- lina: Reshape matrix symmetrify function
- filter: IIR interface, add buffer size variable and check condition if size < max(size_a, size_b)
- memfuncs: optimized memswap C28_FPU
### Removed
- interpolation: Envelope functions
### Fixed
- lina: Fatality code of matrix determinant was replaced new variant [Gauss matrix eliminating](https://en.wikipedia.org/wiki/Gaussian_elimination)

	
## [0.1.0] - 30-10-2017
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
	
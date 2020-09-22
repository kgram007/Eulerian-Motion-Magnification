# Eulerian Motion Magnification

<p align="left">
  <a href="https://github.com/kgram007/Eulerian-Motion-Magnification/blob/master/LICENSE"><img src="https://img.shields.io/badge/License-MIT-brightgreen.svg" alt="License"></a>
</p>

## About:
This is a C++ implementation of the paper "Eulerian Video Magnification for Revealing Subtle Changes in the World" ACM Transaction on Graphics, Volume 31, Number 4 (Proceedings SIGGRAPH 2012).

This implementation is based on the works done at MIT CSAIL.
For futher details visit http://people.csail.mit.edu/mrub/vidmag

The code includes the following spatial and temporal filters:

|     Spatial       |          Temporal         |
|-------------------|---------------------------|
| Laplacian pyramid | Second-order IIR bandpass |

Library Used: OpenCV, Boost
	

## Compiling and Running the code:
Required packages: g++, CMake, OpenCV, Boost
### Compiling
	$ cd <PROJ_DIR>
	$ cmake .
	$ make
### Running the program with test params
	$ cd <PROJ_DIR>
	$ ./bin/Eulerian_Motion_Magnification test/test_baby.param
	
## Adaptations:
This project has been adapted by:

1. [https://github.com/katiewasnothere/bwi_pulse_detector](https://github.com/katiewasnothere/bwi_pulse_detector)

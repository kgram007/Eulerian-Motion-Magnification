This is The C++ implementation of the following paper using the OpenCV library.

"Eulerian Video Magnification for Revealing Subtle Changes in the World"
ACM Transaction on Graphics, Volume 31, Number 4 (Proceedings SIGGRAPH
2012)

The paper and example videos can be found on the project web page
http://people.csail.mit.edu/mrub/vidmag/

Programming Language: C++
Library Used: OpenCV
Environment Used: Visual Studio 2010

The code includes the following spatial and temporal filters:

	Spatial					Temporal
=========================================================================
	Laplacian pyramid		Second-order IIR bandpass
	
	
This implementation is based on the works done at MIT CSAIL
For futher details visit http://people.csail.mit.edu/mrub/vidmag/
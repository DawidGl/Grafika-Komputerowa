// Vector Math Functions
// OpenGL SuperBible gltools library
// Richard S. Wright Jr.
// One note of interest. These REALLY should be inlined. I'm sorry I was too stupid at the time
// to figure out how to get inlining to work on all the platforms and different compilers I use.
// this seemed simpler than a ton of #ifdef's all over the place. Watch the web site as I may
// make frequent improvments t
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include "stdafx.h"
#include "gltools_extracted.h"
#include <math.h>


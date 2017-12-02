#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <GL/glaux.h>
#endif

#include "mathlib.h"
#include "studio.h"
#include "mdlviewer.h"

#pragma comment (lib, "glaux.lib")    /* link with Win32 GLAUX lib usada para ler bitmaps */

// funçÁao para ler jpegs do ficheiro readjpeg.c
extern "C" int read_JPEG_file(const char *, char **, int *, int *, int *);

#include "const.h"
#include "structs.h"
#include "tank.h"

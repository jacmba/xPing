#ifndef __OPENGL_H__
#define __OPENGL_H__

#if IBM
#include <windows.h>
#endif

#if LIN
#include <GL/gl.h>
#elif __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#endif


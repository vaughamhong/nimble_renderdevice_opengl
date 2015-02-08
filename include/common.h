//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_opengl_common_h__
#define __nimble_renderdevice_opengl_common_h__

//////////////////////////////////////////////////////////////////////////

#if defined(__APPLE__)
    #include "TargetConditionals.h"
    #include <OpenGL/gl.h>
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
#elif defined(NIMBLE_TARGET_WIN32)
    #include <windows.h>

    #define GLEW_STATIC
    #include <gl\glew.h>

    #include <gl\gl.h>
    #include <gl\glu.h>
#else
    #pragma message("Warning - trying to include OpenGL drivers for unsupported platform")
#endif

#if defined(NIMBLE_DEBUG)
    #define GLDEBUG(x) \
        x; \
        { \
            GLenum e; \
            while((e = glGetError()) != GL_NO_ERROR){ \
                fprintf(stderr, "Error at line number %d, in file %s. glGetError() returned %i for call %s\n",__LINE__, __FILE__, e, #x); \
            } \
        }
#else
    #define GLDEBUG(x) x;
#endif

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
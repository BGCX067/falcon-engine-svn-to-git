#ifndef FALCONENGINE_STDAFX_H
#define FALCONENGINE_STDAFX_H

#include <windows.h>
#define WIN32_LEAN_AND_MEAN //Exclude rarely-used stuff from Windows

#define LUABIND_DYNAMIC_LINK

#include "GL/glew.h"
#include "GL/wglew.h"

#include <gl/gl.h>
#include <gl/glu.h>



// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <crtdbg.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <utility>

#include "LogManager.h"

#endif
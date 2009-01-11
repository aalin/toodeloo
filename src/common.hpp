#include <iostream>
#include <stack>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <SDL/SDL.h>

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#endif

#include "engine.hpp"
#include "abstract_state.hpp"
#include "play_state.hpp"

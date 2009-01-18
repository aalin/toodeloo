#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/assign/list_of.hpp>

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

#include <chipmunk/chipmunk.h>
#include "chipmunk.hpp"

#include "bridge.hpp"
#include "map.hpp"

#include "engine.hpp"
#include "abstract_state.hpp"
#include "player.hpp"
#include "play_state.hpp"

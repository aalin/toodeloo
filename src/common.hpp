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
#include <boost/operators.hpp>

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
#include "wrappers/chipmunk.hpp"

#include "wrappers/vbo.hpp"

#include "math/math.hpp"
#include "math/angle.hpp"

#include "graphics/image.hpp"

#include "math/vector2.hpp"
#include "math/vector3.hpp"
#include "graphics/vertex.hpp"
#include "graphics/geometry.hpp"

#include "heightmap.hpp"

#include "bridge.hpp"
#include "map.hpp"

#include "camera.hpp"

#include "engine.hpp"
#include "states/state.hpp"
#include "player.hpp"
#include "states/gameplay.hpp"

cmake_minimum_required(VERSION 2.6)
 
project(game)
 
find_package(SDL)
find_package(SDL_image)
find_package(OpenGL)
find_package(Boost)

FIND_PATH(BOX2D_INCLUDE_DIR Box2D.h
	box2d/*/Box2D/Include
)

FIND_LIBRARY(BOX2D_LIBRARY
	NAMES BOX2D box2d
	box2d/*/Box2D/Source/Gen/float
)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${BOX2D_INCLUDE_DIR})
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
 
set(SHARED_SOURCES 
	# engine
	engine
	camera

	# wrappers
	wrappers/vbo

	# in game stuff
	player
	heightmap
	map

	# math
	math/vector2
	math/vector3
	math/angle

	# graphics
	graphics/image
	graphics/geometry

	# States
	states/state
	states/gameplay
	states/editor
)

set(BOOST_LIBRARIES -lboost_program_options)

set(MAIN_SOURCES main ${SHARED_SOURCES})
if(APPLE)
        set(MAIN_SOURCES ${MAIN_SOURCES} sdl/SDLMain.m)
endif(APPLE)
 
add_executable(game ${MAIN_SOURCES})
target_link_libraries(game ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${SDLIMAGE_LIBRARY} 
    ${BOX2D_LIBRARY} ${BOOST_LIBRARIES})

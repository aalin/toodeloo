cmake_minimum_required(VERSION 2.6)
 
project(game)
 
find_package(SDL)
find_package(SDL_image)
find_package(OpenGL)
find_package(Boost)
 
FIND_PATH( CHIPMUNK_INCLUDE_DIR chipmunk/chipmunk.h
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where chipmunk/chipmunk.h resides")
FIND_LIBRARY( CHIPMUNK_LIBRARY
        NAMES CHIPMUNK chipmunk
        PATHS
        /usr/lib64
        /usr/lib
        /usr/local/lib64
        /usr/local/lib
        /sw/lib
        /opt/local/lib
        DOC "The chipbajs library")
 
if(NOT SDL_FOUND)
        message(FATAL_ERROR "SDL not found!" )
endif(NOT SDL_FOUND)
 
if(NOT SDLIMAGE_FOUND)
        message(FATAL_ERROR "SDL Image not found!" )
endif(NOT SDLIMAGE_FOUND)
 
if(NOT OPENGL_FOUND)
        message(FATAL_ERROR "OpenGL not found!" )
endif(NOT OPENGL_FOUND)
 
include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR}
${SDLIMAGE_INCLUDE_DIR}
${CHIPMUNK_INCLUDE_DIR}
)
 
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
 
set(SHARED_SOURCES 
        abstract_state
        play_state
        engine
        chipmunk
        player
        map
        bridge
)
 
set(MAIN_SOURCES main ${SHARED_SOURCES})
if(APPLE)
        set(MAIN_SOURCES ${MAIN_SOURCES} sdl/SDLMain.m)
endif(APPLE)
 
add_executable(game ${MAIN_SOURCES})
target_link_libraries(game ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${SDLIMAGE_LIBRARY} 
    ${CHIPMUNK_LIBRARY})

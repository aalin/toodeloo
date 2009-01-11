project(worldzor)

find_package(SDL)
find_package(SDL_image)
find_package(OpenGL)
find_package(Boost)

if(NOT SDL_FOUND)
	message(FATAL_ERROR "SDL not found!" )
endif(NOT SDL_FOUND)

if(NOT SDLIMAGE_FOUND)
	message(FATAL_ERROR "SDL Image not found!" )
endif(NOT SDLIMAGE_FOUND)

if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!" )
endif(NOT OPENGL_FOUND)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR})

set(SHARED_SOURCES 
	main
	abstract_state
	play_state
	engine
)

set(MAIN_SOURCES main ${SHARED_SOURCES})
if(APPLE)
	set(MAIN_SOURCES ${MAIN_SOURCES} sdl/SDLMain.m)
endif(APPLE)

add_executable(worldzor ${MAIN_SOURCES})
#add_executable(testzor test ${SHARED_SOURCES})
target_link_libraries(worldzor ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${SDLIMAGE_LIBRARY})
#target_link_libraries(testzor ${SDL_LIBRARY} ${OPENGL_LIBRARIES})
#add_test(Test testzor)

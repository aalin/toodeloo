#include "common.hpp"

Engine::Engine(int width, int height, bool fullscreen)
	: _width(width), _height(height)
{
	_running = true;

	const SDL_VideoInfo* video_info = SDL_GetVideoInfo();

	Uint32 flags = SDL_OPENGL;
	flags |= SDL_GL_DOUBLEBUFFER;
	flags |= SDL_HWPALETTE;

	if(video_info->hw_available)
		flags |= SDL_HWSURFACE;
	else
		flags |= SDL_SWSURFACE;

	if (video_info->blit_hw)
		flags |= SDL_HWACCEL;

	if(fullscreen)
		flags = flags|SDL_FULLSCREEN;

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	_surface = SDL_SetVideoMode(width, height, 32, flags);
	if(_surface == 0)
		throw std::runtime_error("could init surface");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_WM_GrabInput(SDL_GRAB_ON);
	//SDL_GrabMode(SDL_GRAB_ON);
	//SDL_ShowCursor(0);

	initGL();
}

Engine::~Engine()
{
	std::cout << "~Engine();" << std::endl;
	while(!_states.empty())
		_states.pop();
}

void
Engine::changeState(boost::shared_ptr<AbstractState> state)
{
	if(!_states.empty())
		_states.pop();

	_states.push(state);
	_states.top()->init();
}

void
Engine::initGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glPointSize(3.0);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth(2.5f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-320.0, 320.0, -240.0, 240.0, -1.0, 1.0);
	glTranslatef(0.5, 0.5, 0.0);

	glEnable(GL_TEXTURE_2D);
}

void
Engine::pushState(boost::shared_ptr<AbstractState> state)
{
	if(!_states.empty())
		_states.top()->pause();

	_states.push(state);
	_states.top()->init();
}

void
Engine::popState()
{
	if(!_states.empty())
		_states.pop();

	if(!_states.empty())
		_states.top()->resume();
}

bool
Engine::isRunning() const
{
	return _running;
}

void
Engine::handleInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			_running = false;
		else
		{
			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						_running = false;
						break;
					default:
						break;
				}
			}
		}
		_states.top()->handleInput(event);
	}
}

void
Engine::update()
{
	while(GLenum error = glGetError())
	{
		if(error == GL_NO_ERROR)
			break;
		//std::cerr << glGetError() << std::endl;
	}

	if(_states.empty())
		throw std::runtime_error("No states.");
	_states.top()->update();
}

void
Engine::draw()
{
	if(_states.empty())
		throw std::runtime_error("No states.");
	_states.top()->draw();
	SDL_GL_SwapBuffers();
}

int
Engine::getWidth() const
{
	return _width;
}

int
Engine::getHeight() const
{
	return _height;
}


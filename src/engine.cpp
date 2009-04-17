#include "common.hpp"

namespace Toodeloo
{
	Engine::Engine(int width, int height, bool fullscreen)
		: _width(width), _height(height), _last_update(0)
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
			throw std::runtime_error("couldn't init surface");

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//SDL_WM_GrabInput(SDL_GRAB_ON);
		//SDL_GrabMode(SDL_GRAB_ON);
		//SDL_ShowCursor(0);

		initGL();
	}

	void
	Engine::quit()
	{
		_running = false;
	}

	Engine::~Engine()
	{
		std::cout << "~Engine();" << std::endl;
		while(!_states.empty())
			_states.pop();
	}

	void
	Engine::changeState(boost::shared_ptr<Toodeloo::States::State> state)
	{
		if(!_states.empty())
			_states.pop();

		_states.push(state);
		_states.top()->init();
	}

	void
	Engine::initGL()
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClearDepth(1);

		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		/*
		glPointSize(3.0);

		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth(2.5f);

		glEnable(GL_FOG);
		GLfloat fog_color[] = {0.3359375, 0.46875, 0.7578125, 0.2};
		glFogfv(GL_FOG_COLOR, fog_color);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_DENSITY, 0.5);
		glHint(GL_FOG_HINT, GL_NICEST);
		glFogf(GL_FOG_START, 150.0);
		glFogf(GL_FOG_END, 1000.0);

		glEnable(GL_NORMALIZE);

		glEnable(GL_CULL_FACE);
		*/
	}

	void
	Engine::pushState(boost::shared_ptr<Toodeloo::States::State> state)
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
		if(_states.empty())
			throw std::runtime_error("No states.");

		while(_last_update == 0)
			_last_update = SDL_GetTicks();

		unsigned int new_time = SDL_GetTicks();

		_states.top()->update(new_time - _last_update);

		_last_update = new_time;
	}

	void
	Engine::draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(_states.empty())
			throw std::runtime_error("No states.");
		_states.top()->draw();
		SDL_GL_SwapBuffers();
	}
}

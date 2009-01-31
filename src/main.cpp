#include "common.hpp"
#include "engine.hpp"
#include "states/state.hpp"
#include "states/gameplay.hpp"

#ifdef __APPLE__
int SDL_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Video initialization failed: " << SDL_GetError() << std::endl;
		return 1;
	}

	Toodeloo::Engine engine(1024, 768, false);

	try {
		boost::shared_ptr<Toodeloo::States::State> play_state(new Toodeloo::States::Gameplay(engine));
		//boost::shared_ptr<TestState> play_state(new TestState(engine));
		engine.pushState(play_state);
	}
	catch(const char* msg)
	{
		std::cout << msg << "\n";
		return 1;
	}

	int frames = 0;
	int start_time = SDL_GetTicks();
	while(engine.isRunning())
	{
		engine.handleInput();
		engine.update();
		engine.draw();

		frames++;
		int end_time = SDL_GetTicks();
		if(end_time - start_time >= 5000)
		{
			float seconds = (end_time - start_time) / 1000.0;
			float fps = frames / seconds;
			std::cout << frames << " frames in " << seconds << " seconds: " << fps << " fps" << std::endl;
			frames = 0;
			start_time = end_time;
		}
	}

	SDL_Quit();

	return 0;
}


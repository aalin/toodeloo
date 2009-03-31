#include "common.hpp"
#include "engine.hpp"
#include "states/state.hpp"
#include "states/gameplay.hpp"

#include <boost/program_options.hpp>

namespace po = boost::program_options;

#ifdef __APPLE__
int SDL_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	po::options_description desc("Options");
	desc.add_options()
		("help", "show help")
		("editor", "start editor")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Video initialization failed: " << SDL_GetError() << std::endl;
		return 1;
	}

	Toodeloo::Engine engine(1024, 768, false);

	try {
		if(vm.count("editor"))
		{
			std::cout << "Starting editor" << std::endl;
			engine.pushState(boost::shared_ptr<Toodeloo::States::State>(new Toodeloo::States::Editor(engine)));
		}
		else
		{
			std::cout << "Starting gameplay" << std::endl;
			engine.pushState(boost::shared_ptr<Toodeloo::States::State>(new Toodeloo::States::Gameplay(engine)));
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
	}
	catch(const char* msg)
	{
		std::cout << msg << "\n";
		return 1;
	}

	SDL_Quit();

	return 0;
}


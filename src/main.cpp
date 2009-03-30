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
	std::string state;
	po::options_description desc("Options");
	desc.add_options()
		("help", "show help")
		("state", po::value<std::string>(&state)->default_value("gameplay"), "start with state. Valid states are gameplay and editor")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	//std::string state = vm.count("state") ? vm["state"].as<std::string>() : "gameplay";

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Video initialization failed: " << SDL_GetError() << std::endl;
		return 1;
	}

	Toodeloo::Engine engine(1024, 768, false);

	try {
		if(state == "gameplay")
		{
			std::cout << "Starting gameplay" << std::endl;
			engine.pushState(boost::shared_ptr<Toodeloo::States::State>(new Toodeloo::States::Gameplay(engine)));
		}
		else if(state == "editor")
		{
			std::cout << "Starting editor" << std::endl;
			engine.pushState(boost::shared_ptr<Toodeloo::States::State>(new Toodeloo::States::Editor(engine)));
		}
		else
			throw "unknown state!!!!!!!";
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


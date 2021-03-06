#ifndef ENGINE_HPP
#define ENGINE_HPP

namespace Toodeloo
{
	namespace States
	{
		class State;
	}

	class Engine
	{
		public:
			struct Layers
			{
				enum Layer
				{
					None = 0,
					Background1 = 1,
					Background2 = 2,
					Background3 = 4,
					Playfield = 8,
					Interface1 = 16,
					Interface2 = 32,
					Interface3 = 64,
					Interface4 = 128,
					PlayerHands = 256
				};
			};
			Engine(int, int, bool);
			~Engine();

			void handleInput();
			void update();
			void draw();

			void pushState(boost::shared_ptr<States::State>);
			void changeState(boost::shared_ptr<States::State>);
			void popState();

			int getWidth() const { return _width; }
			int getHeight() const { return _height; }

			bool isRunning() const;
			void quit();
		private:
			bool _running;
			SDL_Surface* _surface;
			std::stack<boost::shared_ptr<States::State> > _states;
			int _width;
			int _height;
			void initGL();

			unsigned int _last_update;
	};
}

#endif


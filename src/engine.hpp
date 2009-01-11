#ifndef ENGINE_HPP
#define ENGINE_HPP

class AbstractState;

class Engine {
	public:
		Engine(int, int, bool);
		~Engine();

		void handleInput();
		void update();
		void draw();

		void pushState(boost::shared_ptr<AbstractState>);
		void changeState(boost::shared_ptr<AbstractState>);
		void popState();

		int getWidth() const;
		int getHeight() const;

		bool isRunning() const;
	private:
		bool _running;
		SDL_Surface* _surface;
		std::stack<boost::shared_ptr<AbstractState> > _states;
		int _width;
		int _height;
		void initGL();
};

#endif


#ifndef ABSTRACT_STATE_HPP
#define ABSTRACT_STATE_HPP

class AbstractState {
	public:
		AbstractState(Engine&);
		virtual ~AbstractState();
		virtual void update();
		virtual void draw();
		virtual void init();
		virtual void pause();
		virtual void resume();
		virtual void handleInput(const SDL_Event&);
	protected:
		Engine& _engine;
};

#endif


#ifndef STATES_STATE_HPP
#define STATES_STATE_HPP

namespace Toodeloo
{
	namespace States
	{
		class State {
			public:
				State(Engine&);
				virtual ~State();
				virtual void update();
				virtual void draw();
				virtual void init();
				virtual void pause();
				virtual void resume();
				virtual void handleInput(const SDL_Event&);
			protected:
				Engine& _engine;
		};
	}
}

#endif


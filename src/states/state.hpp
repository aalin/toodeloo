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
				virtual void update(unsigned int delta);
				virtual void draw();
				virtual void init();
				virtual void pause();
				virtual void resume();
				virtual void handleInput(const SDL_Event&);

				Engine& engine() { return _engine; }
			protected:
				Engine& _engine;
		};
	}
}

#endif


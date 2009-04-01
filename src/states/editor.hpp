#ifndef TOODELOO_STATES_EDITOR_HPP
#define TOODELOO_STATES_EDITOR_HPP

namespace Toodeloo
{
	class Player;

	namespace States
	{
		class Editor : public Toodeloo::States::State
		{
			public:
				Editor(Engine&);
				void update(unsigned int delta);
				void draw();
				void handleInput(const SDL_Event&);

			private:
				Map _map;
				Math::Vector2 _position;
		};
	}
}

#endif


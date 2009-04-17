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
				float _zoom;

				std::pair<Math::Vector2, Math::Vector2> box();
				Math::Vector2 screenToWorld(int x, int y);
		};
	}
}

#endif


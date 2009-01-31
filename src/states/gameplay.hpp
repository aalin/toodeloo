#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

namespace Toodeloo
{
	class Player;

	namespace States
	{

		class Gameplay : public Toodeloo::States::State
		{
			public:
				Gameplay(Engine&);
				void update();
				void draw();
				void handleInput(const SDL_Event&);

				Wrappers::Chipmunk::Space& space() { return _space; };

			private:
				Wrappers::Chipmunk::Space _space;
				Toodeloo::Player _player;
				Map _map;
				Toodeloo::Heightmap _heightmap;
		};
	}
}

#endif


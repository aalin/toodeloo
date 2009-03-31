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

			private:
				Toodeloo::Camera _camera;
				Toodeloo::Player _player;
				Map _map;

				b2AABB _worldAABB;
				boost::shared_ptr<b2World> _world;
				Graphics::DebugDraw _debug_draw;
		};
	}
}

#endif


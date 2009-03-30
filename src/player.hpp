#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace Toodeloo
{
	namespace States
	{
		class Gameplay;
	}

	class Player
	{
		public:
			Player(Toodeloo::States::Gameplay& state);
			~Player();

			void update();
			void draw();

			void goLeft();
			void goRight();
			void jump();
			void stop();

			Math::Vector2 position() const
			{
				return Math::Vector2(0.0, 0.0);
			}

		private:
			Toodeloo::States::Gameplay& _state;
	};
}

#endif


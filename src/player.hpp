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

			Wrappers::Chipmunk::Vector2 position() const { return _bodies.at("bottom")->position(); }

		private:
			Toodeloo::States::Gameplay& _state;
			Wrappers::Chipmunk::Shapes::Circle* _bottom;
			std::map<std::string, Wrappers::Chipmunk::Body*> _bodies;
	};
}

#endif


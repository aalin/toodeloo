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

			Toodeloo::Wrappers::Chipmunk::Vector2 position() const
			{
				std::map<std::string, Toodeloo::Wrappers::Chipmunk::Body*>::const_iterator it = _bodies.find("bottom");

				if(it == _bodies.end())
					throw std::runtime_error("There is no bottom!");

				return it->second->position();
			}

		private:
			Toodeloo::States::Gameplay& _state;
			Toodeloo::Wrappers::Chipmunk::Shapes::Circle* _bottom;
			std::map<std::string, Toodeloo::Wrappers::Chipmunk::Body*> _bodies;
	};
}

#endif


#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayState;

class Player
{
	public:
		Player(PlayState& state);
		~Player();

		void update();
		void draw();

		void goLeft();
		void goRight();
		void jump();
		void stop();

		Chipmunk::Vector2 position() const { return _bodies.at("bottom")->position(); }

	private:
		PlayState& _state;
		Chipmunk::Shapes::Circle* _bottom;
		std::map<std::string, Chipmunk::Body*> _bodies;
};

#endif


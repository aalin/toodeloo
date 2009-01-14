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

		Chipmunk::Vector2 position() const { return _body.position(); }

	private:
		Chipmunk::Body _body;
		Chipmunk::Body _tracer;
		std::vector<Chipmunk::Vector2> _vertices;
		PlayState& _state;
};

#endif


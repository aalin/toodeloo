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

	private:
		Chipmunk::Body _body;
		std::vector<Chipmunk::Vector2> _vertices;
		PlayState& _state;
};

#endif


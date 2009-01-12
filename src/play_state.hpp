#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

class Player;

class PlayState : public AbstractState
{
	public:
		PlayState(Engine&);
		void update();
		void draw();
		void handleInput(const SDL_Event&);

		Chipmunk::Space& space() { return _space; };

	private:
		Chipmunk::Space _space;
		Player _player;
};

#endif


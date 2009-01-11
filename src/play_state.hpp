#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

class PlayState : public AbstractState {
	public:
		PlayState(Engine&);
		void update();
		void draw();
		void handleInput(const SDL_Event&);
};

#endif


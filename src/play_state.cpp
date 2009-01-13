#include "common.hpp"

PlayState::PlayState(Engine& engine)
	: AbstractState(engine), _player(Player(*this))
{
	_space.gravity(cpv(0, -100));
}

void
PlayState::update()
{
	Uint8* keys = SDL_GetKeyState(NULL);
	_player.update();

	_space.update();
}

void
PlayState::handleInput(const SDL_Event& event)
{
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_LEFT:
				_player.goLeft();
				break;
			case SDLK_RIGHT:
				_player.goRight();
				break;
			case SDLK_UP:
				_player.jump();
				break;
			default:
				break;
		}
	}
}

void
PlayState::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-320.0, 320.0, -240.0, 240.0, -1.0, 1.0);
	glTranslatef(0.5, 0.5, 0.0);

	glMatrixMode(GL_MODELVIEW);
	_player.draw();
}


#include "common.hpp"

PlayState::PlayState(Engine& engine)
	: AbstractState(engine)

{
}

void
PlayState::update()
{
	Uint8* keys = SDL_GetKeyState(NULL);
}

void
PlayState::handleInput(const SDL_Event& event)
{
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_F1:
				break;
			default:
				break;
		}
	}
}

void
PlayState::draw()
{
}


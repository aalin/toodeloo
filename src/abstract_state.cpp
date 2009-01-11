#include "common.hpp"

AbstractState::AbstractState(Engine& engine)
	: _engine(engine)
{ }

AbstractState::~AbstractState()
{ }

void
AbstractState::update()
{ }

void
AbstractState::draw()
{ }

void
AbstractState::init()
{ }

void
AbstractState::pause()
{ }

void
AbstractState::resume()
{ }

void
AbstractState::handleInput(const SDL_Event&)
{ }

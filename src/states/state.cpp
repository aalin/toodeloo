#include "../common.hpp"

namespace Toodeloo
{
	namespace States
	{
		State::State(Engine& engine)
			: _engine(engine)
		{ }

		State::~State()
		{ }

		void
		State::update(unsigned int delta)
		{ }

		void
		State::draw()
		{ }

		void
		State::init()
		{ }

		void
		State::pause()
		{ }

		void
		State::resume()
		{ }

		void
		State::handleInput(const SDL_Event&)
		{ }
	}
}

#include "../common.hpp"

namespace Toodeloo
{
	namespace States
	{
		Editor::Editor(Engine& engine)
			: Toodeloo::States::State(engine),
			  _map(*this, "map.txt"),
		      _position(0.0, 0.0),
		      _zoom(1.0)
		{
		}

		Math::Vector2
		Editor::screenToWorld(int x, int y)
		{
			// This is from the box2d testbed
			float u = x / static_cast<float>(engine().getWidth());
			float v = y / static_cast<float>(engine().getHeight());

			return Math::Vector2(
				(1.0 - u) * box().second.x + u * box().first.x,
				(1.0 - v) * box().second.y + v * box().first.y
			);
		}

		void
		Editor::update(unsigned int delta)
		{
			Uint8* keys = SDL_GetKeyState(NULL);
			float speed = 3.0;
			_map.update();
		}

		void
		Editor::handleInput(const SDL_Event& event)
		{
			//	uint8_t* keys = SDL_GetKeyState(NULL);

			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						_position -= Math::Vector2(_zoom, 0);
						break;
					case SDLK_RIGHT:
						_position += Math::Vector2(_zoom, 0);
						break;
					case SDLK_UP:
						_position -= Math::Vector2(0, _zoom);
						break;
					case SDLK_DOWN:
						_position += Math::Vector2(0, _zoom);
						break;
					case SDLK_z:
						_zoom *= 0.5;
						break;
					case SDLK_x:
						_zoom *= 1.5;
						break;
					case SDLK_ESCAPE:
						_engine.quit();
						break;
					default:
						break;
				}
			}
		}

		std::pair<Math::Vector2, Math::Vector2>
		Editor::box()
		{
			float ratio = engine().getWidth() / static_cast<float>(engine().getHeight());
			Math::Vector2 extents(ratio * 25.0, 25.0);
			extents *= _zoom;
			return std::pair<Math::Vector2, Math::Vector2>(_position - extents, _position + extents);
		}

		void
		Editor::draw()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, engine().getWidth(), engine().getHeight());
			glOrtho(box().first.x, box().second.x, box().second.y, box().first.y, -1.0, 1.0);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();
			//glTranslatef(-_position.x, -_position.y, 0.0);
			//_map.draw();
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_TRIANGLES);
				glVertex3f(1.0, 1.0, 0.0);
				glVertex3f(3.0, 1.0, 0.0);
				glVertex3f(3.0, 3.0, 0.0);
			glEnd();
			glPopMatrix();
		}
	}
}

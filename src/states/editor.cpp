#include "../common.hpp"

namespace Toodeloo
{
	namespace States
	{
		Editor::Editor(Engine& engine)
			: Toodeloo::States::State(engine),
			  _map(*this, "map.txt"),
		      _position(0, 0)
		{
		}

		void
		Editor::update()
		{
			Uint8* keys = SDL_GetKeyState(NULL);
			float speed = 3.0;
/*			if(keys[SDLK_z]) _camera.move(Toodeloo::Math::Vector3( 0.0, 0.0, speed));
			if(keys[SDLK_x]) _camera.move(Toodeloo::Math::Vector3( 0.0, 0.0,-speed));

			if(keys[SDLK_w]) _camera.moveForward(speed);
			if(keys[SDLK_s]) _camera.moveForward(-speed);

			if(keys[SDLK_LEFT]) _camera.rotateY(Toodeloo::Math::Degrees(4));
			if(keys[SDLK_RIGHT]) _camera.rotateY(Toodeloo::Math::Degrees(-4));

			if(keys[SDLK_DOWN]) _camera.rotateX(Toodeloo::Math::Degrees(4));
			if(keys[SDLK_UP]) _camera.rotateX(Toodeloo::Math::Degrees(-4));
			if(keys[SDLK_a]) _camera.strafe(-speed);
			if(keys[SDLK_d]) _camera.strafe(speed);
			*/

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
						_position -= Math::Vector2(5, 0);
						break;
					case SDLK_RIGHT:
						_position += Math::Vector2(5, 0);
						break;
					case SDLK_UP:
						_position -= Math::Vector2(0, 5);
						break;
					case SDLK_DOWN:
						_position += Math::Vector2(0, 5);
						break;
					case SDLK_ESCAPE:
						_engine.quit();
						break;
					default:
						break;
				}
			}
		}

		void
		Editor::draw()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-320.0, 320.0, -240.0, 240.0, -1.0, 1.0);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();
			glTranslatef(-_position.x, -_position.y, 0.0);
			_map.draw();
			glPopMatrix();
		}
	}
}

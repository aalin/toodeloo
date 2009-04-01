#include "../common.hpp"

namespace Toodeloo
{
	namespace States
	{
		Gameplay::Gameplay(Engine& engine)
			: Toodeloo::States::State(engine),
			  _player(Toodeloo::Player(*this)),
			  _map(*this, "map.txt")
		{
			_worldAABB.upperBound.Set(100.0, 100.0);
			_worldAABB.lowerBound.Set(-100.0, -100.0);
			_world.reset(new b2World(_worldAABB, b2Vec2(0.0, -10.0), true));

			b2BodyDef ground_body_def;
			ground_body_def.position.Set(0.0, -10.0);
			b2Body* ground_body = _world->CreateBody(&ground_body_def);
			b2PolygonDef ground_shape_def;
			ground_shape_def.SetAsBox(50.0, 10.0);
			ground_body->CreateShape(&ground_shape_def);

			_debug_draw.SetFlags(
				b2DebugDraw::e_shapeBit | 
				b2DebugDraw::e_jointBit | 
				b2DebugDraw::e_coreShapeBit | 
				b2DebugDraw::e_aabbBit | 
				b2DebugDraw::e_obbBit | 
				b2DebugDraw::e_pairBit | 
				b2DebugDraw::e_centerOfMassBit
			);
		}

		void
		Gameplay::update(unsigned int delta)
		{
			Uint8* keys = SDL_GetKeyState(NULL);
			float speed = 3.0;
			if(keys[SDLK_z]) _camera.move(Toodeloo::Math::Vector3( 0.0, 0.0, speed));
			if(keys[SDLK_x]) _camera.move(Toodeloo::Math::Vector3( 0.0, 0.0,-speed));

			if(keys[SDLK_w]) _camera.moveForward(speed);
			if(keys[SDLK_s]) _camera.moveForward(-speed);

			if(keys[SDLK_LEFT]) _camera.rotateY(Toodeloo::Math::Degrees(4));
			if(keys[SDLK_RIGHT]) _camera.rotateY(Toodeloo::Math::Degrees(-4));

			if(keys[SDLK_DOWN]) _camera.rotateX(Toodeloo::Math::Degrees(4));
			if(keys[SDLK_UP]) _camera.rotateX(Toodeloo::Math::Degrees(-4));
			if(keys[SDLK_a]) _camera.strafe(-speed);
			if(keys[SDLK_d]) _camera.strafe(speed);

			_world->Step(delta / 100.0, 10);
			_world->Validate();

			_camera.update();
			_player.update();
			_map.update();
		}

		void
		Gameplay::handleInput(const SDL_Event& event)
		{
			//	uint8_t* keys = SDL_GetKeyState(NULL);

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
					case SDLK_ESCAPE:
						_engine.quit();
						break;
					default:
						break;
				}
			}
		}

		void
		Gameplay::draw()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-320.0, 320.0, -240.0, 240.0, -1.0, 1.0);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();

			_world->SetDebugDraw(&_debug_draw);
			_world->Step(0, 0);
			_world->SetDebugDraw(0);
			//glTranslatef(-_player.position().x, -_player.position().y, 0.0);
			//_player.draw();
			glPopMatrix();
		}
	}
}

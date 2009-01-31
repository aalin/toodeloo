#include "common.hpp"

namespace Toodeloo
{
	Bridge::Bridge(Toodeloo::Wrappers::Chipmunk::Space& space, Toodeloo::Wrappers::Chipmunk::Body& body1, Toodeloo::Wrappers::Chipmunk::Vector2 pos1, Toodeloo::Wrappers::Chipmunk::Body& body2, Toodeloo::Wrappers::Chipmunk::Vector2 pos2, int steps)
		: _space(space)
	{
		float delta_x = std::abs(pos1.x - pos2.x);
		float delta_y = std::abs(pos1.y - pos2.y);

		float step_x = delta_x / steps;
		float step_y = delta_y / steps;

		for(int i = 0; i < steps; i++)
		{
			float x = pos1.x + step_x * i;
			float y = pos2.y + step_y * i;

			std::cout << x << "x" << y << std::endl;

			Toodeloo::Wrappers::Chipmunk::Body* body = new Toodeloo::Wrappers::Chipmunk::Body(space, 5.0, INFINITY);
			body->position(cpv(x, y));

			Toodeloo::Wrappers::Chipmunk::Shapes::Circle* shape = new Toodeloo::Wrappers::Chipmunk::Shapes::Circle(*body, 2.5, cpvzero);
			shape->elasticity(1.0);
			shape->friction(1.0);

			body->addShape(shape);
			body->addToSpace();

			_bodies.push_back(body);
		}

		for(int i = 0; i < _bodies.size(); i++)
		{
			Toodeloo::Wrappers::Chipmunk::Body& one = (i == 0) ? body1 : *_bodies[i];
			Toodeloo::Wrappers::Chipmunk::Body& two = (i == _bodies.size() - 1) ? body2 : *_bodies[i+1];

			std::cout << "joint between " << &one << " and " << &two << std::endl;
			space.addJoint(new Toodeloo::Wrappers::Chipmunk::Joints::Slide(one, two, cpv(0, 0), cpv(0.1, 0.1), 20, 40));
		}
	}
}


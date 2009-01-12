#include "common.hpp"

namespace Chipmunk {

// Space

	Space::Space()
	{
		_p = cpSpaceNew();
		cpSpaceResizeStaticHash(_p, 20.0, 999);
	}

	Space::~Space()
	{
		cpSpaceFreeChildren(_p);
		cpSpaceFree(_p);
	}

	Vector2
	Space::gravity() const
	{
		return _p->gravity;
	}

	Space&
	Space::gravity(Vector2 v)
	{
		_p->gravity = v;
		return *this;
	}

	void
	Space::update()
	{
		for(int i = 0; i < 2; i++)
			cpSpaceStep(_p, 1.0 / 60.0 / 2);
	}

	Space&
	Space::addStaticShape(Shape& shape)
	{
		cpSpaceAddStaticShape(_p, shape.p());
	}

	Space&
	Space::addBody(Body& body)
	{
		cpSpaceAddBody(_p, body.p());
	}

// Body

	Body::Body(float m, float i)
	{
		_p = cpBodyNew(m, i);
	}

	Body::~Body()
	{
		cpBodyDestroy(_p);
		cpBodyFree(_p);
	}

	float Body::mass() const { return _p->m; }
	float Body::moment() const { return _p->i; }
	Vector2 Body::rotation() const { return _p->rot; }
	Vector2 Body::position() const { return _p->p; }

	Body& Body::mass(float m) { cpBodySetMass(_p, m); return *this; }
	Body& Body::moment(float i) { cpBodySetMoment(_p, i); return *this; }
	Body& Body::angle(float a) { cpBodySetAngle(_p, a); return *this; }
	Body& Body::position(Vector2 p) { _p->p = p; return *this; }

	Body&
	Body::slew(Vector2 pos, float dt)
	{
		cpBodySlew(_p, pos, dt); return *this;
	}

	Body&
	Body::updateVelocity(Vector2 gravity, float damping, float dt)
	{
		cpBodyUpdateVelocity(_p, gravity, damping, dt); return *this;
	}

	Body&
	Body::updatePosition(float dt)
	{
		cpBodyUpdatePosition(_p, dt);
		return *this;
	}

	Body&
	Body::applyImpulse(Vector2 j, Vector2 r)
	{
		cpBodyApplyImpulse(_p, j, r);
		return *this;
	}

	Body&
	Body::resetForces()
	{
		cpBodyResetForces(_p);
		return *this;
	}

	Body&
	Body::applyForce(Vector2 f, Vector2 r)
	{
		cpBodyApplyForce(_p, f, r);
	}

	Body&
	Body::dampedSpring(Body& other, Vector2 anchr1, Vector2 anchr2, float rlen, float k, float dmp, float dt)
	{
		cpDampedSpring(_p, other.p(), anchr1, anchr2, rlen, k, dmp, dt);
		return *this;
	}

	Shape&
	Body::shapeCircle(float radius, Vector2 offset)
	{
		_shapes.push_back(Shape::circle(*this, radius, offset));
		return _shapes[_shapes.size() - 1];
	}

	Shape&
	Body::shapePolygon(std::vector<Vector2> vertices, Vector2 offset)
	{
		_shapes.push_back(Shape::polygon(*this, vertices, offset));
		return _shapes[_shapes.size() - 1];
	}

	Shape&
	Body::shapeSegment(Vector2 a, Vector2 b, float radius)
	{
		_shapes.push_back(Shape::segment(*this, a, b, radius));
		return _shapes[_shapes.size() - 1];
	}

// Shape

	Shape::Shape(cpShape* shape)
	{
		_p = shape;
	}

	Shape
	Shape::circle(Body& body, float radius, Vector2 offset)
	{
		return Shape(cpCircleShapeNew(body.p(), radius, offset));
	}

	Shape
	Shape::polygon(Body& body, std::vector<Vector2> vertices, Vector2 offset)
	{
		return Shape(cpPolyShapeNew(body.p(), vertices.size(), &vertices[0], offset));
	}

	Shape
	Shape::segment(Body& body, Vector2 a, Vector2 b, float radius)
	{
		return Shape(cpSegmentShapeNew(body.p(), a, b, radius));
	}

	float Shape::elasticity() const { return _p->e; }

	float Shape::friction() const { return _p->u; }

	Shape& Shape::elasticity(float e) { _p->e = e; return *this; }
	Shape& Shape::friction(float u) { _p->u = u; return *this; }
}

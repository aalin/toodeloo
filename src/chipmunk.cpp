#include "common.hpp"

namespace Chipmunk {

// Space

	Space::Space()
	{
		_space = cpSpaceNew();
		cpSpaceResizeStaticHash(_space, 20.0, 999);
	}

	Space::~Space()
	{
		cpSpaceFreeChildren(_space);
		cpSpaceFree(_space);
	}

	Vector2
	Space::gravity() const
	{
		return _space->gravity;
	}

	Space&
	Space::gravity(Vector2 v)
	{
		_space->gravity = v;
		return *this;
	}

// Body

	Body::Body(float m, float i)
	{
		_body = cpBodyNew(m, i);
	}

	Body::~Body()
	{
		cpBodyDestroy(_body);
		cpBodyFree(_body);
	}

	float Body::mass() const { return _body->m; }
	float Body::moment() const { return _body->i; }
	Vector2 Body::rotation() const { return _body->rot; }

	Body& Body::mass(float m) { cpBodySetMass(_body, m); return *this; }
	Body& Body::moment(float i) { cpBodySetMoment(_body, i); return *this; }
	Body& Body::angle(float a) { cpBodySetAngle(_body, a); return *this; }

	Body&
	Body::slew(Vector2 pos, float dt)
	{
		cpBodySlew(_body, pos, dt); return *this;
	}

	Body&
	Body::updateVelocity(Vector2 gravity, float damping, float dt)
	{
		cpBodyUpdateVelocity(_body, gravity, damping, dt); return *this;
	}

	Body&
	Body::updatePosition(float dt)
	{
		cpBodyUpdatePosition(_body, dt);
		return *this;
	}

	Body&
	Body::applyImpulse(Vector2 j, Vector2 r)
	{
		cpBodyApplyImpulse(_body, j, r);
		return *this;
	}

	Body&
	Body::resetForces()
	{
		cpBodyResetForces(_body);
		return *this;
	}

	Body&
	Body::applyForce(Vector2 f, Vector2 r)
	{
		cpBodyApplyForce(_body, f, r);
	}

	Body&
	Body::dampedSpring(Body& other, Vector2 anchr1, Vector2 anchr2, float rlen, float k, float dmp, float dt)
	{
		cpDampedSpring(_body, other._body, anchr1, anchr2, rlen, k, dmp, dt);
		return *this;
	}

// Shape

	Shape::Shape(boost::shared_ptr<ShapeWrapper> shape_wrapper)
		: _shape_wrapper(shape_wrapper)
	{
	}

	Shape::Shape(cpShape* shape)
	{
		_shape_wrapper.reset(new ShapeWrapper(shape));
	}

	Shape
	Shape::circle(Body& body, float radius, Vector2 offset)
	{
		return Shape(cpCircleShapeNew(body.chipmunkBody(), radius, offset));
	}

	Shape
	Shape::polygon(Body& body, std::vector<Vector2> vertices, Vector2 offset)
	{
		return Shape(cpPolyShapeNew(body.chipmunkBody(), vertices.size(), &vertices[0], offset));
	}

	Shape
	Shape::segment(Body& body, Vector2 a, Vector2 b, float radius)
	{
		return Shape(cpSegmentShapeNew(body.chipmunkBody(), a, b, radius));
	}
}

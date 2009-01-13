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
		//cpSpaceFreeChildren(_p);
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
	Space::addShape(Shapes::Shape* shape)
	{
		cpSpaceAddShape(_p, shape->p());
	}

	Space&
	Space::addStaticShape(Shapes::Shape* shape)
	{
		cpSpaceAddStaticShape(_p, shape->p());
	}

	Space&
	Space::addBody(Body& body)
	{
		cpSpaceAddBody(_p, body.p());
	}

// Body

	Body::Body(Space& space, float m, float i)
		: _space(space)
	{
		_p = cpBodyNew(m, i);
		_space.addBody(*this);
	}

	Body::~Body()
	{
		BOOST_FOREACH(Shapes::Shape* shape, _shapes)
		{
			delete shape;
		}

		cpBodyFree(_p);
	}

	float Body::mass() const { return _p->m; }
	float Body::moment() const { return _p->i; }
	Vector2 Body::rotation() const { return _p->rot; }
	Vector2 Body::position() const { return _p->p; }
	Vector2 Body::velocity() const { return _p->v; }
	Vector2 Body::force() const { return _p->f; }

	Body& Body::mass(float m) { cpBodySetMass(_p, m); return *this; }
	Body& Body::moment(float i) { cpBodySetMoment(_p, i); return *this; }
	Body& Body::angle(float a) { cpBodySetAngle(_p, a); return *this; }
	Body& Body::position(Vector2 p) { _p->p = p; return *this; }
	Body& Body::velocity(Vector2 v) { _p->v = v; return *this; }
	Body& Body::force(Vector2 f) { _p->f = f; return *this; }

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

	void
	Body::addShape(Shapes::Shape* shape)
	{
		_shapes.push_back(shape);
		_space.addShape(shape);
	}

// Shape

	Shapes::Shape::~Shape()
	{
		cpShapeFree(_p);
	}

	float Shapes::Shape::elasticity() const { return _p->e; }
	float Shapes::Shape::friction() const { return _p->u; }

	Shapes::Shape& Shapes::Shape::elasticity(float e) { _p->e = e; return *this; }
	Shapes::Shape& Shapes::Shape::friction(float u) { _p->u = u; return *this; }

	// Circle

	Shapes::Circle::Circle(Body& body, float radius, Vector2 offset)
	{
		_p = cpCircleShapeNew(body.p(), radius, offset);
	}

	// Polygon

	Shapes::Polygon::Polygon(Body& body, std::vector<Vector2> vertices, Vector2 offset)
	{
		_p = cpPolyShapeNew(body.p(), vertices.size(), &vertices[0], offset);
	}

	// Segment

	Shapes::Segment::Segment(Body& body, Vector2 a, Vector2 b, float radius)
	{
		_p = cpSegmentShapeNew(body.p(), a, b, radius);
	}

}

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

		BOOST_FOREACH(Joints::Joint* joint, _joints)
			delete joint;
	}

	Vector2
	Space::gravity() const
	{
		return _p->gravity;
	}

	int
	Space::iterations() const
	{
		return _p->iterations;
	}

	int
	Space::elasticIterations() const
	{
		return _p->elasticIterations;
	}

	Space&
	Space::gravity(Vector2 v)
	{
		_p->gravity = v;
		return *this;
	}

	Space&
	Space::iterations(int iterations)
	{
		_p->iterations = iterations;
	}

	Space&
	Space::elasticIterations(int elastic_iterations)
	{
		_p->elasticIterations = elastic_iterations;
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
		std::cout << "Space::addStaticShape(" << shape << ")" << std::endl;
		cpSpaceAddStaticShape(_p, shape->p());
	}

	Space&
	Space::addBody(Body& body)
	{
		std::cout << "Space::addBody(" << &body << ")" << std::endl;
		cpSpaceAddBody(_p, body.p());
	}

	Space&
	Space::addJoint(Joints::Joint* joint)
	{
		_joints.push_back(joint);
		cpSpaceAddJoint(_p, joint->p());
	}

	void
	Space::draw()
	{
		glColor3f(1.0, 1.0, 1.0);
		cpSpaceHashEach(_p->activeShapes, &Space::drawObject, 0);
		cpSpaceHashEach(_p->staticShapes, &Space::drawObject, 0);
		cpArrayEach(_p->joints, &Space::drawJoint, 0);
	}

	void
	Space::drawJoint(void* ptr, void* unused)
	{
		cpJoint* joint = static_cast<cpJoint*>(ptr);

		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(joint->a->p.x, joint->a->p.y, 0.0);
		glVertex3f(joint->b->p.x, joint->b->p.y, 0.0);
		glEnd();
	}

	void
	Space::drawObject(void* ptr, void* unused)
	{
		cpShape* shape = static_cast<cpShape*>(ptr);

		switch(shape->klass->type)
		{
			case CP_CIRCLE_SHAPE:
				Space::drawCircleShape(shape);
				break;
			case CP_SEGMENT_SHAPE:
				Space::drawSegmentShape(shape);
				break;
			case CP_POLY_SHAPE:
				Space::drawPolyShape(shape);
				break;
			default:
				std::cout << "bad enum in drawObject" << std::endl;
				break;
		}
	}

	void drawCircle(cpFloat x, cpFloat y, cpFloat r, cpFloat a)
	{
		const int segs = 15;
		const cpFloat coef = 2.0 * 3.0849609375 / (cpFloat)segs;

		glBegin(GL_LINE_STRIP);
			for(int n = 0; n <= segs; n++)
			{
				cpFloat rads = n*coef;
				glVertex2f(r*std::cos(rads + a) + x, r*std::sin(rads + a) + y);
			}
			glVertex2f(x,y);
		glEnd();
	}

	void
	Space::drawCircleShape(cpShape* shape)
	{
		cpBody *body = shape->body;
		cpCircleShape *circle = (cpCircleShape *)shape;
		cpVect c = cpvadd(body->p, cpvrotate(circle->c, body->rot));
		drawCircle(c.x, c.y, circle->r, body->a);
	}

	void
	Space::drawSegmentShape(cpShape* shape)
	{
		cpBody *body = shape->body;
		cpSegmentShape *seg = (cpSegmentShape *)shape;
		cpVect a = cpvadd(body->p, cpvrotate(seg->a, body->rot));
		cpVect b = cpvadd(body->p, cpvrotate(seg->b, body->rot));

		glBegin(GL_LINES);
			glVertex2f(a.x, a.y);
			glVertex2f(b.x, b.y);
		glEnd();
	}

	void
	Space::drawPolyShape(cpShape* shape)
	{
		cpBody *body = shape->body;
		cpPolyShape *poly = (cpPolyShape *)shape;

		int num = poly->numVerts;
		cpVect *verts = poly->verts;

		glBegin(GL_LINE_LOOP);
			for(int i=0; i<num; i++)
			{
				cpVect v = cpvadd(body->p, cpvrotate(verts[i], body->rot));
				glVertex2f(v.x, v.y);
			}
		glEnd();
	}

// Body

	Body::Body(Space& space, float m, float i)
		: _space(space)
	{
		_p = cpBodyNew(m, i);
	}

	Body::~Body()
	{
		BOOST_FOREACH(Shapes::Shape* shape, _shapes)
		{
			delete shape;
		}

		cpBodyFree(_p);
	}

	void
	Body::addToSpace()
	{
		_space.addBody(*this);
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

	void
	Body::addStaticShape(Shapes::Shape* shape)
	{
		_shapes.push_back(shape);
		_space.addStaticShape(shape);
	}

// Shape

	Shapes::Shape::~Shape()
	{
		cpShapeFree(_p);
	}

	float Shapes::Shape::elasticity() const { return _p->e; }
	float Shapes::Shape::friction() const { return _p->u; }
	int Shapes::Shape::group() const { return _p->group; }
	int Shapes::Shape::layers() const { return _p->layers; }

	Shapes::Shape& Shapes::Shape::elasticity(float e) { _p->e = e; return *this; }
	Shapes::Shape& Shapes::Shape::friction(float u) { _p->u = u; return *this; }
	Shapes::Shape& Shapes::Shape::group(int g) { _p->group = g; return *this; }
	Shapes::Shape& Shapes::Shape::layers(int l) { _p->layers = l; return *this; }

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

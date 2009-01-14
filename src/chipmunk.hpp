#ifndef CHIPMUNK_HPP
#define CHIPMUNK_HPP

namespace Chipmunk {
	typedef cpVect Vector2;
	class Body;

	namespace Shapes
	{
		class Shape;
	}

	namespace Joints
	{
		class Joint;
	}

	class Space
	{
		public:
			Space();
			~Space();

			Vector2 gravity() const;
			Space& gravity(Vector2 v);

			void draw();
			void update();

			Space& addShape(Shapes::Shape*);
			Space& addStaticShape(Shapes::Shape*);
			Space& addBody(Body&);

			Space& addJoint(Joints::Joint*);

			cpSpace* p() { return _p; }
			
		private:
			cpSpace* _p;
			std::vector<Joints::Joint*> _joints;
			static void drawObject(void* ptr, void* unused);
			static void drawCircleShape(cpShape* shape);
			static void drawSegmentShape(cpShape* shape);
			static void drawPolyShape(cpShape* shape);
	};

	class Body
	{
		public:
			Body(Space& _space, float m, float i);
			~Body();

			void addToSpace();

			float mass() const;
			float moment() const;
			Vector2 rotation() const;
			Vector2 position() const;
			Vector2 velocity() const;
			Vector2 force() const;

			Body& mass(float);
			Body& moment(float);
			Body& angle(float);
			Body& position(Vector2);
			Body& velocity(Vector2);
			Body& force(Vector2);

			Body& slew(Vector2 pos, float dt);
			Body& updateVelocity(Vector2 gravity, float damping, float dt);
			Body& updatePosition(float dt);

			Body& applyImpulse(Vector2, Vector2);
			Body& resetForces();
			Body& applyForce(Vector2, Vector2);

			void addShape(Shapes::Shape*);
			void addStaticShape(Shapes::Shape*);

			// Apply a spring force between this and another body at anchors anchr1 and anchr2
			// respectively. k is the spring constant (Young's modulus), rlen is the
			// rest length of the spring, dmp is the damping constant (force/velocity),
			// and dt is the time step to apply the force over. Note: not solving the
			// damping forces in the impulse solver causes problems with large damping values.
			// This function will eventually be replaced by a new constraint (joint) type.
			Body& dampedSpring(Body& other, Vector2 anchr1, Vector2 anchr2, float rlen, float k, float dmp, float dt);

			cpBody* p() { return _p; };

		private:
			Space& _space;
			cpBody* _p;
			std::vector<Shapes::Shape*> _shapes;
	};

	namespace Joints
	{
		class Joint
		{
			public:
				~Joint()
				{
					cpJointFree(_p);
				}

				cpJoint* p() { return _p; }
			protected:
				cpJoint* _p;
		};

		class Pin : public Joint
		{
			public:
				Pin(Body& a, Body& b, Vector2 anchr1, Vector2 anchr2)
				{
					_p = cpPinJointNew(a.p(), b.p(), anchr1, anchr2);
				}
		};

		class Slide : public Joint
		{
			public:
				Slide(Body& a, Body& b, Vector2 anchr1, Vector2 anchr2, float min, float max)
				{
					_p = cpSlideJointNew(a.p(), b.p(), anchr1, anchr2, min, max);
				}
		};

		class Pivot : public Joint
		{
			public:
				Pivot(Body& a, Body& b, Vector2 pivot)
				{
					_p = cpPivotJointNew(a.p(), b.p(), pivot);
				}
		};

		class Groove : public Joint
		{
			public:
				Groove(Body& a, Body& b, Vector2 groove_a, Vector2 groove_b, Vector2 anchr2)
				{
					_p = cpGrooveJointNew(a.p(), b.p(), groove_a, groove_b, anchr2);
				}
		};
	};

	namespace Shapes
	{
		class Shape
		{
			public:
				~Shape();

				cpShape* p() { return _p; };
				
				bool isInitialized();

				float elasticity() const;
				float friction() const;
				int group() const;
				int layers() const;

				// TODO: virtual void draw() = 0;

				Shape& elasticity(float e);
				Shape& friction(float u);
				Shape& group(int g);
				Shape& layers(int l);

			protected:
				cpShape* _p;
		};

		class Circle : public Shape
		{
			public:
				Circle(Body& body, float radius, Vector2 offset);
		};

		class Polygon : public Shape
		{
			public:
				Polygon(Body& body, std::vector<Vector2> vertices, Vector2 offset);
		};

		class Segment : public Shape
		{
			public:
				Segment(Body& body, Vector2 a, Vector2 b, float radius);
		};
	}
}

#endif


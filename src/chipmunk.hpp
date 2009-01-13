#ifndef CHIPMUNK_HPP
#define CHIPMUNK_HPP

namespace Chipmunk {
	typedef cpVect Vector2;
	class Body;

	namespace Shapes
	{
		class Shape;
	}

	class Space
	{
		public:
			Space();
			~Space();

			Vector2 gravity() const;
			Space& gravity(Vector2 v);

			void update();

			Space& addStaticShape(Shapes::Shape*);
			Space& addBody(Body&);

			cpSpace* p() { return _p; }
			
		private:
			cpSpace* _p;
	};

	class Body
	{
		public:
			Body(float m, float i);
			~Body();

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

			// Apply a spring force between this and another body at anchors anchr1 and anchr2
			// respectively. k is the spring constant (Young's modulus), rlen is the
			// rest length of the spring, dmp is the damping constant (force/velocity),
			// and dt is the time step to apply the force over. Note: not solving the
			// damping forces in the impulse solver causes problems with large damping values.
			// This function will eventually be replaced by a new constraint (joint) type.
			Body& dampedSpring(Body& other, Vector2 anchr1, Vector2 anchr2, float rlen, float k, float dmp, float dt);

			cpBody* p() { return _p; };

		private:
			cpBody* _p;
			std::vector<Shapes::Shape*> _shapes;
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

				// TODO: virtual void draw() = 0;

				Shape& elasticity(float e);
				Shape& friction(float u);

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


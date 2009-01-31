#ifndef CAMERA_HPP
#define CAMERA_HPP

namespace Toodeloo
{
	class Camera
	{
		public:
			Camera();
			void set(const Toodeloo::Math::Vector3&, const Toodeloo::Math::Vector3&, const Toodeloo::Math::Vector3&);
			void move(const Toodeloo::Math::Vector3&);
			void moveForward(float);
			void strafe(float);
			void rotateX(const Toodeloo::Math::Angle&);
			void rotateY(const Toodeloo::Math::Angle&);
			void rotateZ(const Toodeloo::Math::Angle&);
			const Toodeloo::Math::Vector3& getPosition() const { return _position; };
			void update();
			void draw() const;
			void debug() const;
		private:
			Toodeloo::Math::Vector3 _up;
			Toodeloo::Math::Vector3 _forward;
			Toodeloo::Math::Vector3 _right;
			Toodeloo::Math::Vector3 _position;
	};
}

#endif


#include "common.hpp"

namespace Toodeloo
{
	Camera::Camera()
	{
		_position = Toodeloo::Math::Vector3(5.0,-30.0, 5.0);
		_forward = Toodeloo::Math::Vector3(0.0,1.0, 0.0);
		_right = Toodeloo::Math::Vector3(1.0, 0.0, 0.0);
		_up = Toodeloo::Math::Vector3(0.0, 0.0, 1.0);
	}

	void
		Camera::update()
		{ }

	void
		Camera::set(const Toodeloo::Math::Vector3& pos, const Toodeloo::Math::Vector3& forward, const Toodeloo::Math::Vector3& up)
		{
			_position = pos;
			_forward = forward;
			_up = up;
		}

	void
		Camera::rotateX(const Toodeloo::Math::Angle& angle)
		{
			_forward = (
					_forward * angle.cos() +
					_up * angle.sin()
					).normalize();
			//_up = _forward.crossProduct(_right) * -1;
			_up = Toodeloo::Math::Vector3(0.0, 0.0, 1.0);
		}

	void
		Camera::rotateY(const Toodeloo::Math::Angle& angle)
		{
			_forward = (
					_forward * angle.cos() -
					_right * angle.sin()
					).normalize();
			_right = _forward.crossProduct(_up);
		}

	void
		Camera::rotateZ(const Toodeloo::Math::Angle& angle)
		{
			_right = (
					_right * angle.cos() +
					_up * angle.sin()
					).normalize();
			//_up = _forward.crossProduct(_right) * -1;
			_up = Toodeloo::Math::Vector3(0.0, 0.0, 1.0);
		}

	void
		Camera::draw() const
		{
			Toodeloo::Math::Vector3 point = _position + _forward;
			gluLookAt(
					_position.x, _position.y, _position.z,
					point.x, point.y, point.z,
					_up.x, _up.y, _up.z
					);
		}

	void
		Camera::move(const Toodeloo::Math::Vector3& v)
		{
			_position += v;
		}

	void
		Camera::strafe(float distance)
		{
			_position = _position + _right * distance;
		}

	void
		Camera::moveForward(float distance)
		{
			_position = _position + _forward * distance;
		}

}

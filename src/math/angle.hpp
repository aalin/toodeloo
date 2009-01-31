#ifndef ANGLE_HPP
#define ANGLE_HPP

namespace Toodeloo
{
	namespace Math
	{
		class Angle {
			public:
				Angle(float value)
					: _value(value)
				{ }

				Angle()
					: _value(0.0)
				{ }

				virtual ~Angle()
				{ }

				float value() const
				{
					return _value;
				}

				virtual float getFullCircle() const = 0;

				float cos() const;
				float sin() const;
				float tan() const;

				Angle& setValue(float value)
				{
					_value = value; return *this;
				}

			protected:
				float _value;

				float convert(const Angle& other) const
				{
					return other.value() * getFullCircle() / other.getFullCircle();
				}
		};

		class Radians : public Angle {
			public:
				Radians(float f) : Angle(f) {}
				Radians(const Angle& other) { _value = convert(other); }
				float getFullCircle() const;
		};

		class Degrees : public Angle {
			public:
				Degrees(float f) : Angle(f) {}
				Degrees(const Angle& other) { _value = convert(other); }
				float getFullCircle() const;
		};
	}
}

#endif


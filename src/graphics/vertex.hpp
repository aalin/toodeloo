#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace Toodeloo
{
	namespace Graphics
	{
		struct Vertex {
			Toodeloo::Math::Vector3 position;
			Toodeloo::Math::Vector3 normal;
			Toodeloo::Math::Vector2 texcoord;
			uint32_t color;
		};
	}
}

#endif


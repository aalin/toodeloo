#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace Toodeloo
{
	namespace Graphics
	{
		class Geometry {
			public:
				Geometry();
				void draw();
				void pushVertex(const Toodeloo::Graphics::Vertex&);

			private:
				void readyBuffers();
				void drawBuffers();
				std::vector<Toodeloo::Math::Vector3> _positions;
				std::vector<Toodeloo::Math::Vector3> _normals;
				std::vector<Toodeloo::Math::Vector2> _texcoords;
				std::vector<uint32_t> _colors;
				boost::shared_ptr<Toodeloo::Wrappers::VBO> _position_buffer;
				boost::shared_ptr<Toodeloo::Wrappers::VBO> _normal_buffer;
				boost::shared_ptr<Toodeloo::Wrappers::VBO> _texcoord_buffer;
				boost::shared_ptr<Toodeloo::Wrappers::VBO> _color_buffer;
		};
	}
}

#endif


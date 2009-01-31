#include "common.hpp"

namespace Toodeloo
{
	Heightmap::Heightmap(std::string filename)
		: _heightmap(filename)
	{
		printf("%dx%d: %8x\n", 32, 64, _heightmap.at(32, 64));
		for(int y = 0; y < _heightmap.getHeight() - 1; y++)
		{
			for(int x = 0; x < _heightmap.getWidth() - 1; x++)
			{
				std::vector<Toodeloo::Graphics::Vertex> vertices(this->at(x, y));

				_geometry.pushVertex(vertices[0]);
				_geometry.pushVertex(vertices[1]);
				_geometry.pushVertex(vertices[2]);

				_geometry.pushVertex(vertices[0]);
				_geometry.pushVertex(vertices[2]);
				_geometry.pushVertex(vertices[3]);
			}
		}
	}

	Heightmap::~Heightmap()
	{
	}

	void
		Heightmap::update()
		{
		}

	void
		Heightmap::draw()
		{
			_geometry.draw();
		}

	float
		Heightmap::heightAt(int x, int y) const
		{
			uint8_t alpha = (_heightmap.at(x, y) & 0xff000000) >> 24;
			return alpha / 256.0 * 100.0;
		}

	std::vector<Toodeloo::Graphics::Vertex>
		Heightmap::at(int x, int y)
		{
			std::vector<Toodeloo::Graphics::Vertex> vertices(4);

			vertices[0].position = Toodeloo::Math::Vector3(x + 0.0, y + 0.0, heightAt(x + 0, y + 0));
			vertices[1].position = Toodeloo::Math::Vector3(x + 1.0, y + 0.0, heightAt(x + 1, y + 0));
			vertices[2].position = Toodeloo::Math::Vector3(x + 1.0, y + 1.0, heightAt(x + 1, y + 1));
			vertices[3].position = Toodeloo::Math::Vector3(x + 0.0, y + 1.0, heightAt(x + 0, y + 1));

			BOOST_FOREACH(Toodeloo::Graphics::Vertex& vertex, vertices)
			{
				vertex.normal = vertex.position.getNormalized();
			}

			vertices[0].color = _heightmap.at(x + 0, y + 0);
			vertices[1].color = _heightmap.at(x + 1, y + 0);
			vertices[2].color = _heightmap.at(x + 1, y + 1);
			vertices[3].color = _heightmap.at(x + 0, y + 1);

			return vertices;
		}
}

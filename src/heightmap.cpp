#include "common.hpp"

Heightmap::Heightmap(std::string filename)
	: _heightmap(filename)
{
	for(int y = 0; y < _heightmap.getHeight() - 1; y++)
	{
		for(int x = 0; x < _heightmap.getWidth() - 1; x++)
		{
			std::vector<Vertex> vertices(this->at(x, y));

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
	uint8_t red = (_heightmap.at(x, y) & 0x00ff0000) >> 16;
	return red / 256.0 * 100.0;
}

std::vector<Vertex>
Heightmap::at(int x, int y)
{
	std::vector<Vertex> vertices(4);

	vertices[0].position = Vector3(x + 0.0, y + 0.0, heightAt(x + 0, y + 0));
	vertices[1].position = Vector3(x + 1.0, y + 0.0, heightAt(x + 1, y + 0));
	vertices[2].position = Vector3(x + 1.0, y + 1.0, heightAt(x + 1, y + 1));
	vertices[3].position = Vector3(x + 0.0, y + 1.0, heightAt(x + 0, y + 1));

	vertices[0].color = _heightmap.at(x + 0, y + 0) | 0xff000000;
	vertices[0].color = _heightmap.at(x + 1, y + 0) | 0xff000000;
	vertices[0].color = _heightmap.at(x + 1, y + 1) | 0xff000000;
	vertices[0].color = _heightmap.at(x + 0, y + 1) | 0xff000000;

	return vertices;
}


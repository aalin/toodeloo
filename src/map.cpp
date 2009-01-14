#include "common.hpp"
#include <fstream>
#include <sstream>

Map::Map(PlayState& state, std::string filename)
	: _body(state.space(), INFINITY, INFINITY)
{
	std::ifstream f(filename.c_str());
	if(!f.good())
		throw std::runtime_error("file not found");

	std::vector<std::vector<Chipmunk::Vector2> > shapes;

	std::vector<Chipmunk::Vector2> current_shape;

	while(f.good())
	{
		std::string line;
		getline(f, line);

		if(line.length() == 0)
		{
			if(current_shape.size() == 0)
				continue;

			shapes.push_back(current_shape);
			std::vector<Chipmunk::Vector2>().swap(current_shape);
		}
		else
		{
			std::stringstream ss;
			ss << line;

			Chipmunk::Vector2 v;
			ss >> v.x;
			ss >> v.y;
			current_shape.push_back(v);
		}
	}
	
	BOOST_FOREACH(std::vector<Chipmunk::Vector2> shape, shapes)
	{
		std::cout << "New shape: " << std::endl;
		for(int i = 0; i < shape.size(); i++)
		{
			int j = 0;
			if(i < (shape.size() - 1))
				j = i + 1;

			Chipmunk::Shapes::Shape* p = new Chipmunk::Shapes::Segment(_body, shape[i], shape[j], 1.0);
			_body.addStaticShape(p);
			std::cout << "  Segment: " << shape[i].x << "x" << shape[i].y << " - " << shape[j].x << "x" << shape[j].y << std::endl;
		}
	}
}

void
Map::update()
{
	// std::cout << _body.position().x << "x" << _body.position().y << std::endl;
}


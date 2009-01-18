#include "common.hpp"
#include <fstream>
#include <sstream>

Map::Map(PlayState& state, std::string filename)
	: _body(state.space(), INFINITY, INFINITY)
{
	std::vector<std::vector<Chipmunk::Vector2> > shapes = load(state, filename);

	BOOST_FOREACH(std::vector<Chipmunk::Vector2>& shape, shapes)
	{
		for(int i = 0; i < shape.size(); i+=2)
		{
			Chipmunk::Shapes::Shape* p = new Chipmunk::Shapes::Segment(_body, shape[i], shape[i+1], 1.0);
			std::cout << "  Segment: " << shape[i].x << "x" << shape[i].y << " - " << shape[i+1].x << "x" << shape[i+1].y << std::endl;
			p->elasticity(10.0);
			p->friction(1.0);
			_body.addStaticShape(p);
		}
	}
	// Bridge(state.space(), _body, cpv(-120, -180), _body, cpv(-20, -180), 10);
}

std::vector<std::vector<Chipmunk::Vector2> >
Map::load(PlayState& state, std::string filename)
{
	std::ifstream f(filename.c_str());
	if(!f.good())
		throw std::runtime_error("file not found");

	std::vector<std::vector<Chipmunk::Vector2> > shapes;
	std::vector<Chipmunk::Vector2> shape;

	while(f.good())
	{
		std::string line;
		getline(f, line);

		if(line.length() == 0)
		{
			if(shape.size() == 0)
				continue;

			std::cout << "New shape, " << shape.size() << " vertices" << std::endl;

			shapes.push_back(shape);

			std::vector<Chipmunk::Vector2>().swap(shape);
		}
		else
		{
			std::stringstream ss;
			ss << line;

			Chipmunk::Vector2 v;
			ss >> v.x;
			ss >> v.y;
			shape.push_back(v);
		}
	}
	
	return shapes;
}

void
Map::update()
{
	// std::cout << _body.position().x << "x" << _body.position().y << std::endl;
}

void
Map::draw()
{

}

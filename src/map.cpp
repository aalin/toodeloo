#include "common.hpp"
#include <fstream>
#include <sstream>

namespace Toodeloo
{
	Map::Map(Toodeloo::States::State& state, std::string filename)
		: _shapes(load(filename))
	{

		/*
		BOOST_FOREACH(std::vector<Toodeloo::Wrappers::Chipmunk::Vector2>& shape, shapes)
		{
			for(int i = 0; i < shape.size(); i+=2)
			{
				Toodeloo::Wrappers::Chipmunk::Shapes::Shape* p = new Toodeloo::Wrappers::Chipmunk::Shapes::Segment(_body, shape[i], shape[i+1], 1.0);
				std::cout << "  Segment: " << shape[i].x << "x" << shape[i].y << " - " << shape[i+1].x << "x" << shape[i+1].y << std::endl;
				p->elasticity(10.0);
				p->friction(1.0);
				_body.addStaticShape(p);
			}
		}
		*/
		// Bridge(state.space(), _body, cpv(-120, -180), _body, cpv(-20, -180), 10);
	}

	void
	Map::addToSpace(Wrappers::Chipmunk::Space& space)
	{
		if(_body.get())
			return; // Don't make it if there is one already.

		_body.reset(new Wrappers::Chipmunk::Body(space, INFINITY, INFINITY));

		std::vector<std::vector<Toodeloo::Wrappers::Chipmunk::Vector2> > shapes;

		BOOST_FOREACH(std::vector<Math::Vector2> shape, _shapes)
		{
			for(int i = 0; i < shape.size(); i+=2)
			{
				Math::Vector2 v1 = shape[i];
				Math::Vector2 v2 = shape[i+1];

				Toodeloo::Wrappers::Chipmunk::Shapes::Shape* p =
					new Toodeloo::Wrappers::Chipmunk::Shapes::Segment(*_body, cpv(v1.x, v1.y), cpv(v2.x, v2.y), 1.0);
				std::cout << "  Segment: " << shape[i].x << "x" << shape[i].y << " - " << shape[i+1].x << "x" << shape[i+1].y << std::endl;
				p->elasticity(10.0);
				p->friction(1.0);
				_body->addStaticShape(p);
			}
		}
	}

	std::vector<std::vector<Math::Vector2> >
	Map::load(std::string filename)
	{
		std::ifstream f(filename.c_str());
		if(!f.good())
			throw std::runtime_error("file not found");

		std::vector<std::vector<Math::Vector2> > shapes;
		std::vector<Math::Vector2> current_shape;

		while(f.good())
		{
			std::string line;
			getline(f, line);

			if(line.length() == 0)
			{
				if(current_shape.size() == 0)
					continue;

				std::cout << "New shape, " << current_shape.size() << " vertices" << std::endl;

				shapes.push_back(current_shape);

				std::vector<Math::Vector2>().swap(current_shape);
			}
			else
			{
				std::stringstream ss;
				ss << line;

				Math::Vector2 v;
				ss >> v.x;
				ss >> v.y;
				current_shape.push_back(v);
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
}

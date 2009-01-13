#include "common.hpp"
#include <fstream>
#include <sstream>

Map::Map(PlayState& state, std::string filename)
	: _body(state.space(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max())
{
	std::ifstream f(filename.c_str());
	if(!f.good())
		throw std::runtime_error("file not found");

	std::vector<Chipmunk::Vector2> current_vectors;

	while(f.good())
	{
		std::string line;
		getline(f, line);

		if(line.length() == 0)
		{
			if(current_vectors.size() == 0)
				continue;

			for(int i = 0; i < current_vectors.size(); i++)
			{
				int j = i < current_vectors.size() ? i : j;
				_body.addShape(new Chipmunk::Shapes::Segment(_body, current_vectors[i], current_vectors[j], 1.0));
			}
			// Clear the current_vectors-thing
			std::vector<Chipmunk::Vector2>().swap(current_vectors);
		}
		else
		{
			std::stringstream ss;
			ss << line;

			Chipmunk::Vector2 v;
			ss >> v.x;
			ss >> v.y;
			current_vectors.push_back(v);
		}
	}
}


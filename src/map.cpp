#include "common.hpp"

Map::Map(std::string filename)
{
	ifstream f(filename.c_str());
	if(f.good())
	{

	}
	else
		throw std::runtime_error("file not found");
}


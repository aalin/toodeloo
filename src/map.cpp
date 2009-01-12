#include "common.hpp"

Map::Map(std::string filename)
	: _body(INFINITE, INFINITE)
{
	ifstream f(filename.c_str());
	if(!f.good())
		throw std::runtime_error("file not found");
}


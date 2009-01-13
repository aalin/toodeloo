#include "common.hpp"

Map::Map(PlayState& state, std::string filename)
	: _body(state.space(), INFINITE, INFINITE)
{
	ifstream f(filename.c_str());
	if(!f.good())
		throw std::runtime_error("file not found");
}


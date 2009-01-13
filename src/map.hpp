#ifndef MAP_HPP
#define MAP_HPP

class PlayState;

class Map
{
	public:
		Map(PlayState& state, std::string filename);
	private:
		Chipmunk::Body _body;
};

#endif


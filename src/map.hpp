#ifndef MAP_HPP
#define MAP_HPP

class PlayState;

class Map
{
	public:
		Map(PlayState& state, std::string filename);
		void update();
		void draw();
	private:
		Chipmunk::Body _body;
		std::vector<std::vector<Chipmunk::Vector2> > load(PlayState& state, std::string filename);
};

#endif


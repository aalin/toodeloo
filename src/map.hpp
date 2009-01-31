#ifndef MAP_HPP
#define MAP_HPP

namespace Toodeloo
{
	namespace States
	{
		class Gameplay;
	}

	class Map
	{
		public:
			Map(Toodeloo::States::Gameplay& state, std::string filename);
			void update();
			void draw();
		private:
			Wrappers::Chipmunk::Body _body;
			std::vector<std::vector<Wrappers::Chipmunk::Vector2> > load(Toodeloo::States::Gameplay& state, std::string filename);
	};
}

#endif


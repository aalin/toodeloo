#ifndef MAP_HPP
#define MAP_HPP

namespace Toodeloo
{
	namespace States
	{
		class State;
	}

	class Map
	{
		public:
			Map(Toodeloo::States::State& state, std::string filename);
			void update();
			void draw();
		private:
			std::vector<std::vector<Math::Vector2> > load(std::string filename);
			std::vector<std::vector<Math::Vector2> > _shapes;
	};
}

#endif


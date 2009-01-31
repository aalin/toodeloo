#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

namespace Toodeloo
{
	class Heightmap
	{
		public:
			Heightmap(std::string filename);
			~Heightmap();
			void update();
			void draw();

		private:
			Toodeloo::Graphics::Image _heightmap;
			Toodeloo::Graphics::Geometry _geometry;
			std::vector<Toodeloo::Graphics::Vertex> at(int, int);

			float heightAt(int x, int y) const;
	};
}

#endif


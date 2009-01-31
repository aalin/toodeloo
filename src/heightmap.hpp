#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

class Heightmap
{
	public:
		Heightmap(std::string filename);
		~Heightmap();
		void update();
		void draw();

	private:
		Image _heightmap;
		Geometry _geometry;
		std::vector<Vertex> at(int, int);

		float heightAt(int x, int y) const;
};


#endif


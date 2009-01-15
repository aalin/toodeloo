#ifndef BRIDGE_HPP
#define BRIDGE_HPP

class Bridge
{
	public:
		Bridge(Chipmunk::Space& space, Chipmunk::Body& body1, Chipmunk::Vector2 pos1, Chipmunk::Body& body2, Chipmunk::Vector2 pos2, int steps);

	private:
		std::vector<Chipmunk::Body*> _bodies;
		Chipmunk::Space& _space;
};

#endif


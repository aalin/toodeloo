#ifndef BRIDGE_HPP
#define BRIDGE_HPP

namespace Toodeloo
{
	class Bridge
	{
		public:
			Bridge(Wrappers::Chipmunk::Space& space, Wrappers::Chipmunk::Body& body1, Wrappers::Chipmunk::Vector2 pos1, Wrappers::Chipmunk::Body& body2, Wrappers::Chipmunk::Vector2 pos2, int steps);

		private:
			std::vector<Wrappers::Chipmunk::Body*> _bodies;
			Wrappers::Chipmunk::Space& _space;
	};
}

#endif


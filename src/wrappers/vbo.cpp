#include "../common.hpp"

namespace Toodeloo
{
	namespace Wrappers
	{
		VBO::VBO()
		{
			glGenBuffers(1, &_buffer_id);
		}

		VBO::~VBO()
		{
			glDeleteBuffers(1, &_buffer_id);
		}

		void
			VBO::bind()
			{
				glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
			}
	}
}


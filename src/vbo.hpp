#ifndef VBO_HPP
#define VBO_HPP

class VBO
{
	public:
		enum Usage
		{
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};

		VBO();
		~VBO();
		void bind();

		template<typename T>
		void updateData(const std::vector<T>& data, Usage usage);

	private:
		GLuint _buffer_id;
};

template<typename T>
void
VBO::updateData(const std::vector<T>& data, VBO::Usage usage)
{
	bind();
	const GLsizeiptr byte_size = sizeof(T) * data.size();
	glBufferData(GL_ARRAY_BUFFER, byte_size, &data[0], usage);
}

#endif


#include "common.hpp"

Geometry::Geometry()
{ }

void
Geometry::pushVertex(const Vertex& vertex)
{
	_positions.push_back(vertex.position);
	_normals.push_back(vertex.normal);
	_texcoords.push_back(vertex.texcoord);
	_colors.push_back(vertex.color);
}

void
Geometry::draw()
{
	if(_positions.size() % 3 != 0)
		throw std::runtime_error("The number of vertices is not dividable by 3.");

	readyBuffers();
	drawBuffers();
}

void
Geometry::readyBuffers()
{
	if(!_position_buffer)
	{
		_position_buffer.reset(new VBO);
		_position_buffer->updateData(_positions, VBO::StaticDraw);
	}

	if(!_normal_buffer)
	{
		_normal_buffer.reset(new VBO);
		_normal_buffer->updateData(_normals, VBO::StaticDraw);
	}

	if(!_color_buffer)
	{
		_color_buffer.reset(new VBO);
		_color_buffer->updateData(_colors, VBO::StaticDraw);
	}

	if(!_texcoord_buffer)
	{
		_texcoord_buffer.reset(new VBO);
		_texcoord_buffer->updateData(_texcoords, VBO::StaticDraw);
	}
}

void
Geometry::drawBuffers()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	_position_buffer->bind();
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glEnableClientState(GL_COLOR_ARRAY);
	_color_buffer->bind();
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, 0);

	/*
	glEnableClientState(GL_NORMAL_ARRAY);
	_normal_buffer->bind();
	glNormalPointer(GL_FLOAT, 0, 0);

	glClientActiveTexture(GL_TEXTURE0);
	_texcoord_buffer->bind();
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	*/
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_positions.size()));

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glClientActiveTexture(GL_TEXTURE0);
}


#include "common.hpp"

Player::Player(PlayState& state)
	: _body(1.0, 1.0), _state(state)
{
	_body.position(cpv(-280, 240));

	_vertices = boost::assign::list_of
		(cpv(-15, -15))
		(cpv( 15, -15))
		(cpv( 15,  15))
		(cpv(-15,  15));

	_body.shapePolygon(_vertices, cpvzero);

//	_state.space().addBody(_body);
//	_state.space().addBody(shape);
}

Player::~Player()
{
}

void
Player::update()
{
}

void
Player::draw()
{
	using Chipmunk::Vector2;
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		BOOST_FOREACH(Vector2 &v, _vertices)
			glVertex2f(v.x, v.y);
	glEnd();
}


#include "common.hpp"

Player::Player(PlayState& state)
	: _body(state.space(), 1.0, 1.0), _state(state)
{
	_body.position(cpv(-280, 240));

	_vertices = boost::assign::list_of
		(cpv(-15, -15))
		(cpv( 15, -15))
		(cpv( 15,  15))
		(cpv(-15,  15));

	Chipmunk::Shapes::Polygon* poly = new Chipmunk::Shapes::Polygon(_body, _vertices, cpvzero);
	poly->elasticity(1.0);
	poly->friction(1.0);
	_body.addShape(poly);
}

Player::~Player()
{
}

void
Player::goLeft()
{
	Chipmunk::Vector2 v = _body.velocity();
	v.x -= 2.5;
	v.y -= 1;
	_body.velocity(v);
}

void
Player::goRight()
{
	Chipmunk::Vector2 v = _body.velocity();
	v.x += 2.5;
	v.y -= 1;
	_body.velocity(v);
}

void Player::jump()
{
	Chipmunk::Vector2 v = _body.velocity();
	v.y -= 5;
	_body.velocity(v);
}

void
Player::update()
{
}

void
Player::draw()
{
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		BOOST_FOREACH(Chipmunk::Vector2 &v, _vertices)
			glVertex2f(v.x + _body.position().x, v.y + _body.position().y);
	glEnd();
}


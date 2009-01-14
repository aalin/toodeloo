#include "common.hpp"

Player::Player(PlayState& state)
	:
		_body(state.space(), 50.0, 100.0),
		_state(state)
{
	_body.position(cpv(0, 0));

	Chipmunk::Shapes::Circle* circle = new Chipmunk::Shapes::Circle(_body, 5.0, cpvzero);
	circle->group(1);
	circle->elasticity(20.0);
	circle->friction(1.0);
	_body.addShape(circle);
	_body.addToSpace();
}

Player::~Player()
{
}

void
Player::goLeft()
{
	Chipmunk::Vector2 v = _body.velocity();
	v.x -= 5.0;
	v.y += 1.0;
	_body.velocity(v);
}

void
Player::goRight()
{
	Chipmunk::Vector2 v = _body.velocity();
	v.x += 5.0;
	v.y += 1.0;
	_body.velocity(v);
}

void Player::jump()
{
	Chipmunk::Vector2 v = _body.velocity();
	v.y += 15;
	_body.velocity(v);
}

void
Player::update()
{
}

void
Player::draw()
{
	/*
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		BOOST_FOREACH(Chipmunk::Vector2 &v, _vertices)
			glVertex2f(v.x + _body.position().x, v.y + _body.position().y);
	glEnd();*/
}


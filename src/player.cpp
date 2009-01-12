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

	Chipmunk::Shape shape(
		Chipmunk::Shape::polygon(_body, _vertices, cpvzero).elasticity(0.0).friction(0.0)
	);

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
}


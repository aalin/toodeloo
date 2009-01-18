#include "common.hpp"

Player::Player(PlayState& state)
		: _state(state)
{
	_bodies["bottom"] = new Chipmunk::Body(state.space(), 100.0, INFINITY);
	Chipmunk::Body* body = _bodies["bottom"];

	_bottom = new Chipmunk::Shapes::Circle(*body, 5.0, cpv(0.0, 13.0));
	_bottom->elasticity(0.1);
	_bottom->friction(1.0);
	body->addShape(_bottom);

	_bottom = new Chipmunk::Shapes::Circle(*body, 8.0, cpv(0.0, 0.0));
	_bottom->elasticity(0.0);
	_bottom->friction(1.0);
	body->addShape(_bottom);

	_bodies["center"] = new Chipmunk::Body(state.space(), 50.0, 50000000.0);
	body = _bodies["center"];

	Chipmunk::Shapes::Circle* shape = new Chipmunk::Shapes::Circle(*body, 5.0, cpv(0.0, 23.0));
	shape->elasticity(0.0);
	shape->friction(1.0);
	body->addShape(shape);

	_bodies["left_hand"] = new Chipmunk::Body(state.space(), 10.0, 50.0);
	body = _bodies["left_hand"];
	shape = new Chipmunk::Shapes::Circle(*body, 1.0, cpv(-40.0, 0.0));
	shape->elasticity(0.0);
	shape->friction(1.0);
	body->addShape(shape);

	_bodies["right_hand"] = new Chipmunk::Body(state.space(), 10.0, 50.0);
	body = _bodies["right_hand"];
	shape = new Chipmunk::Shapes::Circle(*body, 1.0, cpv(40.0, 0.0));
	shape->elasticity(0.0);
	shape->friction(1.0);
	body->addShape(shape);

	_bodies["head"] = new Chipmunk::Body(state.space(), 50.0, 5.0);
	body = _bodies["head"];
	shape = new Chipmunk::Shapes::Circle(*body, 5.0, cpv(0.0, 40.0));
	shape->elasticity(0.0);
	shape->friction(1.0);
	body->addShape(shape);

	state.space().addJoint(new Chipmunk::Joints::Slide(*_bodies["bottom"], *_bodies["center"], cpv(-1, 0), cpv(-1, 0), 0.0, 1.0));
	state.space().addJoint(new Chipmunk::Joints::Slide(*_bodies["bottom"], *_bodies["center"], cpv( 1, 0), cpv( 1, 0), 0.0, 1.0));
	//state.space().addJoint(new Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["left_hand"], cpv( 1, 0), cpv( 1, 0), 0.0, 2.0));
	//state.space().addJoint(new Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["right_hand"], cpv( 1, 0), cpv( 1, 0), 0.0, 2.0));
	state.space().addJoint(new Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["head"], cpv(-1, 0), cpv(-1, 0), 0.0, 1.0));
	state.space().addJoint(new Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["head"], cpv( 1, 0), cpv( 1, 0), 0.0, 1.0));

	typedef std::pair<std::string, Chipmunk::Body*> BodyPair;

	BOOST_FOREACH(BodyPair body_pair, _bodies)
	{
		std::cout << "Adding " << body_pair.first << std::endl;
		body_pair.second->addToSpace();
	}
}

Player::~Player()
{
}

void
Player::stop()
{
	_bottom->friction(1.0);
}

void
Player::goLeft()
{
	_bodies["center"]->applyImpulse(cpv(-2000.0, 1.0), cpvzero);
	_bottom->friction(0.0);
}

void
Player::goRight()
{
	_bodies["center"]->applyImpulse(cpv(2000.0, 1.0), cpvzero);
	_bottom->friction(0.0);
}

void Player::jump()
{
	Chipmunk::Vector2 v = _bodies["center"]->velocity();
	_bodies["bottom"]->applyImpulse(cpv(0.0, 5000.0), cpvzero);
}

void
Player::update()
{
}

void
Player::draw()
{
}


#include "common.hpp"

namespace Toodeloo
{
	Player::Player(States::Gameplay& state)
		: _state(state)
	{
		_bodies["bottom"] = new Toodeloo::Wrappers::Chipmunk::Body(state.space(), 100.0, INFINITY);
		Toodeloo::Wrappers::Chipmunk::Body* body = _bodies["bottom"];

		_bottom = new Toodeloo::Wrappers::Chipmunk::Shapes::Circle(*body, 5.0, cpv(0.0, 13.0));
		_bottom->elasticity(0.1);
		_bottom->friction(1.0);
		body->addShape(_bottom);

		_bottom = new Toodeloo::Wrappers::Chipmunk::Shapes::Circle(*body, 8.0, cpv(0.0, 0.0));
		_bottom->elasticity(0.0);
		_bottom->friction(1.0);
		body->addShape(_bottom);

		/*
		state.space().addJoint(new Toodeloo::Wrappers::Chipmunk::Joints::Slide(*_bodies["bottom"], *_bodies["center"], cpv(-1, 0), cpv(-1, 0), 0.0, 1.0));
		state.space().addJoint(new Toodeloo::Wrappers::Chipmunk::Joints::Slide(*_bodies["bottom"], *_bodies["center"], cpv( 1, 0), cpv( 1, 0), 0.0, 1.0));
		//state.space().addJoint(new Toodeloo::Wrappers::Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["left_hand"], cpv( 1, 0), cpv( 1, 0), 0.0, 2.0));
		//state.space().addJoint(new Toodeloo::Wrappers::Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["right_hand"], cpv( 1, 0), cpv( 1, 0), 0.0, 2.0));
		state.space().addJoint(new Toodeloo::Wrappers::Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["head"], cpv(-1, 0), cpv(-1, 0), 0.0, 1.0));
		state.space().addJoint(new Toodeloo::Wrappers::Chipmunk::Joints::Slide(*_bodies["center"], *_bodies["head"], cpv( 1, 0), cpv( 1, 0), 0.0, 1.0));

		*/

		typedef std::pair<std::string, Toodeloo::Wrappers::Chipmunk::Body*> BodyPair;

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
		Toodeloo::Wrappers::Chipmunk::Vector2 v = _bodies["center"]->velocity();
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
}


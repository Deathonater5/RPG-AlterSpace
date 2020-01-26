#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), 
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

// Accessors
const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}


// Functions
const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.0f && this->velocity.y == 0.0f)
			return true;
		break;

	case MOVING_UP:
		if (this->velocity.y < 0.0f)
			return true;
		break;

	case MOVING_LEFT:
		if (this->velocity.x < 0.0f)
			return true;
		break;

	case MOVING_DOWN:
		if (this->velocity.y > 0.0f)
			return true;
		break;

	case MOVING_RIGHT:
		if (this->velocity.x > 0.0f)
			return true;
		break;

	}

	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*Accelerating srite until it recahes max velocity*/

	// Acceleration 
	this->velocity.x += this->acceleration * dir_x;	
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	// Deceleration x
	if (this->velocity.x > 0.0f) // check for right
	{
		// Max velocity check right
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		// Deceleration right
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.0f)
			this->velocity.x = 0.0f;

	}
	else if (this->velocity.x < 0.0f) // check for left
	{
		// Ma velocity check left
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		// Deceleration left
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.0f)
			this->velocity.x = 0.0f;
	}

	// Deceleration y
	if (this->velocity.y > 0.0f) // check for up
	{
		// Max velocity check up
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		// Deceleration up
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.0f)
			this->velocity.y = 0.0f;

	}
	else if (this->velocity.y < 0.0f) // check for down
	{
		// Ma velocity check down
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		// Deceleration down
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.0f)
			this->velocity.y = 0.0f;
	}

	// Final move
	this->sprite.move(this->velocity * dt); // Uses velocity
}

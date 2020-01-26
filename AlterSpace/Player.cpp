#include "Player.h"

// Initializer functions
void Player::initVariables()
{
	this->direction = MOVING_DOWN;
}

void Player::initComponents()
{
	
}

// Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 16, 16, 32.0f, 48.0f);
	this->createMovementComponent(300.0f, 15.0f, 5.0f);
	this->createAnimationComponent(texture_sheet);

	// Idle Animation
	this->animationComponent->addAnimation("IDLE_UP", 3.0f, 0, 8, 0, 8, 64, 64);
	this->animationComponent->addAnimation("IDLE_LEFT", 3.0f, 0, 9, 0, 9, 64, 64);
	this->animationComponent->addAnimation("IDLE_DOWN", 3.0f, 0, 10, 0, 10, 64, 64);
	this->animationComponent->addAnimation("IDLE_RIGHT", 3.0f, 0, 11, 0, 11, 64, 64);

	// Walk Animation
	this->animationComponent->addAnimation("WALK_UP", 1.0f, 0, 8, 8, 8, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 1.0f, 0, 9, 8, 9, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 1.0f, 0, 10, 8, 10, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 1.0f, 0, 11, 8, 11, 64, 64);

	// Attack Animation
	this->animationComponent->addAnimation("ATTACK_UP", 1.5f, 0, 7, 5, 7, 64*3, 64*3);
	this->animationComponent->addAnimation("ATTACK_LEFT", 1.5f, 0, 8, 6, 8, 64 * 3, 64 * 3);
	this->animationComponent->addAnimation("ATTACK_DOWN", 1.5f, 0, 9, 6, 9, 64 * 3, 64 * 3);
	this->animationComponent->addAnimation("ATTACK_RIGHT", 1.5f, 0, 10, 6, 10, 64 * 3, 64 * 3);
}

Player::~Player()
{
}

// Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->getState(IDLE))
	{
		if (direction == MOVING_LEFT)
		{
			this->animationComponent->play("IDLE_LEFT", dt);
		}
		else if (direction == MOVING_RIGHT)
		{
			this->animationComponent->play("IDLE_RIGHT", dt);
		}
		else if (direction == MOVING_UP)
		{
			this->animationComponent->play("IDLE_UP", dt);
		}
		else if (direction == MOVING_DOWN)
		{
			this->animationComponent->play("IDLE_DOWN", dt);
		}
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->direction = MOVING_UP;
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
		
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->direction = MOVING_LEFT;
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->direction = MOVING_DOWN;
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->direction = MOVING_RIGHT;
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
		

	this->hitboxComponent->update();
}

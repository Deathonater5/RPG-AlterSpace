#pragma once

#include "Entity.h"

class Player :
	public Entity
{
private:
	// Variables
	unsigned short direction;

	// Initializer functions
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	// Functions 
	virtual void update(const float& dt);
}; 


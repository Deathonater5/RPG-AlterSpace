#pragma once

#include <iostream>
#include <string>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class AnimationComponent
{
private:
	class Animation
	{
	public:
		// Variables 
		sf::Sprite& sprite; 
		sf::Texture& textureSheet;
		float animationTimer; 
		float timer;
		int width;
		int height;

		sf::IntRect currentRect;
		sf::IntRect startRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
			int animation_timer, 
			int start_frame_x, int start_frame_y, int frames_x,  int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height)
		{
			this->timer = 0.0f;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);
			this->currentRect = this->startRect;

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		// Functions
		void play(const float& dt)
		{
			// Update timer
			this->timer += 10.0f * dt;
			if (this->timer >= this->animationTimer)
			{
				// Reset timer
				this->timer = 0.0f;

				// Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else // Reset
				{
					this->currentRect.left = this->startRect.left; 
				}
				this->sprite.setTextureRect(this->currentRect); 
			}
		}

		void play(const float& dt, float mod_percent)
		{
			// Update timer
			if (mod_percent < 0.5f)
				mod_percent = 0.5f;

			this->timer += mod_percent * 10.0f * dt;
			if (this->timer >= this->animationTimer)
			{
				// Reset timer
				this->timer = 0.0f;

				// Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else // Reset
				{
					this->currentRect.left = this->startRect.left;
				}
				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};


	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	// Functions
	void addAnimation(const std::string key,
		int animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	void play(const std::string key, const float& dt, const bool priority = false);
	void play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};


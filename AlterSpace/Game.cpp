#include "Game.h"

// Static functions

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.0f;

}

// Init functions
void Game::initWindow()
{
	/* Creates a SFML window using options from a window.ini file */

	std::ifstream ifs("Config/window.ini");

	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "AlterSpace";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode(); 
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0; 

	if (ifs.is_open()) 
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

void Game::initKeys()
{

	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key;
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();	
	

}

// Constructors and Destructors
Game::Game()
{
	this->initVariables(); 
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending Application" << std::endl;
}

void Game::updateDt()
{
	/*Update the dt variable for the time it took to update one frame*/
	this->dt = this->dtClock.restart().asSeconds();
}

// Functions
void Game::updateSFMLEvents()
{
	
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	// Render here
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}
	
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

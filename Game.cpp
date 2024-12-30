#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;

	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;

}
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Inferno Artica", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{ 
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

// Constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	/*
	* Description: Delete the poin    ter window to avoid memory leakage
	*/
	delete this->window;	
}

// Accessors
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen(); 
}

// Public functions
void Game::spawnEnemy()
{
	/*
	*	@return void
	*
	*	Description: Spawns enemies and sets their color and positions
	*	- Sets a random position
	*	- Sets a random color 
	*	- Adds enemy to the vector
	*/
	
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	// Spawn the enemy
	this->enemies.push_back(this->enemy);

	// Remove enemies at end of screen
}

void Game::pollEvents()
{
	// Event polling
	while (this->window->pollEvent(this->e))
	{
		switch (this->e.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->e.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
	* @ return void
	* 
	* Desc: Updates the mouse position:
	*	- Mouse position relative to the window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateEnemies()
{
	/*
	*	@return void
	* 
	*	Description: Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the maximum
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen // TODO
	*/

	// Updating the timer for enemy spawning
	if(this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->spawnEnemy();
			this->enemySpawnTimer += 1.f; 
	}

	// Move the enemies
	for (auto& e : this->enemies)
	{
		e.move(0.f, 1.f);
	}
	
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();
}

void Game::renderEnemies()
{
	// Rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
	* @return void
	* - clear old frme
	* - render objects
	* - display frame in window
	* 
	* Description: Renders the game objects.
	*/
	this->window->clear();

	// Draw game objects
	this->renderEnemies();

	this->window->display();
}

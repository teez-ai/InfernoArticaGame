#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

/*
* Class that acts a sthe Game Manager
*/
#ifndef GAME_H
#define GAME_H

class Game
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;	// will be a pointer (we will dynamically allocate it / delete later)
	sf::VideoMode videoMode;
	sf::Event e;

	// Mouse positions
	sf::Vector2i mousePosWindow;

	// Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Private functions
	void initVariables();
	void initWindow(); 
	void initEnemies();
public:
	// Constructor / Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool getWindowIsOpen() const;

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
};

#endif
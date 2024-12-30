#include <iostream>
#include <vector>
//#include "Game.h"
#include "Goblin.h"
#include "Platform.h"

int main()
{
    // Window settings
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platform Game", sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);

    // Player settings
    sf::RectangleShape player;
    player.setSize({ 50, 50 });
    player.setFillColor(sf::Color::Blue);
    player.setPosition(375, 500);

    sf::RectangleShape playerHealthBarBackground(sf::Vector2f(50, 5));
    playerHealthBarBackground.setFillColor(sf::Color::Red);

    sf::RectangleShape playerHealthBar(sf::Vector2f(50, 5));
    playerHealthBar.setFillColor(sf::Color::Green);
    int playerHealth = 100;

    sf::Vector2f velocity(0, 0);
    const float gravity = 0.5f;
    const float jumpStrength = -12.f;
    const float moveSpeed = 5.f;
    bool isJumping = false;

    // Platforms
    std::vector<Platform> platforms = {
        Platform(0, 550, 800, 50),
        Platform(300, 400, 200, 20),
        Platform(100, 300, 150, 20),
        Platform(500, 250, 200, 20)
    };

    // Goblins
    std::vector<Goblin> goblins = {
        Goblin(350, 500),
        Goblin(150, 450),
        Goblin(600, 200)
    };

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
            velocity.y = jumpStrength;
            isJumping = true;
        }

        // Update player health bar position
        playerHealthBarBackground.setPosition(player.getPosition().x, player.getPosition().y - 10);
        playerHealthBar.setPosition(player.getPosition().x, player.getPosition().y - 10);

        // Attack goblins
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            for (auto& goblin : goblins) {
                if (goblin.isAlive && player.getGlobalBounds().intersects(goblin.shape.getGlobalBounds())) {
                    goblin.health -= 10;
                    if (goblin.health <= 0) {
                        goblin.isAlive = false;
                    }
                }
            }
        }

        // Goblin movement and interaction
        for (auto& goblin : goblins) {
            if (goblin.isAlive) {
                goblin.move();

                // Update goblin health bar position
                goblin.healthBarBackground.setPosition(goblin.shape.getPosition().x, goblin.shape.getPosition().y - 10);
                goblin.healthBar.setPosition(goblin.shape.getPosition().x, goblin.shape.getPosition().y - 10);

                if (player.getGlobalBounds().intersects(goblin.shape.getGlobalBounds())) {
                    playerHealth -= 1; // Goblin damages the player on contact
                    if (playerHealth < 0) playerHealth = 0;
                    playerHealthBar.setSize(sf::Vector2f(playerHealth / 2.0f, 5));
                }
            }
        }

        // Apply gravity
        velocity.y += gravity;
        player.move(0, velocity.y);

        // Collision detection
        for (auto& platform : platforms) {
            if (player.getGlobalBounds().intersects(platform.shape.getGlobalBounds())) {
                if (velocity.y > 0) { // Falling
                    player.setPosition(player.getPosition().x, platform.shape.getPosition().y - player.getSize().y);
                    velocity.y = 0;
                    isJumping = false;
                }
            }
        }

        // Render
        window.clear(sf::Color::Black);

        // Draw platforms
        for (auto& platform : platforms) {
            window.draw(platform.shape);
        }

        // Draw goblins
        for (auto& goblin : goblins) {
            if (goblin.isAlive) {
                window.draw(goblin.shape);
                window.draw(goblin.healthBarBackground);
                goblin.healthBar.setSize(sf::Vector2f(goblin.health, 5));
                window.draw(goblin.healthBar);
            }
        }

        // Draw player
        window.draw(player);
        window.draw(playerHealthBarBackground);
        window.draw(playerHealthBar);

        window.display();
    }

    return 0;
}
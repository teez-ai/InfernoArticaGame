#pragma once
#ifndef GOBLIN_H
#define GOBLIN_H
#include <SFML/Graphics.hpp>

class Goblin {
public:
    sf::RectangleShape shape;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBackground;
    bool isAlive;
    float speed;
    bool movingRight;
    int health;


    Goblin(float x, float y) {
        shape.setPosition(x, y);
        shape.setSize({ 40, 40 });
        shape.setFillColor(sf::Color::Red);
        isAlive = true;
        speed = 2.0f;
        movingRight = true;
        health = 40;

        healthBarBackground.setSize(sf::Vector2f(40, 5));
        healthBarBackground.setFillColor(sf::Color::Red);
        healthBarBackground.setPosition(x, y - 10);

        healthBar.setSize(sf::Vector2f(40, 5));
        healthBar.setFillColor(sf::Color::Green);
        healthBar.setPosition(x, y - 10);
    }

    void move() {
        if (movingRight) {
            shape.move(speed, 0);
            if (shape.getPosition().x + shape.getSize().x >= 800) {
                movingRight = false;
            }
        }
        else {
            shape.move(-speed, 0);
            if (shape.getPosition().x <= 0) {
                movingRight = true;
            }
        }
    }
};


#endif
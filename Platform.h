#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>

class Platform {
public:
    sf::RectangleShape shape;

    Platform(float x, float y, float width, float height) {
        shape.setPosition(x, y);
        shape.setSize({ width, height });
        shape.setFillColor(sf::Color::Green);
    }
};
#endif
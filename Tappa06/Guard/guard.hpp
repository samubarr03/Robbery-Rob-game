#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "matrix.hpp"

class Guard {
public:
    Guard(Matrix& matrix);
    void setPosition(sf::Vector2i newPos);
    void setMap(Matrix& matrix);
    void setDirection();
    sf::Vector2i getPosition();
    void updatePosition();
private:
    Matrix& matrix;
    sf::Vector2i position;
};

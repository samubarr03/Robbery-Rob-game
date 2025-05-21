#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Utils/utils.hpp"
#include "../Matrix/matrix.hpp"

class Player {
public:
    Player(Matrix& matrix);
    bool canMoveTo(sf::Vector2i pos) const;
    void handleInput();
    void updatePosition();
    sf::Vector2i getPosition() const;
private:
    sf::Vector2i position;
    Matrix& matrix;
};
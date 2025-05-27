#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Utils/utils.hpp"
#include "../Matrix/matrix.hpp"

class Player {
public:
    Player(Matrix& matrix);
    void setMap(Matrix& newMatrix);
    void handleInput();
    void updatePosition();
    sf::Vector2i getPosition() const;
private:
    sf::Vector2i position;
    Matrix& matrix;
    std::vector<std::pair<sf::Vector2i, int>> previousTiles; 
};
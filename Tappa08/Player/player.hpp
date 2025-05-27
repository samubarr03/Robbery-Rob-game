#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Utils/utils.hpp"
#include "../Matrix/matrix.hpp"

class Player {
public:
    Player(Matrix& matrix);
    void setMap(Matrix& newMatrix);
    void handleInput(float dt);
    void updatePosition();
    sf::Vector2i getPosition();
    int getScore();
    bool isOnExit();
    void resetScore();
private:
    sf::Vector2i position;
    Matrix& matrix;
    std::vector<std::pair<sf::Vector2i, int>> previousTiles; 
    float speed = 1;
    float moveTimer = 0;
    int score = 0;
};
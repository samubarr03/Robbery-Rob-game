#include "player.hpp"

Player::Player() : position(cols/2, rows/2) {}

void Player::handleInput() {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && position.y > 0) {
        position.y--;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && position.y < rows - 2) {
        position.y++;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && position.x > 0) {
        position.x--;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && position.x < cols - 2) {
        position.x++;
    }
}

void Player::draw(sf::RenderWindow& window) {
    //creo la matrice del player
    for (int dy = 0; dy < 2; dy++){
        for (int dx = 0; dx < 2; dx++) {
            sf::RectangleShape partOfPlayer(sf::Vector2f(cellWidth, cellHeight));
            partOfPlayer.setFillColor(sf::Color::Green);
            partOfPlayer.setPosition((position.x + dx) * (cellWidth + space), (position.y + dy) * (cellHeight + space));
            window.draw(partOfPlayer);
        }
    }
}

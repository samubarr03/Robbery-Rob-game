#include "player.hpp"

Player::Player(Matrix& matrix) : matrix(matrix) {
    std::vector<std::vector<int>>& map = matrix.getMap();
    for (int y = 0; y < matrix.getRows(); y++) {
        for (int x = 0; x < matrix.getCols(); x++) {
            if (map[y][x] == TYPE_PLAYER) {
                position = sf::Vector2i(x, y);
                return;
            }
        }
    }
}

void Player::handleInput() {
    std::vector<std::vector<int>>& map = matrix.getMap();
    sf::Vector2i newPos = position;
    
if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && position.y > 0) {
        newPos.y--;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && position.y < matrix.getRows() - 2) {
        newPos.y++;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) && position.x > 0) {
        newPos.x--;
    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) && position.x < matrix.getCols() - 2) {
        newPos.x++;
    }

    //controllo che la nuova posizione sia il player o il terreno calpestabile
    
    if (
        (map[newPos.y][newPos.x] == TYPE_FLOOR  || map[newPos.y][newPos.x] == TYPE_PLAYER) &&
        (map[newPos.y][newPos.x + 1] == TYPE_FLOOR || map[newPos.y][newPos.x + 1] == TYPE_PLAYER)&&
        (map[newPos.y + 1][newPos.x] == TYPE_FLOOR || map[newPos.y + 1][newPos.x] == TYPE_PLAYER)&&
        (map[newPos.y + 1][newPos.x + 1] == TYPE_FLOOR || map[newPos.y + 1][newPos.x + 1] == TYPE_PLAYER)
        ) {
            position = newPos;
    }
}

void Player::updatePosition() {
    std::vector<std::vector<int>>& map = matrix.getMap(); 
    for (int y = 0; y < matrix.getRows(); y++) {
        for (int x = 0; x < matrix.getCols(); x++) {
            if (map[y][x] == TYPE_PLAYER)
                map[y][x] = TYPE_FLOOR;
        }
    }
    
    //disegno il player nella matrice
    int px = position.x;
    int py = position.y;
    if (px + 1 < matrix.getCols() && py + 1 < matrix.getRows()) {
        map[py][px]     = TYPE_PLAYER;
        map[py][px + 1] = TYPE_PLAYER;
        map[py + 1][px] = TYPE_PLAYER;
        map[py + 1][px + 1] = TYPE_PLAYER;
    }

    matrix.setMap(map);
}

sf::Vector2i Player::getPosition() const {
    return position;
}
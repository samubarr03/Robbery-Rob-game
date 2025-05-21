#include "player.hpp"

Player::Player(Matrix &matrix) : matrix(matrix)
{
    std::vector<std::vector<int>> &map = matrix.getMap();
    for (int x = 0; x < matrix.getCols(); x++)
    {
        for (int y = 0; y < matrix.getRows(); y++)
        {
            if (map[x][y] == TYPE_PLAYER)
            {
                position = sf::Vector2i(x, y);
                return;
            }
        }
    }
}

void Player::handleInput()
{
    std::vector<std::vector<int>> &map = matrix.getMap();
    sf::Vector2i newPos = position;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)))
    {
        newPos.y--;
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)))
    {
        newPos.y++;
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
    {
        newPos.x--;
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
    {
        newPos.x++;
    }

    // controllo che la nuova posizione sia il player o il terreno calpestabile

    if ((map[newPos.x][newPos.y] == TYPE_FLOOR || map[newPos.x][newPos.y] == TYPE_PLAYER) &&
        (map[newPos.x][newPos.y + 1] == TYPE_FLOOR || map[newPos.x][newPos.y + 1] == TYPE_PLAYER) &&
        (map[newPos.x + 1][newPos.y] == TYPE_FLOOR || map[newPos.x + 1][newPos.y] == TYPE_PLAYER) &&
        (map[newPos.x + 1][newPos.y + 1] == TYPE_FLOOR || map[newPos.x + 1][newPos.y + 1] == TYPE_PLAYER))
    {
        position = newPos;
    }
}

void Player::updatePosition()
{
    std::vector<std::vector<int>> &map = matrix.getMap();

    for (int x = 0; x < matrix.getCols(); x++)
    {
        for (int y = 0; y < matrix.getRows(); y++)
        {
            if (map[x][y] == TYPE_PLAYER)
                map[x][y] = TYPE_FLOOR;
        }
    }

    // disegno il player nella matrice
    int px = position.x;
    int py = position.y;
    if (px + 1 < matrix.getCols() && py + 1 < matrix.getRows())
    {
        map[px][py] = TYPE_PLAYER;
        map[px][py + 1] = TYPE_PLAYER;
        map[px + 1][py] = TYPE_PLAYER;
        map[px + 1][py + 1] = TYPE_PLAYER;
    }

    matrix.setMap(map);
}

sf::Vector2i Player::getPosition() const
{
    return position;
}
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

void Player::setMap(Matrix &newMatrix)
{
    matrix = newMatrix;
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
void Player::handleInput(float dt)
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

    if (newPos.x < 0 || newPos.y < 0 ||
        newPos.x + 1 >= static_cast<int>(map.size()) ||
        newPos.y + 1 >= static_cast<int>(map[0].size()))
    {
        return;
    }

    if (newPos != position)
    {
        moveTimer += dt;
        if (moveTimer >= 0.1 / speed)
        {
            moveTimer = 0;
            // controllo che la nuova posizione sia il player o il terreno calpestabile
            auto isWalkable = [&](int x, int y)
            {
                int type = map[x][y];
                return type == TYPE_FLOOR || type == TYPE_PLAYER || type == TYPE_GUARD_ROUTE || type == TYPE_LOOT || type == TYPE_EXIT;
            };

            if (isWalkable(newPos.x, newPos.y) &&
                isWalkable(newPos.x, newPos.y + 1) &&
                isWalkable(newPos.x + 1, newPos.y) &&
                isWalkable(newPos.x + 1, newPos.y + 1))
            {
                position = newPos;
            }
        
        }
    }
    else
    {
        moveTimer = 0;
    }
}

void Player::updatePosition()
{
    std::vector<std::vector<int>> &map = matrix.getMap();

    for (int x = 0; x < matrix.getCols(); ++x)
        for (int y = 0; y < matrix.getRows(); ++y)
            if (map[x][y] == TYPE_PLAYER)
                map[x][y] = TYPE_FLOOR;

    for (const auto &[pos, originalType] : previousTiles)
    {
        if (pos.x >= 0 && pos.y >= 0 &&
            pos.x < matrix.getCols() && pos.y < matrix.getRows() && originalType != TYPE_LOOT)
        {
            map[pos.x][pos.y] = originalType;
        }
    }
    previousTiles.clear();
    // disegno il player nella matrice
    int px = position.x;
    int py = position.y;
    if (px + 1 < matrix.getCols() && py + 1 < matrix.getRows())
    {

        previousTiles.push_back({sf::Vector2i(px, py), map[px][py]});
        previousTiles.push_back({sf::Vector2i(px, py + 1), map[px][py + 1]});
        previousTiles.push_back({sf::Vector2i(px + 1, py), map[px + 1][py]});
        previousTiles.push_back({sf::Vector2i(px + 1, py + 1), map[px + 1][py + 1]});

        map[px][py] = TYPE_PLAYER;
        map[px][py + 1] = TYPE_PLAYER;
        map[px + 1][py] = TYPE_PLAYER;
        map[px + 1][py + 1] = TYPE_PLAYER;
    }

    for (const auto &[pos, originalType] : previousTiles)
    {
        if (originalType == TYPE_LOOT)
        {
           score++;
        }
    }
}

sf::Vector2i Player::getPosition()
{
    return position;
}

bool Player::isOnExit()
{
    for (const auto &[pos, originalType] : previousTiles)
    {
        if (originalType == TYPE_EXIT && score >=matrix.getTotalScore())
        {
            return true;
        }
    }
    return false;
}




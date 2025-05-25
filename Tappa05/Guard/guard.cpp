#include "guard.hpp"

Guard::Guard(Matrix &matrix) : matrix(matrix){}

void Guard::setPosition(sf::Vector2i newPos)
{
    position = newPos;
}

void Guard::setMap(Matrix& newMatrix)
{
    matrix = newMatrix;
}

sf::Vector2i Guard::getPosition()
{
    return position;
}

//funzione che aggiorna la poszione della guardia randomicamente
void Guard::setDirection()
{
    std::vector<std::vector<int>> &map = matrix.getMap();
    sf::Vector2i newPos = position;

    // Genera una direzione casuale (su, giù, sinistra, destra)
    int direction = rand() % 4;

    switch (direction)
    {
        case 0:
            newPos.y--;
            break;
        case 1:
            newPos.y++;
            break;
        case 2:
            newPos.x--;
            break;
        case 3:
            newPos.x++;
            break;
    }

    if(newPos.x < 0 || newPos.y < 0 ||
        newPos.x + 1 >= static_cast<int>(map.size()) ||   
        newPos.y + 1 >= static_cast<int>(map[0].size())){}

    // controllo che la nuova posizione sia il player o il terreno calpestabile
    if ((map[newPos.x][newPos.y] == TYPE_FLOOR || map[newPos.x][newPos.y] == TYPE_GUARD) &&
        (map[newPos.x][newPos.y + 1] == TYPE_FLOOR || map[newPos.x][newPos.y + 1] == TYPE_GUARD) &&
        (map[newPos.x + 1][newPos.y] == TYPE_FLOOR || map[newPos.x + 1][newPos.y] == TYPE_GUARD) &&
        (map[newPos.x + 1][newPos.y + 1] == TYPE_FLOOR || map[newPos.x + 1][newPos.y + 1] == TYPE_GUARD))
    {
        position = newPos;
    }
}

void Guard::updatePosition()
{
    std::vector<std::vector<int>> &map = matrix.getMap();

    for (int x = 0; x < matrix.getCols(); x++)
    {
        for (int y = 0; y < matrix.getRows(); y++)
        {
            if (map[x][y] == TYPE_GUARD)
                map[x][y] = TYPE_FLOOR;
        }
    }
    // disegno il player nella matrice
    int px = position.x;
    int py = position.y;
    if (px + 1 < matrix.getCols() && py + 1 < matrix.getRows())
    {
        map[px][py] = TYPE_GUARD;
        map[px][py + 1] = TYPE_GUARD;
        map[px + 1][py] = TYPE_GUARD;
        map[px + 1][py + 1] = TYPE_GUARD;
    }

    matrix.setMap(map);
}


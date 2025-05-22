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



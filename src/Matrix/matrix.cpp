#include "matrix.hpp"

Matrix::Matrix() {
    //creo la matrice
    map = {
        {1, 1, 0, 0,0,0,0,0,0,0,0,0,0},
        {1, 1, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
        {0, 0, 0, 0,0,0,0,0,0,0,0,0,0},
    };   

    rows = map.size();
    cols = map[0].size();
    cellWidth = sf::VideoMode::getDesktopMode().width / cols;
    cellHeight = sf::VideoMode::getDesktopMode().height / rows;
    space = 2;
}

std::vector<std::vector<int>>& Matrix::getMap() {
    return map;
}

void Matrix::setMap(std::vector<std::vector<int>> newMap) {
    map = newMap;
}

int Matrix::getRows() const{
    return rows;
}

int Matrix::getCols() const{
    return cols;
}

void Matrix::draw(sf::RenderWindow& window) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
           sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            cell.setPosition(y * (cellWidth + space), x * (cellHeight + space));
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            switch (map[x][y]) {
                case TYPE_FLOOR:
                    cell.setFillColor(sf::Color::White);
                    break;
                case TYPE_PLAYER: 
                    cell.setFillColor(sf::Color::Green);
                    break;
                case TYPE_WALL:
                    cell.setFillColor(sf::Color::Blue);
                    break;
            }

            window.draw(cell);
        }
    }
}


#include "matrix.hpp"

Matrix::Matrix() {
    //creo la matrice
    grid.resize(rows, std::vector<sf::RectangleShape>(cols));

    //setto le proprietà di ogni cella
    for (int x = 0; x < rows; x++){
        for (int y = 0; y < cols; y++) {
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            cell.setFillColor(sf::Color::White);
            cell.setOutlineColor(sf::Color::Black);
            cell.setPosition((cellWidth + space) * x, (cellHeight + space) * y);
            grid[x][y] = cell;
        }
    }   
}

void Matrix::draw(sf::RenderWindow& window) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            window.draw(grid[x][y]);
        }
    }
}


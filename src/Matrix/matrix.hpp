#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/utils.hpp"

class Matrix {
public:
    Matrix();
    void draw(sf::RenderWindow& window);
    void setMap(std::vector<std::vector<int>> newMap);
    std::vector<std::vector<int>>& getMap();
    int getRows() const;
    int getCols() const;
private:
    std::vector<std::vector<int>> map;
    int rows;
    int cols;
    float cellWidth;
    float cellHeight;
    int space;
};

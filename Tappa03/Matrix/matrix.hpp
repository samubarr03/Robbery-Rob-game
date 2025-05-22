#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

class Matrix {
public:
    Matrix();
    void draw(sf::RenderWindow& window);
    void loadMapFromFile(const std::string &filename);
    void setMap(std::vector<std::vector<int>> newMap);
    std::vector<std::vector<int>>& getMap();
    int getRows() const;
    int getCols() const;
private:
    sf::Texture floorTexture;
    sf::Texture wallTexture;
    sf::Texture furnitureTexture;
    sf::Texture playerTexture;
    sf::Texture guardTexture;
    std::vector<std::vector<int>> map;
    int rows;
    int cols;
    float cellWidth;
    float cellHeight;
    int space;
};

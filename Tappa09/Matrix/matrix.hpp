#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

struct Texture {
    int type;
    std::string name;
    int width;
    int height;
    sf::Texture texture;
};

class Matrix {
public:
    Matrix();
    void loadTexture(int type, const std::string& name, int w, int h);
    void draw(sf::RenderWindow& window, bool isGameMode);
    void createEmptyMatrix();
    void drawItemInPosition(sf::Vector2f mousePos, int selectedTool);
    void loadMapFromFile(const std::string &filename);
    void setMap(std::vector<std::vector<int>> newMap);
    std::vector<std::vector<int>>& getMap();
    int getRows() const;
    int getCols() const;
    bool isMapLoaded();
    int getTotalScore();
    void calculateTotalScore();
    std::map<int, Texture> getFurnitureTextureMap();;
private:
    std::map<int, Texture> textureMap;
    std::vector<std::vector<int>> map;
    int rows;
    int cols;
    float cellWidth;
    float cellHeight;
    int space;
    static const int GRID_SIZE = 64;
    bool mapLoaded;

    int CELL_SIZE;
    int GRID_OFFSET_X;
    int GRID_OFFSET_Y;

    bool isDrawingWall;

    int posxWall;
    int posyWall;

    int score;


};

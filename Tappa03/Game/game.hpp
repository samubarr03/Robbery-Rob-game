#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../Matrix/matrix.hpp"
#include "../Player/player.hpp"
#include "../Guard/guard.hpp"
#include "../Utils/utils.hpp"

class Game {
public:
    Game();
    void init();
private:
    void handleMouseClick(sf::Vector2f mousePos);
    void drawGridToCreateMap();

    static const int GRID_SIZE = 64;

    sf::RenderWindow window;
    Matrix matrix;
    Player player;
    std::vector<Guard> guards;

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Bottoni principali
    sf::RectangleShape playButton;
    sf::RectangleShape selectMapButton;
    sf::RectangleShape drawMapButton;
    sf::Font font;
    sf::Text playText;
    sf::Text selectMapText;
    sf::Text drawMapText;

    // Griglia disegna mappa
    std::vector<std::vector<int>> createMap;

    //Modalità gioco o disegna mappa
    bool drawMatrix;
    bool drawMap;

    // Bottoni disegna mappa
    sf::RectangleShape wallButton;
    sf::RectangleShape furnitureButton;
    sf::RectangleShape playerButton;
    sf::RectangleShape guardButton;
    sf::RectangleShape saveMapButton;

    sf::Text wallButtonText;
    sf::Text furnitureButtonText;
    sf::Text playerButtonText;
    sf::Text guardButtonText;
    sf::Text saveMapButtonText;

    //tool per la creazione della mappa
    int CELL_SIZE;
    int GRID_OFFSET_X;
    int GRID_OFFSET_Y;

    int selectedTool;
};

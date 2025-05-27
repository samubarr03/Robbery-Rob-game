#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../Matrix/matrix.hpp"
#include "../Player/player.hpp"
#include "../Guard/guard.hpp"
#include "../Utils/utils.hpp"

struct FurnitureItem {
    int id;
    std::string name;
    sf::RectangleShape buttonShape;
    sf::Text label;

    FurnitureItem(int id, const std::string& name, const sf::Font& font)
        : id(id), name(name), label(font, name, 24)
    {
        buttonShape.setSize({150, 50});
        buttonShape.setFillColor(sf::Color(255, 200, 0));
    }
};




class Game {
public:
    Game();
    void init();
private:
    void handleMouseClick(sf::Vector2f mousePos);
    std::string askMapName(sf::RenderWindow& window);
    std::string selectMapToPlay(sf::RenderWindow &window);
    std::vector<FurnitureItem> furnitureItems;

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
    bool gameMode;
    bool drawMap;

    // Bottoni disegna mappa
    sf::RectangleShape wallButton;
    sf::RectangleShape playerButton;
    sf::RectangleShape guardButton;
    sf::RectangleShape saveMapButton;
    sf::RectangleShape floorButton;
    sf::RectangleShape importMapButton;
    sf::RectangleShape guardRouteButton;
    sf::RectangleShape lootButton;
    sf::RectangleShape exitButton;
    
    sf::Text wallButtonText;
    sf::Text playerButtonText;
    sf::Text guardButtonText;
    sf::Text saveMapButtonText;
    sf::Text floorButtonText;
    sf::Text importMapButtonText;
    sf::Text guardRouteButtonText;
    sf::Text lootButtonText;
    sf::Text exitButtonText;
    

    sf::Texture winTexture, gameOverTexture;
    sf::Sprite winSprite, gameOverSprite;
    bool showWin = false;
    bool showGameOver = false;


    //tool per la creazione della mappa
    int CELL_SIZE;
    int GRID_OFFSET_X;
    int GRID_OFFSET_Y;

    int selectedTool;

    sf::Clock endClock;
    bool endGame = false;
    bool endScreenStarted = false;
};

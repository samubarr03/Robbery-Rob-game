#include <SFML/Graphics.hpp>
#include "../Utils/utils.hpp"

class Player {
public:
    Player();
    void handleInput();
    void draw(sf::RenderWindow& window);
private:
    sf::Vector2i position; // In tile coordinates
};

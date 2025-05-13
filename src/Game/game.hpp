#include <SFML/Graphics.hpp>
#include "../Matrix/matrix.hpp"
#include "../Player/player.hpp"
#include "../Utils/utils.hpp"

class Game {
public:
    Game();
    void init();
private:
    sf::RenderWindow window;
    Matrix matrix;
    Player player;
};


#include <SFML/Graphics.hpp>
#include "../Utils/utils.hpp"

class Matrix {
public:
    Matrix();
    void draw(sf::RenderWindow& window);
private:
    std::vector<std::vector<sf::RectangleShape>> grid;
};

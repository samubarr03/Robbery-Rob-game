#include <SFML/Graphics.hpp>

int main() {
    const int rows = 100;
    const int cols = 100;
    const int cellSize = 10; 
    const int space = 2;

    const int windowWidth = 800;
    const int windowHeight = 600;

    // Creo la finestra di gioco
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Robbery Rob");

    while (window.isOpen()) {
        sf::Event event;

        //listener chiusura finestra
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Disegno la matrice
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; col++) {
                // Creo una cella e la posiziono
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setFillColor(sf::Color::White); 
                cell.setPosition(col * (cellSize + space), row * (cellSize + space));  
                window.draw(cell);
            }
        }

        window.display();
    }

    // Chiudo la finestra
    window.close();
    return 0;
}
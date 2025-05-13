#include <game.hpp>

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Robbery Rob") {}

void Game::init() {
    //creo il gioco e in loop ridisegno tutta la matrice
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        player.handleInput();
        matrix.draw(window);
        player.draw(window);
        window.display();
    }
}

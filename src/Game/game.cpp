#include <game.hpp>

Game::Game() 
    :window(sf::VideoMode( 
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height),
        "Robbery Rob"),
    matrix(),
    player(matrix)
{}

void Game::init() {
    //creo il gioco e in loop ridisegno tutta la matrice
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        player.handleInput();
        player.updatePosition();

        matrix.draw(window);
        window.display();
    }
}

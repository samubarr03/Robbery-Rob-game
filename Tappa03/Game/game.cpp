#include "game.hpp"

Game::Game()
    : window(sf::VideoMode::getFullscreenModes().at(0), "Robbery Rob"),
      matrix(),
      player(matrix),
      drawMatrix(false),
      drawMap(false),
      selectedTool(0),
      playText(font, "", 24),
      selectMapText(font, "", 24),
      drawMapText(font, "", 24),
      wallButtonText(font, "", 24),
      furnitureButtonText(font, "", 24),
      playerButtonText(font, "", 24),
      guardButtonText(font, "", 24),
      saveMapButtonText(font, "", 24),
      backgroundSprite(backgroundTexture)
{
    // Carico background
    if (!backgroundTexture.loadFromFile("resources/image1.png"))
    {
        std::cerr << "Errore nel caricamento di image1.png\n";
    }

    if (!font.openFromFile("resources/arial.ttf"))
    {
        std::cerr << "Errore caricamento font\n";
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y))));

    // Bottoni home
    playButton.setSize({250, 100});
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition({sf::VideoMode::getDesktopMode().size.x / 2 - playButton.getSize().x / 2,
                            (sf::VideoMode::getDesktopMode().size.y * 2) / 3});

    selectMapButton.setSize({250, 100});
    selectMapButton.setFillColor(sf::Color::Blue);
    selectMapButton.setPosition({(sf::VideoMode::getDesktopMode().size.x / 2 - selectMapButton.getSize().x / 2) +300,
                                 (sf::VideoMode::getDesktopMode().size.y * 2) / 3});

    drawMapButton.setSize({250, 100});
    drawMapButton.setFillColor(sf::Color::Blue);
    drawMapButton.setPosition({sf::VideoMode::getDesktopMode().size.x / 2 - drawMapButton.getSize().x / 2,
                               (sf::VideoMode::getDesktopMode().size.y * 2) / 3 + 120});

    // Testi home
    playText.setString("Gioca");
    playText.setFillColor(sf::Color::Black);
    playText.setPosition({playButton.getPosition().x + 50, playButton.getPosition().y + 30});

    selectMapText.setString("Seleziona Mappa");
    selectMapText.setFillColor(sf::Color::White);
    selectMapText.setPosition({selectMapButton.getPosition().x + 20, selectMapButton.getPosition().y + 30});

    drawMapText.setString("Disegna Mappa");
    drawMapText.setFillColor(sf::Color::White);
    drawMapText.setPosition({drawMapButton.getPosition().x + 20, drawMapButton.getPosition().y + 30});

    // Bottoni disegna mappa
    wallButton.setSize({150, 50});
    wallButton.setFillColor(sf::Color::Red);
    wallButton.setPosition({20, 160});

    furnitureButton.setSize({150, 50});
    furnitureButton.setFillColor(sf::Color(255, 165, 0));
    furnitureButton.setPosition({20, 230});

    playerButton.setSize({150, 50});
    playerButton.setFillColor(sf::Color::Green);
    playerButton.setPosition({20, 300});

    guardButton.setSize({150, 50});
    guardButton.setFillColor(sf::Color::Magenta);
    guardButton.setPosition({20, 370});

    saveMapButton.setSize({150, 50});
    saveMapButton.setFillColor(sf::Color::Cyan);
    saveMapButton.setPosition({20, 440});

    // Testi bottoni disegna mappa
    wallButtonText.setString("Muro");
    wallButtonText.setFillColor(sf::Color::White);
    wallButtonText.setPosition({50, 170});

    furnitureButtonText.setString("Arredamento");
    furnitureButtonText.setFillColor(sf::Color::White);
    furnitureButtonText.setPosition({30, 240});

    playerButtonText.setString("Player");
    playerButtonText.setFillColor(sf::Color::White);
    playerButtonText.setPosition({50, 310});

    guardButtonText.setString("Guardia");
    guardButtonText.setFillColor(sf::Color::White);
    guardButtonText.setPosition({50, 380});

    saveMapButtonText.setString("Salva Mappa");
    saveMapButtonText.setFillColor(sf::Color::White);
    saveMapButtonText.setPosition({30, 450});
}

void Game::handleMouseClick(sf::Vector2f mousePos)
{
    if (!drawMap)
    {
        // Modalità gioco
        if (playButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Modalità gioco selezionata";

            drawMatrix = true;
            drawMap = false;

            // Aggiorno il player e la mappa
            player.handleInput();
            player.updatePosition();

            //scansiono la mappa e ogni 2 celle (perchè ogni guardia è grande 4 celle) creo una guardia con la sua posizione
            for(int x = 0; x < matrix.getCols(); x += 2)
            {
                for (int y = 0; y < matrix.getRows(); y += 2)
                {
                    if (matrix.getMap()[x][y] == TYPE_GUARD)
                    {
                        std::cout << "Guardia trovata in posizione: " << x << ", " << y << "\n";
                        guards.push_back(Guard(matrix));
                        guards.back().setPosition(sf::Vector2i(x, y));
                    }
                }
            }
        }
        // Modalità selezopna  mappa
        else if (selectMapButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Modalità seleziona mappa selezionata";

            auto file = pfd::open_file("Seleziona una mappa", "../resources", {"Mappe", "*.txt"}).result();

            if (file.empty())
            {
                std::cout << "Nessun file selezionato";
                return;
            }
            matrix.loadMapFromFile(file[0]);
        }

        // Modalità disegna mappa
        else if (drawMapButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Modalità disegna mappa selezionata";
            drawMap = true;
            drawMatrix = false;

            createMap.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
        }
    }
    else
    {
        if (wallButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_WALL;
            std::cout << "Muro selezionato";
        }
        else if (furnitureButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_FURNITURE;
            std::cout << "Arredamento selezionato";
        }
        else if (playerButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_PLAYER;
            std::cout << "Player selezionato";
        }
        else if (guardButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_GUARD;
            std::cout << ("Guardia selezionata");
        }
        else if (saveMapButton.getGlobalBounds().contains(mousePos))
{
    std::cout << "Salva mappa\n";

    auto result = pfd::save_file("Salva la mappa", "../resources", {"Mappe", "*.txt"}).result();

    if (result.empty())
    {
        std::cout << "Nessun file selezionato\n";
        return;
    }

    std::ofstream file(result);
    if (file.is_open())
    {
        for (const std::vector<int> &row : createMap)
        {
            for (int cell : row)
            {
                file << cell;
            }
            file << "\n";
        }
        file.close();
        std::cout << "Mappa salvata con successo\n";
    }
    else
    {
        std::cerr << "Errore durante il salvataggio della mappa\n";
    }
}
        else
        {
            // Clic su una cella o movimeto con il mouse cliccato
            int cellX = (mousePos.x - GRID_OFFSET_X) / CELL_SIZE;
            int cellY = (mousePos.y - GRID_OFFSET_Y) / CELL_SIZE;

            if (cellX >= 0 && cellX < GRID_SIZE && cellY >= 0 && cellY < GRID_SIZE)
            {
                switch (selectedTool)
                {
                case TYPE_WALL:
                    createMap[cellY][cellX] = TYPE_WALL;
                    break;

                case TYPE_FURNITURE:
                    createMap[cellY][cellX] = TYPE_FURNITURE;
                    break;

                case TYPE_PLAYER:
                    if (cellX + 1 < GRID_SIZE && cellY + 1 < GRID_SIZE)
                    {
                        for (int dy = 0; dy < 2; dy++)
                            for (int dx = 0; dx < 2; dx++)
                                createMap[cellY + dy][cellX + dx] = TYPE_PLAYER;
                    }
                    break;

                case TYPE_GUARD:
                    if (cellX + 1 < GRID_SIZE && cellY + 1 < GRID_SIZE)
                    {
                        for (int dy = 0; dy < 2; dy++)
                            for (int dx = 0; dx < 2; dx++)
                                createMap[cellY + dy][cellX + dx] = TYPE_GUARD;
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }
}

void Game::drawGridToCreateMap()
{
    /* calcolo la posizione dela griglia:
    LARGHEZZA: da 1/3 sinistra a 10 px meno della fine dello schermo
    ALTEZZA: da 10 px sotto il limite a 10 px sopra il minimo
    */
    GRID_OFFSET_X = sf::VideoMode::getDesktopMode().size.x / 3;
    GRID_OFFSET_Y = 10;

    // calcolo il cell size
    CELL_SIZE = (sf::VideoMode::getDesktopMode().size.x - GRID_OFFSET_X - 10) / GRID_SIZE;
    // Disegno la griglia
    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition({x * CELL_SIZE + GRID_OFFSET_X,
                              y * CELL_SIZE + GRID_OFFSET_Y});
            cell.setOutlineThickness(1);
            // a seconda di che numero c'è nella matrice disegno il colore del colore del bottone
            switch (createMap[y][x])
            {
            case TYPE_WALL:
                cell.setFillColor(sf::Color::Blue);
                break;
            case TYPE_FURNITURE:
                cell.setFillColor(sf::Color::Red);
                break;
            case TYPE_PLAYER:
                cell.setFillColor(sf::Color::Green);
                break;
            case TYPE_GUARD:
                cell.setFillColor(sf::Color::Magenta);
                break;
            default:
                cell.setFillColor(sf::Color::White);
                break;
            }
            cell.setOutlineColor(sf::Color(200, 200, 200)); // grigio chiaro
            window.draw(cell);
        }
    }
}

void Game::init()
{

    while (window.isOpen())
    {
        while (auto eventOpt = window.pollEvent())
        {
            const sf::Event &event = *eventOpt;

            if (event.is<sf::Event::Closed>())
            {
                window.close();
                break;
            }

            if (const auto *mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    handleMouseClick(mousePos);
                }
            }
            else if (const auto *mouseMoved = event.getIf<sf::Event::MouseMoved>())
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    handleMouseClick(mousePos);
                }
            }
            else if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    drawMap = false;
                    drawMatrix = false;
                    std::cout << "Tornato alla schermata principale\n";
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(backgroundSprite);

        if (!drawMap)
        {
            window.draw(playButton);
            window.draw(playText);
            window.draw(selectMapButton);
            window.draw(selectMapText);
            window.draw(drawMapButton);
            window.draw(drawMapText);

            if (drawMatrix)
            {
                player.handleInput();
                player.updatePosition();
                matrix.draw(window);
            }
        }
        else
        {
            window.draw(wallButton);
            window.draw(wallButtonText);
            window.draw(furnitureButton);
            window.draw(furnitureButtonText);
            window.draw(playerButton);
            window.draw(playerButtonText);
            window.draw(guardButton);
            window.draw(guardButtonText);
            window.draw(saveMapButton);
            window.draw(saveMapButtonText);

            drawGridToCreateMap();
        }

        window.display();
    }
}

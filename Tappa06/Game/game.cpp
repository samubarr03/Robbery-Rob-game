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
      floorButtonText(font, "", 24),
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
    playButton.setPosition({
        static_cast<float>(sf::VideoMode::getDesktopMode().size.x / 2 - playButton.getSize().x / 2),
        static_cast<float>((sf::VideoMode::getDesktopMode().size.y * 2) / 3)
    });

    selectMapButton.setSize({250, 100});
    selectMapButton.setFillColor(sf::Color::Blue);
    selectMapButton.setPosition({
        static_cast<float>(sf::VideoMode::getDesktopMode().size.x / 2 - selectMapButton.getSize().x / 2),
        static_cast<float>((sf::VideoMode::getDesktopMode().size.y * 2) / 3)
    });

    drawMapButton.setSize({250, 100});
    drawMapButton.setFillColor(sf::Color::Blue);
    drawMapButton.setPosition({
        static_cast<float>(sf::VideoMode::getDesktopMode().size.x / 2 - drawMapButton.getSize().x / 2),
        static_cast<float>((sf::VideoMode::getDesktopMode().size.y * 2) / 3 + 120)
    });

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

    playerButton.setSize({150, 50});
    playerButton.setFillColor(sf::Color::Green);
    playerButton.setPosition({20, 230});

    guardButton.setSize({150, 50});
    guardButton.setFillColor(sf::Color::Magenta);
    guardButton.setPosition({20, 300});

    saveMapButton.setSize({150, 50});
    saveMapButton.setFillColor(sf::Color::Cyan);
    saveMapButton.setPosition({20, 370});

    floorButton.setSize({150, 50});
    floorButton.setFillColor(sf::Color::Cyan);
    floorButton.setPosition({20, 440});

    // Testi bottoni disegna mappa
    wallButtonText.setString("Muro");
    wallButtonText.setFillColor(sf::Color::White);
    wallButtonText.setPosition({50, 170});

    playerButtonText.setString("Player");
    playerButtonText.setFillColor(sf::Color::White);
    playerButtonText.setPosition({50, 240});

    guardButtonText.setString("Guardia");
    guardButtonText.setFillColor(sf::Color::White);
    guardButtonText.setPosition({50, 310});

    saveMapButtonText.setString("Salva Mappa");
    saveMapButtonText.setFillColor(sf::Color::White);
    saveMapButtonText.setPosition({30, 380});

    floorButtonText.setString("Pavimento");
    floorButtonText.setFillColor(sf::Color::White);
    floorButtonText.setPosition({30, 450});

    std::vector<std::pair<int, std::string>> furnitureTypes = {
        {TYPE_FURNITURE_BED, "BED"},
        {TYPE_FURNITURE_WARDROBE, "WARDROBE"},
        {TYPE_FURNITURE_KITCHEN, "KITCHEN"},
        {TYPE_FURNITURE_TABLE, "TABLE"},
        {TYPE_FURNITURE_FRIDGE, "FRIDGE"},
        {TYPE_FURNITURE_STOVE, "STOVE"},
        {TYPE_FURNITURE_SINK, "SINK"},
        {TYPE_FURNITURE_SOFA, "SOFA"},
        {TYPE_FURNITURE_TV, "TV"},
        {TYPE_FURNITURE_PLANT, "PLANT"},
        {TYPE_FURNITURE_FIREPLACE, "FIREPLACE"},
        {TYPE_FURNITURE_BATH, "BATH"},
        {TYPE_FURNITURE_BATH_SINK, "BATH_SINK"},
        {TYPE_FURNITURE_TOILET, "TOILET"},
        {TYPE_FURNITURE_WASHINGMACHINE, "WASHINGMACHINE"},
    };

    // Dropdown: Popola gli elementi del menu a discesa partendo dal player button + 50 px
    float dropdownX = playerButton.getPosition().x + 250;
    float dropdownY = 50;

    for (int i = 0; i < furnitureTypes.size(); i++)
    {
        const auto &[id, name] = furnitureTypes[i];

        FurnitureItem item(id, name, font);

        item.buttonShape.setPosition(sf::Vector2f(dropdownX, dropdownY + i * 55));
        item.label.setPosition(sf::Vector2f(item.buttonShape.getPosition().x + 10, item.buttonShape.getPosition().y + 10));
        item.label.setFillColor(sf::Color::Black);

        furnitureItems.push_back(item);
    }
}

void Game::handleMouseClick(sf::Vector2f mousePos)
{
    int mousePosX = static_cast<int>(mousePos.x);
    int mousePosY = static_cast<int>(mousePos.y);

    if (!drawMap)
    {
        // Modalità gioco
        if (playButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Modalità gioco selezionata";

            if (!matrix.isMapLoaded())
            {
                matrix.loadMapFromFile("resources/mapNew.txt");
            }

            drawMatrix = true;
            drawMap = false;

            // Aggiorno il player e la mappa
            player.handleInput();
            player.updatePosition();

            // scansiono la mappa e ogni 2 celle (perchè ogni guardia è grande 4 celle) creo una guardia con la sua posizione
            for (int x = 0; x < matrix.getCols(); x++)
            {
                for (int y = 0; y < matrix.getRows(); y++)
                {
                    bool isTopLeftGuard = (matrix.getMap()[x][y] == TYPE_GUARD) &&
                                          (matrix.getMap()[x + 1][y] == TYPE_GUARD) &&
                                          (matrix.getMap()[x][y + 1] == TYPE_GUARD) &&
                                          (matrix.getMap()[x + 1][y + 1] == TYPE_GUARD);
                    if (isTopLeftGuard)
                    {
                        guards.push_back(Guard(matrix));
                        guards.back().setPosition(sf::Vector2i(x, y));
                    }
                }
            }
        }
        // Modalità selezopna  mappa
        else if (selectMapButton.getGlobalBounds().contains(mousePos))
        {
            std::string mapFile = selectMapToPlay(window);

            if (mapFile.empty())
            {
                std::cout << "Nessuna mappa selezionata\n";
                return;
            }
            matrix.loadMapFromFile(mapFile);
        }

        // Modalità disegna mappa
        else if (drawMapButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Modalità disegna mappa selezionata \n";
            drawMap = true;
            drawMatrix = false;

            matrix.createEmptyMatrix();
        }
    }
    else
    {
        if (wallButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_WALL;
            std::cout << "Muro selezionato \n";
        }
        else if (playerButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_PLAYER;
            std::cout << "Player selezionato \n";
        }
        else if (floorButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_FLOOR;
            std::cout << "Pavimento selezionato \n";
        }
        else if (guardButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_GUARD;
            std::cout << ("Guardia selezionata \n");
        }
        else if (saveMapButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Salva mappa\n";

            auto result = askMapName(window);

            if (result.empty())
            {
                std::cout << "Nessun nome inserito\n";
                return;
            }

            std::string filename = result + ".txt";

            // Percorsi in cui salvare
            std::vector<std::string> paths = {
                "../../resources/" + filename,
                "../../build/bin/resources/" + filename};

            for (const auto &path : paths)
            {
                std::ofstream file(path);
                if (file.is_open())
                {
                    for (const std::vector<int> &row : matrix.getMap())
                    {
                        for (int cell : row)
                        {
                            file << cell << " ";
                        }
                        file << "\n";
                    }
                    file.close();
                    std::cout << "Mappa salvata in: " << path << "\n";
                }
                else
                {
                    std::cerr << "Errore nel salvataggio in: " << path << "\n";
                }
            }
        }
        else
        {
            bool clickedFurnitureItem = false;

            for (const auto &item : furnitureItems)
            {
                if (item.buttonShape.getGlobalBounds().contains(mousePos))
                {
                    selectedTool = item.id;
                    std::cout << "Arredamento selezionato: " << item.name << "\n";
                    clickedFurnitureItem = true;
                    break;
                }
            }

            if (!clickedFurnitureItem)
            {
                matrix.drawItemInPosition(mousePos, selectedTool);
            }
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

                auto &map = matrix.getMap();
                for (int x = 0; x < matrix.getCols(); ++x)
                {
                    for (int y = 0; y < matrix.getRows(); ++y)
                    {
                        if (map[x][y] == TYPE_GUARD)
                            map[x][y] = TYPE_FLOOR;
                    }
                }

                // Per ogni guardia, calcolo la nuova direzione e aggiorno la posizione
                for (auto &guard : guards)
                {
                    guard.setDirection(); // muove la guardia se possibile
                }

                // Dopo aver aggiornato tutte le posizioni, disegno tutte le guardie sulla mappa
                for (auto &guard : guards)
                {
                    guard.updatePosition();
                }

                matrix.draw(window, true);
            }
        }
        else
        {
            window.draw(wallButton);
            window.draw(wallButtonText);
            window.draw(playerButton);
            window.draw(playerButtonText);
            window.draw(guardButton);
            window.draw(guardButtonText);
            window.draw(saveMapButton);
            window.draw(saveMapButtonText);

            window.draw(floorButton);
            window.draw(floorButtonText);

            for (auto &item : furnitureItems)
            {
                window.draw(item.buttonShape);
                window.draw(item.label);
            }

            matrix.draw(window, false);
        }

        window.display();
    }
}
std::string Game::askMapName(sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.openFromFile("resources/arial.ttf"))
    {
        std::cerr << "Errore nel caricamento del font.\n";
        return "";
    }

    sf::Text prompt(font, "Inserisci nome mappa:", 24);

    prompt.setPosition({50, 50});
    prompt.setFillColor(sf::Color::White);

    sf::Text inputText(font, "", 24);
    inputText.setPosition({50, 100});
    inputText.setFillColor(sf::Color::Green);

    sf::Text errorText(font, "", 24);
    errorText.setPosition({50, 150});
    errorText.setFillColor(sf::Color::Red);

    std::string input;
    std::string errorMessage;
    bool done = false;

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(30, 30, 30));

    while (window.isOpen() && !done)
    {
        while (auto eventOpt = window.pollEvent())
        {
            const sf::Event &event = *eventOpt;

            if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    return "";
                else if (keyPressed->code == sf::Keyboard::Key::Enter)
                {
                    std::string filePath = "../../resources/" + input + ".txt";
                    if (std::filesystem::exists(filePath))
                    {
                        errorText.setString("Scegli un altro nome per questa mappa che non sia stato preso");
                        input.clear();
                        inputText.setString("");
                    }
                    else
                    {
                        done = true;
                    }
                }
                else if (keyPressed->code >= sf::Keyboard::Key::A && keyPressed->code <= sf::Keyboard::Key::Z)
                {
                    char letter = static_cast<char>('A' + (static_cast<int>(keyPressed->code) - static_cast<int>(sf::Keyboard::Key::A)));
                    input += letter;
                    inputText.setString(input);
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(prompt);
        window.draw(inputText);
        window.draw(errorText);
        window.display();
    }

    return input;
}

std::string Game::selectMapToPlay(sf::RenderWindow &window)
{
    std::vector<std::string> mapNames;
    std::string path = "resources/";

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".txt")
        {
            mapNames.push_back(entry.path().filename().string()); // solo il nome
        }
    }

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(30, 30, 30));

    sf::Font font;
    if (!font.openFromFile("resources/arial.ttf"))
    {
        std::cerr << "Errore nel caricamento del font.\n";
        return "";
    }

    sf::Text prompt(font, "Seleziona una mappa:", 24);
    prompt.setPosition({50, 50});
    prompt.setFillColor(sf::Color::White);

    std::vector<sf::Text> mapTexts;
    for (size_t i = 0; i < mapNames.size(); ++i)
    {
        sf::Text text(font, mapNames[i], 24);
        text.setPosition({50.f, 100.f + static_cast<float>(i) * 30.f});
        text.setFillColor(sf::Color::White);
        mapTexts.push_back(text);
    }

    while (window.isOpen())
    {
        while (auto eventOpt = window.pollEvent())
        {
            const sf::Event &event = *eventOpt;

            if (event.is<sf::Event::Closed>())
            {
                window.close();
                return "";
            }

            if (const auto *mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for (size_t i = 0; i < mapTexts.size(); ++i)
                    {
                        if (mapTexts[i].getGlobalBounds().contains(mousePos))
                        {
                            // ritorna il path completo
                            return path + mapNames[i];
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(prompt);
        for (const auto &text : mapTexts)
        {
            window.draw(text);
        }
        window.display();
    }

    return "";
}
#include "game.hpp"

Game::Game()
    : window(sf::VideoMode::getFullscreenModes().at(0), "Robbery Rob"),
      matrix(),
      player(matrix),
      gameMode(false),
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
      importMapButtonText(font, "", 24),
      guardRouteButtonText(font, "", 24),
      lootButtonText(font, "", 24),
      exitButtonText(font, "", 24),
      backgroundSprite(backgroundTexture),
      winSprite(winTexture),
      gameOverSprite(gameOverTexture)
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

    if (!winTexture.loadFromFile("resources/win.jpg"))
    {
        std::cerr << "Errore nel caricamento di win.jpg\n";
    }

    if (!gameOverTexture.loadFromFile("resources/gameOver.jpg"))
    {
        std::cerr << "Errore nel caricamento di gameOver.jpg\n";
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y))));

    winSprite.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y))));

    gameOverSprite.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y))));

    // Bottoni home
    playButton.setSize({250, 100});
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition({static_cast<float>(sf::VideoMode::getDesktopMode().size.x / 2 - playButton.getSize().x / 2),
                            static_cast<float>((sf::VideoMode::getDesktopMode().size.y * 2) / 3)});

    selectMapButton.setSize({250, 100});
    selectMapButton.setFillColor(sf::Color::Blue);
    selectMapButton.setPosition({static_cast<float>(sf::VideoMode::getDesktopMode().size.x / 2 - selectMapButton.getSize().x / 2) + 300,
                                 static_cast<float>((sf::VideoMode::getDesktopMode().size.y * 2) / 3)});

    drawMapButton.setSize({250, 100});
    drawMapButton.setFillColor(sf::Color::Blue);
    drawMapButton.setPosition({static_cast<float>(sf::VideoMode::getDesktopMode().size.x / 2 - drawMapButton.getSize().x / 2),
                               static_cast<float>((sf::VideoMode::getDesktopMode().size.y * 2) / 3 + 120)});

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

    // Lista di bottoni
    sf::Vector2f buttonSize = {220, 60};
    const float startX = 20;
    const float startY = 160;
    const float space = 80;

    std::vector<ButtonInfo> buttons = {
        {&saveMapButton, &saveMapButtonText, "Salva Mappa", sf::Color(0, 200, 0)},
        {&importMapButton, &importMapButtonText, "Importa Mappa", sf::Color(0, 200, 0)},
        {&exitButton, &exitButtonText, "Uscita", sf::Color(200, 0, 0)},
        {&floorButton, &floorButtonText, "Pavimento", sf::Color(70, 130, 180)},
        {&wallButton, &wallButtonText, "Muro", sf::Color(70, 130, 180)},
        {&playerButton, &playerButtonText, "Giocatore", sf::Color(70, 130, 180)},
        {&guardButton, &guardButtonText, "Guardia", sf::Color(70, 130, 180)},
        {&guardRouteButton, &guardRouteButtonText, "Cammino Guardia", sf::Color(70, 130, 180)},
        {&lootButton, &lootButtonText, "Bottino", sf::Color(70, 130, 180)},
    };

    for (int i = 0; i < buttons.size(); i++)
    {
        auto &btn = buttons[i];
        sf::Vector2f position = {startX, startY + i * space};

        btn.shape->setSize(buttonSize);
        btn.shape->setFillColor(btn.color);
        btn.shape->setOutlineThickness(2);
        btn.shape->setOutlineColor(sf::Color::Black);
        btn.shape->setPosition(position);

        btn.text->setString(btn.label);
        btn.text->setPosition({
            static_cast<float>(btn.shape->getPosition().x + 20),
            static_cast<float>(btn.shape->getPosition().y + ( buttonSize.y/3))
        });
    }

    std::vector<std::pair<int, std::string>> furnitureTypes = {
        {TYPE_FURNITURE_BED, "Letto"},
        {TYPE_FURNITURE_WARDROBE, "Armadio"},
        {TYPE_FURNITURE_KITCHEN, "Cucina"},
        {TYPE_FURNITURE_TABLE, "Tavolo"},
        {TYPE_FURNITURE_FRIDGE, "Frigo"},
        {TYPE_FURNITURE_STOVE, "Fornelli"},
        {TYPE_FURNITURE_SINK, "Lavandino"},
        {TYPE_FURNITURE_SOFA, "Divano"},
        {TYPE_FURNITURE_TV, "Televisione"},
        {TYPE_FURNITURE_PLANT, "Pianta"},
        {TYPE_FURNITURE_FIREPLACE, "Camino"},
        {TYPE_FURNITURE_BATH, "Vasca"},
        {TYPE_FURNITURE_BATH_SINK, "Lavandino da bagno"},
        {TYPE_FURNITURE_TOILET, "Gabinetto"},
        {TYPE_FURNITURE_WASHINGMACHINE, "Lavatrice"},
    };

    // disegno i bottoni dell' arredamento
    float dropdownX = playerButton.getPosition().x + 250;
    float dropdownY = 70;
    buttonSize = {240, 50};

    for (int i = 0; i < furnitureTypes.size(); i++)
    {
        const auto &[id, name] = furnitureTypes[i];

        FurnitureItem item(id, name, font);

        item.buttonShape.setPosition(sf::Vector2f(dropdownX, dropdownY + i * 60));
        item.buttonShape.setSize(buttonSize);
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
                matrix.loadMapFromFile("resources/newMapComplete.txt");
            }

            player.resetScore();
            gameMode = true;
            drawMap = false;
            matrix.calculateTotalScore();
            player.setMap(matrix);
            guards.clear();

            // scansiono la mappa creo una guardia con la sua posizione
            for (int x = 0; x < matrix.getCols(); x++)
            {
                for (int y = 0; y < matrix.getRows(); y++)
                {
                    auto &map = matrix.getMap();
                    if (map[x][y] == TYPE_GUARD)
                    {
                        // Salto se ho già creato la guardia
                        if ((x > 0 && map[x - 1][y] == TYPE_GUARD) ||
                            (y > 0 && map[x][y - 1] == TYPE_GUARD))
                        {
                            continue;
                        }

                        Guard guard(matrix, sf::Vector2i(x, y));
                        guards.push_back(guard);
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
            std::cout << "quindi non dovrei essere qui se non ho selezionato una mappa";
            matrix.loadMapFromFile(mapFile);
        }

        // Modalità disegna mappa
        else if (drawMapButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Modalità disegna mappa selezionata \n";
            drawMap = true;
            gameMode = false;

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
        else if (importMapButton.getGlobalBounds().contains(mousePos))
        {
            std::cout << "Importa mappa\n";
            std::string mapFile = selectMapToPlay(window);

            if (mapFile.empty())
            {
                std::cout << "Nessuna mappa selezionata\n";
                return;
            }
            std::cout << "quindi non dovrei essere qui se non ho selezionato una mappa";
            matrix.loadMapFromFile(mapFile);
            gameMode = false;
            drawMap = true;
            std::cout << "Mappa importata da: " << mapFile << "\n";
        }
        else if (guardRouteButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_GUARD_ROUTE;
        }
        else if (lootButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_LOOT;
        }
        else if (exitButton.getGlobalBounds().contains(mousePos))
        {
            selectedTool = TYPE_EXIT;
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
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
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
                    gameMode = false;
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

            if (gameMode)
            {
                player.handleInput(dt);
                player.updatePosition();

                auto &map = matrix.getMap();
                for (int x = 0; x < matrix.getCols(); x++)
                {
                    for (int y = 0; y < matrix.getRows(); y++)
                    {
                        if (map[x][y] == TYPE_GUARD)
                            map[x][y] = TYPE_FLOOR;
                    }
                }

                for (auto &guard : guards)
                {
                    guard.setDirection(player.getPosition());
                    guard.moveGuard(player.getPosition(), dt);
                    guard.updatePosition();
                    if (guard.getPosition() == player.getPosition())
                        showGameOver = true;
                }

                if (player.isOnExit())
                {
                    showWin = true;
                    std::cout << "Hai vinto";
                }

                if (showWin || showGameOver)
                {
                    if (!endScreenStarted)
                    {
                        endClock.restart();
                        endScreenStarted = true;
                        std::cout << "Hai vinto o perso"; // Solo una volta!
                    }
                    if (showWin)
                    {
                        window.draw(winSprite);
                    }
                    else if (showGameOver)
                    {
                        window.draw(gameOverSprite);
                    }

                    if (endClock.getElapsedTime().asSeconds() > 5)
                    {
                        std::cout << "Sino pasati 5 secondi";
                        showWin = false;
                        showGameOver = false;
                        gameMode = false;
                    }
                }
                else
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
            window.draw(importMapButton);
            window.draw(importMapButtonText);
            window.draw(guardRouteButton);
            window.draw(guardRouteButtonText);
            window.draw(lootButton);
            window.draw(lootButtonText);
            window.draw(exitButton);
            window.draw(exitButtonText);

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
                // tasto per cancellare
                else if (keyPressed->code == sf::Keyboard::Key::Backspace)
                {
                    if (!input.empty())
                        input.pop_back();
                    inputText.setString(input);
                }
                else if (keyPressed->code >= sf::Keyboard::Key::A && keyPressed->code <= sf::Keyboard::Key::Z)
                {
                    char letter = static_cast<char>('A' + (static_cast<int>(keyPressed->code) - static_cast<int>(sf::Keyboard::Key::A)));
                    input += letter;
                    inputText.setString(input);
                }
                else if (keyPressed->code >= sf::Keyboard::Key::Num0 && keyPressed->code <= sf::Keyboard::Key::Num9)
                {
                    char number = static_cast<char>('0' + (static_cast<int>(keyPressed->code) - static_cast<int>(sf::Keyboard::Key::Num0)));
                    input += number;
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
            mapNames.push_back(entry.path().filename().string());
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

            else if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    return "";
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
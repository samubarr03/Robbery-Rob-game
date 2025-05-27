#include "matrix.hpp"

Matrix::Matrix()
{
    std::string filename = "resources/mapNew.txt";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Impossibile aprire il file: " << filename << "\n";
        createEmptyMatrix();
    }
    loadMapFromFile(filename);

    // Generico per tutti gli elementi
    loadTexture(TYPE_FLOOR, "floor.png", 1, 1);
    loadTexture(TYPE_WALL, "wall.jpeg", 2, 2);
    loadTexture(TYPE_PLAYER, "playerRunning.jpeg", 2, 2);
    loadTexture(TYPE_GUARD, "guard.png", 2, 2);
    loadTexture(TYPE_LOOT, "loot.png", 1, 1);
    loadTexture(TYPE_GUARD_ROUTE, "guard-route.png", 1, 1);

    // Arredamento
    loadTexture(TYPE_FURNITURE_BED, "bed.png", 5, 5);
    loadTexture(TYPE_FURNITURE_WARDROBE, "desk.png", 6, 4);
    loadTexture(TYPE_FURNITURE_KITCHEN, "kitchen.png", 8, 3);
    loadTexture(TYPE_FURNITURE_TABLE, "tavolo.png", 4, 4);
    loadTexture(TYPE_FURNITURE_FRIDGE, "fridge.png", 5, 5);
    loadTexture(TYPE_FURNITURE_STOVE, "stove.png", 5, 5);
    loadTexture(TYPE_FURNITURE_SINK, "sink.png", 5, 5);
    loadTexture(TYPE_FURNITURE_SOFA, "sofa.png", 10, 6);
    loadTexture(TYPE_FURNITURE_TV, "tv.png", 6, 3);
    loadTexture(TYPE_FURNITURE_PLANT, "plant.png", 3, 3);
    loadTexture(TYPE_FURNITURE_FIREPLACE, "fireplace.png", 5, 5);
    loadTexture(TYPE_FURNITURE_BATH, "bath.png", 3, 6);
    loadTexture(TYPE_FURNITURE_BATH_SINK, "bathroom-sink.png", 4, 4);
    loadTexture(TYPE_FURNITURE_TOILET, "toilet.png", 5, 3);
    loadTexture(TYPE_FURNITURE_WASHINGMACHINE, "WashingMachine.png", 6, 6);
}

void Matrix::loadTexture(int type, const std::string &name, int w, int h)
{
    Texture texture;
    texture.type = type;
    texture.name = name;
    texture.width = w;
    texture.height = h;

    std::string path = "resources/";

    if (!texture.texture.loadFromFile(path + name))
    {
        std::cerr << "Errore caricando la texture: " << name << "\n";
        return;
    }

    textureMap[type] = texture;
}

void Matrix::loadMapFromFile(const std::string &filename)
{
    std::ifstream mapFile(filename);
    if (!mapFile.is_open())
    {
        std::cerr << "Errore nell'apertura del file: " << filename << "\n";
        createEmptyMatrix();
        return;
    }

    map.clear();
    std::string line;
    bool validMap = true;

    while (std::getline(mapFile, line))
    {
        std::stringstream ss(line);
        std::vector<int> row;
        int value;

        // Legge i valori separati da spazi
        while (ss >> value)
        {
            row.push_back(value);
        }

        if (row.empty())
        {
            validMap = false;
            break;
        }

        map.push_back(row);
    }

    // Controllo che la mappa non sia vuota e tutte le righe abbiano stessa lunghezza
    if (map.empty() || map[0].empty())
    {
        validMap = false;
    }
    else
    {
        size_t expectedCols = map[0].size();
        for (const auto &r : map)
        {
            if (r.size() != expectedCols)
            {
                validMap = false;
                break;
            }
        }
    }

    if (!validMap)
    {
        std::cerr << "Errore: mappa malformata o vuota nel file " << filename << ". Verrà caricata una matrice vuota.\n";
        createEmptyMatrix();
        mapLoaded = false;
    }
    else
    {
        mapLoaded = true;
        rows = map.size();
        cols = map[0].size();
    }
}

std::vector<std::vector<int>> &Matrix::getMap()
{
    return map;
}

void Matrix::setMap(std::vector<std::vector<int>> newMap)
{
    map = newMap;
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getCols() const
{
    return cols;
}

void Matrix::draw(sf::RenderWindow &window, bool isGameMode)
{
    if (cols == 0 || rows == 0)
    {
        std::cerr << "Mappa non valida, non posso disegnare.\n";
        return;
    }
    if (!isGameMode)
    {
        /* calcolo la posizione della griglia:
            LARGHEZZA: da 1/3 sinistra a 10 px meno della fine dello schermo
            ALTEZZA: da 10 px sotto il limite a 10 px sopra il minimo
        */
        GRID_OFFSET_X = sf::VideoMode::getDesktopMode().size.x / 3;
        GRID_OFFSET_Y = 10;
        cellWidth = (sf::VideoMode::getDesktopMode().size.x - GRID_OFFSET_X - 10) / GRID_SIZE;
        cellHeight = sf::VideoMode::getDesktopMode().size.y / rows;
    }
    else
    {
        GRID_OFFSET_X = 0;
        GRID_OFFSET_Y = 0;
        cellWidth = sf::VideoMode::getDesktopMode().size.x / GRID_SIZE;
        cellHeight = sf::VideoMode::getDesktopMode().size.y / rows;
    }

    // Disegno prima lo sfondo (pavimento)
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            sf::RectangleShape floor(sf::Vector2f(cellWidth, cellHeight));
            floor.setPosition({x * cellWidth + GRID_OFFSET_X, y * cellHeight + GRID_OFFSET_Y});
            floor.setTexture(&textureMap[TYPE_FLOOR].texture);
            window.draw(floor);
        }
    }

    // Matrice per evitare ridisegni multipli
    std::vector<std::vector<bool>> drawn(cols, std::vector<bool>(rows, false));

    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            int type = map[x][y];

            // Salto se è già stato disegnato o è una cella vuota
            if (type <= 0 || drawn[x][y])
                continue;

            const auto &tex = textureMap[type];
            int w = tex.width;
            int h = tex.height;

            /*
            if (w == 1 && h == 1)
            {
                sf::Sprite sprite(tex.texture);
                sprite.setPosition(sf::Vector2f(x * cellWidth + GRID_OFFSET_X, y * cellHeight + GRID_OFFSET_Y));
                sprite.setScale({static_cast<float>(cellWidth) / tex.texture.getSize().x,
                                 static_cast<float>(cellHeight) / tex.texture.getSize().y});

                window.draw(sprite);
                drawn[x][y] = true;
                continue;
            }
*/
            // Controllo che tutte le celle dell’oggetto siano effettivamente dello stesso tipo

            sf::Sprite sprite(tex.texture);
            sprite.setPosition(sf::Vector2f(x * cellWidth + GRID_OFFSET_X, y * cellHeight + GRID_OFFSET_Y));
            sprite.setScale({(float)(cellWidth * w) / tex.texture.getSize().x,
                             (float)(cellHeight * h) / tex.texture.getSize().y});
            window.draw(sprite);
            // Segno le celle coperte da questo oggetto come già disegnate
            for (int dx = 0; dx < w; dx++)
            {
                for (int dy = 0; dy < h; dy++)
                {
                    if (x + dx < cols && y + dy < rows)
                        drawn[x + dx][y + dy] = true;
                }
            }
        }
    }
}

void Matrix::createEmptyMatrix()
{
    mapLoaded = false;
    std::vector<std::vector<int>> emptyMap(GRID_SIZE, std::vector<int>(GRID_SIZE, TYPE_FLOOR));
    map = emptyMap;
    rows = GRID_SIZE;
    cols = GRID_SIZE;
}

bool Matrix::isMapLoaded()
{
    return mapLoaded;
}

void Matrix::drawItemInPosition(sf::Vector2f mousePos, int selectedTool)
{
    
    int cellX = (mousePos.x - GRID_OFFSET_X) / cellWidth;
    int cellY = (mousePos.y - GRID_OFFSET_Y) / cellHeight;


    if (selectedTool == TYPE_WALL && !isDrawingWall)
    {
        isDrawingWall = true;
        posxWall = (mousePos.x - GRID_OFFSET_X) / cellWidth;
        posyWall = (mousePos.y - GRID_OFFSET_Y) / cellHeight;
    }
    else if (selectedTool == TYPE_WALL && isDrawingWall)
    {
        if (cellX == posxWall || cellY == posyWall)
        {
            // Disegna una linea orizzontale o verticale
            int startX = std::min(posxWall, cellX);
            int endX = std::max(posxWall, cellX);
            int startY = std::min(posyWall, cellY);
            int endY = std::max(posyWall, cellY);

            for (int x = startX; x <= endX; ++x)
            {
                for (int y = startY; y <= endY; ++y)
                {
                    map[x][y] = TYPE_WALL;
                }
            }
        }
        isDrawingWall = false;
        std::cout << "Muro disegnato da: " << posxWall << ", " << posyWall << " a: " << cellX << ", " << cellY << "\n";
        return;
    }
    else if (selectedTool == TYPE_FLOOR)
    {
        auto typeAtCell = map[cellX][cellY];
       
        if (typeAtCell != TYPE_FLOOR)
        {
            std::cout << "Elimino elemento in cella: " << cellX << ", " << cellY << "\n";
            int w = textureMap[typeAtCell].width;
            int h = textureMap[typeAtCell].height;

            if (cellX + w > GRID_SIZE || cellY + h > GRID_SIZE)
            {
                std::cerr << "Oggetto troppo grande per la posizione selezionata.\n";
                return;
            }

            for (int dx = 0; dx < w; dx++)
            {
                for (int dy = 0; dy < h; dy++)
                {
                    map[cellX + dx][cellY + dy] = TYPE_FLOOR;
                }
            }
        }
    }
    
    if (cellX < 0 || cellX >= GRID_SIZE || cellY < 0 || cellY >= GRID_SIZE)
    {
        std::cerr << "Cella selezionata fuori dai limiti della griglia.\n";
        return;
    }
    std::cout << "Cella selezionata: " << cellX << ", " << cellY << "\n";

    int w = textureMap[selectedTool].width;
    int h = textureMap[selectedTool].height;

    // Controllo di non uscire dai limiti della mappa
    if (cellX + w > GRID_SIZE || cellY + h > GRID_SIZE)
    {
        std::cerr << "Oggetto troppo grande per la posizione selezionata.\n";
        return;
    }

    for (int dx = 0; dx < w; dx++)
    {
        for (int dy = 0; dy < h; dy++)
        {
            map[cellX + dx][cellY + dy] = selectedTool;
        }
    }
}

std::map<int, Texture> Matrix::getFurnitureTextureMap()
{
    return textureMap;
}
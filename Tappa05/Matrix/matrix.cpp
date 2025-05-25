#include "matrix.hpp"

Matrix::Matrix()
{
    std::string filename = "resources/map.txt";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Impossibile aprire il file: " << filename << "\n";
        mapLoaded = false;
        return;
    }
    loadMapFromFile(filename);

 
    // Generico per tutti gli elementi
    loadTexture(TYPE_FLOOR, "floor.png", 1, 1);
    loadTexture(TYPE_WALL, "wall.jpeg", 1, 1);
    loadTexture(TYPE_PLAYER, "playerRunning.jpeg", 4, 4);
    loadTexture(TYPE_GUARD, "guard.png", 4, 4);
    loadTexture(TYPE_LOOT, "loot.png", 1, 1);
    loadTexture(TYPE_GUARD_ROUTE, "guard-route.png", 1, 1);

    // Arredamento
    loadTexture(TYPE_FURNITURE_BED, "bed.png", 3, 3);
    loadTexture(TYPE_FURNITURE_WARDROBE, "desk.png", 3, 1);
    loadTexture(TYPE_FURNITURE_KITCHEN, "kitchen.png", 5, 1);
    loadTexture(TYPE_FURNITURE_TABLE, "tavolo.png", 4, 4);
    loadTexture(TYPE_FURNITURE_FRIDGE, "fridge.png", 2, 2);
    loadTexture(TYPE_FURNITURE_STOVE, "stove.png", 2, 2);
    loadTexture(TYPE_FURNITURE_SINK, "sink.png", 2, 2);
    loadTexture(TYPE_FURNITURE_SOFA, "sofa.png", 5, 3);
    loadTexture(TYPE_FURNITURE_TV, "tv.png", 2, 1);
    loadTexture(TYPE_FURNITURE_PLANT, "plant.png", 1, 1);
    loadTexture(TYPE_FURNITURE_FIREPLACE, "fireplace.png", 1, 4);
    loadTexture(TYPE_FURNITURE_BATH, "bath.png", 1, 3);
    loadTexture(TYPE_FURNITURE_BATH_SINK, "bathroom-sink.png", 2, 1);
    loadTexture(TYPE_FURNITURE_TOILET, "toilet.png", 1, 2);
    loadTexture(TYPE_FURNITURE_WASHINGMACHINE, "WashingMachine.png", 2, 2);
}


void Matrix::loadTexture(int type, const std::string &name, int w, int h)
{
    Texture texture;
    texture.type = type;
    texture.name = name;
    texture.width = w;
    texture.height = h;

    std::string path = "resources/";

    if (!texture.texture.loadFromFile(path + name ))
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
        return;
    }
    mapLoaded = true;
    map.clear();
    std::string line;

    while (std::getline(mapFile, line))
    {
        std::vector<int> row;
        for (char c : line)
        {
            if (std::isdigit(c))
            {
                row.push_back(c - '0');
            }
            else
            {
                std::cerr << "Errore: carattere non numerico nella mappa\n";
                return;
            }
        }
        map.push_back(row);
    }

    mapFile.close();

    rows = map.size();
    cols = map[0].size();
    cellWidth = sf::VideoMode::getDesktopMode().size.x / cols;
    cellHeight = sf::VideoMode::getDesktopMode().size.y / rows;
    space = 0;
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
    if (!isGameMode)
    {
        /* calcolo la posizione dela griglia:
            LARGHEZZA: da 1/3 sinistra a 10 px meno della fine dello schermo
            ALTEZZA: da 10 px sotto il limite a 10 px sopra il minimo
            */
        GRID_OFFSET_X = sf::VideoMode::getDesktopMode().size.x / 3;
        GRID_OFFSET_Y = 10;
        // calcolo il cell size
        cellWidth = (sf::VideoMode::getDesktopMode().size.x - GRID_OFFSET_X - 10) / GRID_SIZE;
        cellHeight = sf::VideoMode::getDesktopMode().size.y / rows;
    }
    else
    {
        GRID_OFFSET_X = 0;
        GRID_OFFSET_Y = 0;
        cellWidth = (sf::VideoMode::getDesktopMode().size.x) / GRID_SIZE;
        cellHeight = sf::VideoMode::getDesktopMode().size.y / rows;
    }

    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            cell.setPosition({x * cellWidth + GRID_OFFSET_X,
                              y * cellHeight + GRID_OFFSET_Y});
            int type = map[x][y];
            if (textureMap.find(type) != textureMap.end()) {
                cell.setTexture(&textureMap[type].texture);
            } else {
                cell.setFillColor(sf::Color::Red);
            }

            window.draw(cell);
        }
    }
}

void Matrix::createEmptyMatrix()
{
    mapLoaded = false;
    std::vector<std::vector<int>> emptyMap(GRID_SIZE, std::vector<int>(GRID_SIZE, TYPE_FLOOR));
    map =  emptyMap;

}

bool Matrix::isMapLoaded()
{
    return mapLoaded;
}

void Matrix::drawItemInPosition(sf::Vector2f mousePos, int selectedTool)
{
    // Clic su una cella o movimeto con il mouse cliccato
    int cellX = (mousePos.x - GRID_OFFSET_X) / cellWidth;
    int cellY = (mousePos.y - GRID_OFFSET_Y) / cellHeight;


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
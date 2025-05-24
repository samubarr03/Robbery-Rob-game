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

    if (!floorTexture.loadFromFile("resources/floor.jpeg"))
    {
        std::cerr << "Errore nel caricamento di floor.jpeg\n";
    }

    if (!playerTexture.loadFromFile("resources/playerRunning.jpeg"))
    {
        std::cerr << "Errore nel caricamento di playerRunning.jpeg\n";
    }

    if (!wallTexture.loadFromFile("resources/wall.jpeg"))
    {
        std::cerr << "Errore nel caricamento di wall.jpeg\n";
    }
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
            switch (map[x][y])
            {
            case TYPE_FLOOR:
                cell.setTexture(&floorTexture);
                break;
            case TYPE_PLAYER:
                cell.setTexture(&playerTexture);
                break;
            case TYPE_WALL:
                cell.setTexture(&wallTexture);
                break;
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

    if (cellX >= 0 && cellX < GRID_SIZE && cellY >= 0 && cellY < GRID_SIZE)
    {
        switch (selectedTool)
        {
        case TYPE_WALL:
            map[cellX][cellY] = TYPE_WALL;
            break;

        case TYPE_FURNITURE:
            map[cellX][cellY] = TYPE_FURNITURE;
            break;

        case TYPE_PLAYER:
            if (cellX + 1 < GRID_SIZE && cellY + 1 < GRID_SIZE)
            {
                for (int dx = 0; dx < 2; dx++)
                    for (int dy = 0; dy < 2; dy++)
                        map[cellX + dx][cellY + dy] = TYPE_PLAYER;
            }
            break;

        case TYPE_GUARD:
            if (cellX + 1 < GRID_SIZE && cellY + 1 < GRID_SIZE)
            {
                for (int dx = 0; dx < 2; dx++)
                    for (int dy = 0; dy < 2; dy++)
                        map[cellX + dx][cellY + dy] = TYPE_GUARD;
            }
            break;

        default:
            break;
        }
    }

}
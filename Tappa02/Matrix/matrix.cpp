#include "matrix.hpp"

Matrix::Matrix()
{
    std::string filename = "resources/map.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file: " << filename << "\n";
        return;
    }
    loadMapFromFile(filename);

    if (!floorTexture.loadFromFile("resources/floor.jpeg")) {
        std::cerr << "Errore nel caricamento di floor.jpeg\n";
    }

    if (!playerTexture.loadFromFile("resources/playerRunning.jpeg")) {
        std::cerr << "Errore nel caricamento di playerRunning.jpeg\n";
    }
}


void Matrix::loadMapFromFile(const std::string &filename) {
    std::ifstream mapFile(filename);
    if (!mapFile.is_open()) {
        std::cerr << "Errore nell'apertura del file: " << filename << "\n";
        return;
    }

    map.clear();
    std::string line;

    while (std::getline(mapFile, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (std::isdigit(c)) {
                row.push_back(c - '0');
            } else {
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

void Matrix::draw(sf::RenderWindow &window)
{

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            cell.setPosition({sf::Vector2f(x * cellWidth, y * cellHeight)});
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            switch (map[x][y])
            {
            case TYPE_FLOOR:
                cell.setTexture(&floorTexture);
                break;
            case TYPE_PLAYER:
                cell.setTexture(&playerTexture);
                break;
            case TYPE_WALL:
                cell.setFillColor(sf::Color::Blue);
                break;
            }

            window.draw(cell);
        }
    }
}

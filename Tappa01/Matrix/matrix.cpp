#include "matrix.hpp"

Matrix::Matrix() {
    std::ifstream file("resources/map.txt");
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file" ;
        return;
    }

    map.clear();
    std::string line;

    while (std::getline(file, line)) {
        if (line.length() != 64) {
            std::cerr << "Errore: ogni riga deve avere esattamente 64 caratteri, ma è lunga " << line.length() ;
            return;
        }

        std::vector<int> row;
        for (char c : line) {
            if (std::isdigit(c)) {
                row.push_back(c - '0');
            } else {
                std::cerr << "Errore: carattere non numerico nella mappa" ;
                return;
            }
        }

        map.push_back(row);
    }

    file.close();

    // Controlla che ci siano esattamente 64 righe
    if (map.size() != 64) {
        std::cerr << "Errore: il file deve contenere esattamente 64 righe, ne ha " << map.size() ;
        return;
    }

    rows = map.size();
    cols = map[0].size();
    cellWidth = sf::VideoMode::getDesktopMode().size.x / cols;
    cellHeight = sf::VideoMode::getDesktopMode().size.y / rows;
    space = 0;
}

std::vector<std::vector<int>>& Matrix::getMap() {
    return map;
}

void Matrix::setMap(std::vector<std::vector<int>> newMap) {
    map = newMap;
}

int Matrix::getRows() const{
    return rows;
}

int Matrix::getCols() const{
    return cols;
}

void Matrix::draw(sf::RenderWindow& window) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
           sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            cell.setPosition({sf::Vector2f(x * cellWidth, y * cellHeight)});
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            switch (map[x][y]) {
                case TYPE_FLOOR:
                    cell.setFillColor(sf::Color::White);
                    break;
                case TYPE_PLAYER: 
                    cell.setFillColor(sf::Color::Green);
                    break;
                case TYPE_WALL:
                    cell.setFillColor(sf::Color::Blue);
                    break;
            }

            window.draw(cell);
        }
    }
}


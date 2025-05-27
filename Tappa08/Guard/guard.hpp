#include "../Utils/utils.hpp"
#include "../Matrix/matrix.hpp"

class Matrix;

class Guard {
public:
    Guard(Matrix& matrix, sf::Vector2i startPos);
    void setDirection(const sf::Vector2i& playerPos);
    void moveGuard(const sf::Vector2i& playerPos, float dt);
    void updatePosition();
    sf::Vector2i getPosition() const;
    bool isOnPlayer();

        void findConnectedRoutePath(sf::Vector2i start);
    sf::Vector2i findNearestGuardRoute();
    bool canMoveTo(sf::Vector2i newPos) const;
    bool isPlayerVisible(const sf::Vector2i& playerPos) const;

private:
    Matrix& matrix;
    sf::Vector2i position;
    std::vector<sf::Vector2i> patrolPath;
    std::vector<std::pair<sf::Vector2i, int>> previousTiles;

    int currentPatrolIndex;
    float moveTimer;
    bool chasingPlayer;
    float speed;
    const int GUARD_VISIBILITY = 5;
};

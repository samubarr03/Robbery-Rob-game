#include "guard.hpp"

Guard::Guard(Matrix &matrix, sf::Vector2i startPos)
    : matrix(matrix), position(startPos), currentPatrolIndex(0), chasingPlayer(false), speed(0.8f), moveTimer(0.0f)
{
    // cerco la GUARD_ROUTE più vicina
    sf::Vector2i nearest = findNearestGuardRoute();
    // vuol dire che non ci sono percorsi di guardia
    if (nearest.x == -1)
        return;

    // applico il dfs
    std::vector<std::vector<bool>> visited(matrix.getCols(), std::vector<bool>(matrix.getRows(), false));

    std::vector<sf::Vector2i> stack;
    stack.push_back(nearest);
    visited[nearest.x][nearest.y] = true;
    patrolPath.clear();

    while (!stack.empty())
    {
        sf::Vector2i current = stack.back();
        stack.pop_back();
        patrolPath.push_back(current);

        // controllo le 4 direzioni
        sf::Vector2i neighbors[] = {
        {current.x + 1, current.y},
        {current.x - 1, current.y},
        {current.x, current.y + 1},
        {current.x, current.y - 1}
    };

    for (const auto& neighbor : neighbors)
    {
        if (neighbor.x >= 0 && neighbor.y >= 0 &&
            neighbor.x < matrix.getCols() && neighbor.y < matrix.getRows() &&
            !visited[neighbor.x][neighbor.y] &&
            matrix.getMap()[neighbor.x][neighbor.y] == TYPE_GUARD_ROUTE)
        {
            visited[neighbor.x][neighbor.y] = true;
            stack.push_back(neighbor);
        }
    }
    }
}

sf::Vector2i Guard::findNearestGuardRoute()
{
    sf::Vector2i nearest(-1, -1);
    float minDist = 999;
    auto &map = matrix.getMap();

    for (int x = 0; x < matrix.getCols(); x++)
    {
        for (int y = 0; y < matrix.getRows(); y++)
        {
            if (map[x][y] == TYPE_GUARD_ROUTE)
            {
                // differenza assoluta tra le coordinate della guardia e quelle del percorso
                float distSq = (x - position.x) * (x - position.x) + (y - position.y) * (y - position.y);
                if (distSq < minDist)
                {
                    minDist = distSq;
                    nearest = sf::Vector2i(x, y);
                }
            }
        }
    }
    return nearest;
}

bool Guard::canMoveTo(sf::Vector2i newPos) const
{
    if (newPos.x < 0 || newPos.y < 0 ||
        newPos.x + 1 >= matrix.getCols() || newPos.y + 1 >= matrix.getRows())
        return false;

    auto &map = matrix.getMap();
    auto isWalkable = [&](int x, int y)
    {
        int type = map[x][y];
        return type == TYPE_FLOOR || type == TYPE_GUARD_ROUTE ||
               type == TYPE_LOOT || type == TYPE_EXIT ||
               type == TYPE_PLAYER;
    };

    return isWalkable(newPos.x, newPos.y) &&
           isWalkable(newPos.x + 1, newPos.y) &&
           isWalkable(newPos.x, newPos.y + 1) &&
           isWalkable(newPos.x + 1, newPos.y + 1);
}

bool Guard::isPlayerVisible(const sf::Vector2i &playerPos) const
{

    return playerPos.x >= position.x - GUARD_VISIBILITY &&
           playerPos.x <= position.x + GUARD_VISIBILITY &&
           playerPos.y >= position.y - GUARD_VISIBILITY &&
           playerPos.y <= position.y + GUARD_VISIBILITY;
}

void Guard::setDirection(const sf::Vector2i &playerPos)
{
    chasingPlayer = isPlayerVisible(playerPos);

    if( !chasingPlayer )
    {
        speed = 0.5f;
    }
    else
    {
        speed = 0.2f;
    }
}

void Guard::moveGuard(const sf::Vector2i &playerPos, float dt)
{
    moveTimer += dt;
    if (moveTimer < speed)
        return;
    moveTimer = 0.0f;

    if (isPlayerVisible(playerPos))
    {
        // Insegue il player
        sf::Vector2i newPos = position;
        if (playerPos.x != position.x)
        {
            if (playerPos.x > position.x)
                newPos.x++;
            else
                newPos.x--;
        }
        else if (playerPos.y != position.y)
        {
            if (playerPos.y > position.y)
                newPos.y++;
            else
                newPos.y--;
        }
        if (canMoveTo(newPos))
            position = newPos;
    }
    else if (!patrolPath.empty())
    {
        // Segue il percorso
        sf::Vector2i target = patrolPath[currentPatrolIndex];
        sf::Vector2i diff = target - position;
        sf::Vector2i newPos = position;
        if (target.x != position.x)
        {
            if (target.x > position.x)
                newPos.x++;
            else
                newPos.x--;
        }
        else if (target.y != position.y)
        {
            if (target.y > position.y)
                newPos.y++;
            else
                newPos.y--;
        }
        if (canMoveTo(newPos))
            position = newPos;
        if (position == target)
            // Passa al prossimo punto del percorso
            currentPatrolIndex = (currentPatrolIndex + 1) % patrolPath.size();
    }
}

void Guard::updatePosition()
{
    // Ripristina il tipo del terreno sotto la guardia
    for (auto &tile : previousTiles)
        matrix.getMap()[tile.first.x][tile.first.y] = tile.second;
    previousTiles.clear();

    int px = position.x;
    int py = position.y;
    if (px + 1 < matrix.getCols() && py + 1 < matrix.getRows())
    {
        previousTiles.push_back({sf::Vector2i(px, py), matrix.getMap()[px][py]});
        previousTiles.push_back({sf::Vector2i(px, py + 1), matrix.getMap()[px][py + 1]});
        previousTiles.push_back({sf::Vector2i(px + 1, py), matrix.getMap()[px + 1][py]});
        previousTiles.push_back({sf::Vector2i(px + 1, py + 1), matrix.getMap()[px + 1][py + 1]});

        matrix.getMap()[px][py] = TYPE_GUARD;
        matrix.getMap()[px][py + 1] = TYPE_GUARD;
        matrix.getMap()[px + 1][py] = TYPE_GUARD;
        matrix.getMap()[px + 1][py + 1] = TYPE_GUARD;
    }
}

sf::Vector2i Guard::getPosition() const { return position; }


bool Guard::isOnPlayer(){
    for (const auto &[pos, originalType] : previousTiles)
    {
        if (originalType == TYPE_PLAYER)
        {
            return true;
        }
    }
    return false;
}
#include "CollisionHandler.h"
#include "../Core/Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
    m_CollisionTilemap = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool xoverlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yoverlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (xoverlaps && yoverlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = 32;
    int rowCount = 20;
    int colCount = 60;

    int leftTile = a.x / tileSize;
    int rightTile = (a.x + a.w) / tileSize;
    int topTile = a.y / tileSize;
    int bottomTile = (a.y + a.h) / tileSize;

    if (leftTile < 0) leftTile = 0;
    if (rightTile >= colCount) rightTile = colCount - 1;
    if (topTile < 0) topTile = 0;
    if (bottomTile >= rowCount) bottomTile = rowCount - 1;

    for (int i = topTile; i <= bottomTile; i++)
    {
        for (int j = leftTile; j <= rightTile; j++)
        {
            if (m_CollisionTilemap[i][j] > 0)
            {
                return true;
            }
        }
    }

    return false; // No collision found
}

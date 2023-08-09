#pragma once
#include <SDL_rect.h>

#include "../Map/TileLayer.h"

class CollisionHandler
{
public:
    static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

    CollisionHandler();
    bool CheckCollision(SDL_Rect a, SDL_Rect b); // collision between two objects/box colliders (a, b)
    bool MapCollision(SDL_Rect a);

private:

    TileMap m_CollisionTilemap;
    TileLayer* m_CollisionLayer;
    static CollisionHandler* s_Instance;
};

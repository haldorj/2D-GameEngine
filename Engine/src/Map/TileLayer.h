#pragma once

#include "Layer.h"
#include <string>
#include <vector>

struct Tileset
{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TileSetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer
{
public:
    TileLayer(){}
    TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tilesets);

    virtual void Render();
    virtual void Update();

    TileMap GetTileMap() { return m_TileMap; }
    
private:
    int m_TileSize;
    int m_RowCount, m_ColCount;
    TileMap m_TileMap;
    TileSetList m_Tilesets;
};

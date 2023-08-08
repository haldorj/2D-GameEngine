#pragma once

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "../../Vendor/TinyXML2/tinyxml2.h"

class MapParser
{
public:
    static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

    bool Load();
    void Clean();

    GameMap* GetMap(std::string id) { return m_MapDict[id]; }
    
private:
    bool Parse(std::string id, std::string source);
    Tileset ParseTileset(tinyxml2::XMLElement* xmlTileset);
    TileLayer* ParseTileLayer(tinyxml2::XMLElement* xmlLayer, TileSetList tilesets, int tileSize, int rowCount, int colCount);
    
    MapParser() {}
    static MapParser* s_Instance;
    std::map<std::string, GameMap*> m_MapDict;
};

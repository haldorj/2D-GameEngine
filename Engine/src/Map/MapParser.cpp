#include "MapParser.h"

#include <iostream>
#include <SDL_log.h>
#include <sstream>

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    // ok
    return Parse("map", "Assets/Maps/map.tmx");
}

bool MapParser::Parse(std::string id, std::string source)
{
    // create a TinyXML document and load the map XML
    tinyxml2::XMLDocument xml;
    xml.LoadFile(source.c_str());

    if (xml.Error())
    {
        std::cerr << "Failed to load: " << source << " Error: " << xml.ErrorName() << std::endl;
        return false;
    }
    std::cerr << "Loaded: " << source << " successfully. Error: " << xml.ErrorName() << std::endl;

    // get the root node
    tinyxml2::XMLElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;
    root->QueryIntAttribute("width", &colcount);
    root->QueryIntAttribute("height", &rowcount);
    root->QueryIntAttribute("tilewidth", &tilesize);

    // Parse tile sets
    TileSetList tilesets;
    for (tinyxml2::XMLElement* e = root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    // Parse layers
    GameMap* gamemap = new GameMap();
    
    for (tinyxml2::XMLElement* e = root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            
            if(gamemap)
            {
                gamemap->GetMapLayers().push_back(tilelayer);
            }
        }
    }
    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(tinyxml2::XMLElement* xmlTileset)
{
    // ok
    Tileset tileset;
    
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->QueryIntAttribute("firstgid", &tileset.FirstID);
    
    xmlTileset->QueryIntAttribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->QueryIntAttribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    
    xmlTileset->QueryIntAttribute("tilewidth", &tileset.TileSize);

    tinyxml2::XMLElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");

    // SDL_Log("name: %s, firstgid: %i, tilecount: %i, rows: %i, columns: %i, tilewidth: %i, source: %s",
    //     tileset.Name.c_str(), tileset.FirstID, tileset.TileCount, tileset.RowCount, tileset.ColCount, tileset.TileSize, tileset.Source.c_str());
    
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(tinyxml2::XMLElement* xmlLayer, TileSetList tilesets, int tileSize, int rowCount,
    int colCount)
{
    tinyxml2::XMLElement* data = nullptr;
    for (tinyxml2::XMLElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    if (!data) { std::cout << "No data \n"; return nullptr; }

    std::string matrix = std::string(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowCount, std::vector<int>(colCount, 0));

    for (int row = 0; row < rowCount; row++)
    {
        for (int col = 0; col < colCount; col++)
        {
            getline(iss, id, ',');

            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
                break;
        }
    }

    return new TileLayer(tileSize, rowCount, colCount, tilemap, tilesets);
}

void MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
        it->second = nullptr;

    m_MapDict.clear();
}
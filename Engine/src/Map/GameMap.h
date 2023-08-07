#pragma once
#include <vector>

#include "Layer.h"

class GameMap
{
public:
    void Render()
    {
        for (const auto mapLayers : m_MapLayers)
            mapLayers->Render();
    }
    void Update()
    {
        for (const auto mapLayers : m_MapLayers)
            mapLayers->Update();
    }
    std::vector<Layer*> GetMapLayers() { return m_MapLayers; }
    
private:
    std::vector<Layer*> m_MapLayers;
};

#pragma once
#include <SDL_log.h>
#include <vector>

#include "Layer.h"

class GameMap
{
public:
    void Render()
    {
        for (unsigned int i = 0; i < m_MapLayers.size(); i++)
        {
            m_MapLayers[i]->Render();
        }
    }
    void Update()
    {
        for (unsigned int i = 0; i < m_MapLayers.size(); i++)
            m_MapLayers[i]->Update();
    }
    // Return a reference to the vector, not a copy
    std::vector<Layer*>& GetMapLayers() { return m_MapLayers; }
    
private:
    std::vector<Layer*> m_MapLayers;
};

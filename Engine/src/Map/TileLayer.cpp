#include "TileLayer.h"

#include <iostream>

#include "../Graphics/TextureManager.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tilesets) :
m_TileSize(tileSize), m_RowCount(rowCount), m_ColCount(colCount), m_TileMap(tileMap), m_Tilesets(tilesets)
{
    for (unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "Assets/Maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render()
{
    
    for (unsigned int row = 0; row < m_RowCount; row++)
    {
        for(unsigned int col = 0; col < m_ColCount; col++)
        {
            int tileID = m_TileMap[row][col];

            if (tileID == 0)
                continue;
            
            int index = 0;
            if(m_Tilesets.size() > 1)
                for (unsigned int i = 1; i < m_Tilesets.size(); i++)
                {
                    if (tileID > m_Tilesets[i].FirstID && tileID < m_Tilesets[i].LastID)
                    {
                        tileID = tileID + m_Tilesets[i].TileCount - m_Tilesets[i].LastID;
                        std::cout << " index " << i << "\n";
                        index = i;
                        break;
                    }
                }
            Tileset tileset = m_Tilesets[index];
            int tileRow = tileID / tileset.ColCount;
            int tileCol = tileID % tileset.ColCount;
            
            if(tileID % tileset.ColCount == 0)
            {
                tileRow--;
                tileCol = tileset.ColCount - 1;
            }
            
            TextureManager::GetInstance()->DrawTile(
                tileset.Name,
                tileset.TileSize,
                col * tileset.TileSize,
                row * tileset.TileSize,
                tileRow,
                tileCol
            );
        }
    }
}

void TileLayer::Update()
{
    
}

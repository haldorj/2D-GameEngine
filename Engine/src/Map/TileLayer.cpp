#include "TileLayer.h"

#include <iostream>

#include "../Graphics/TextureManager.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tilesets) :
m_TileSize(tileSize), m_RowCount(rowCount), m_ColCount(colCount), m_TileMap(tileMap), m_Tilesets(tilesets)
{
    for (unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "Assets/Maps/" + m_Tilesets[i].Source);
        std::cout << "Assets/Maps/" << m_Tilesets[i].Source <<"\n";
    }

    for (unsigned int i = 0; i < m_RowCount; i++)
    {
        for (unsigned int j = 0; j < m_ColCount; j++)
        {
            std::cout << m_TileMap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void TileLayer::Render()
{
    for (unsigned int row = 0; row < m_RowCount; row++)
    {
        for (unsigned int col = 0; col < m_ColCount; col++)
        {
            int tileID = m_TileMap[row][col];

            // Skip rendering if tile is empty
            if (tileID == 0)
                continue;
            
            int index = 0;

            // Check if there are multiple tilesets
            if (m_Tilesets.size() > 1)
            {
                // Iterate through tilesets to find the appropriate one for the tile ID
                for (unsigned int i = 1; i < m_Tilesets.size(); i++)
                {
                    if (tileID > m_Tilesets[i].FirstID && tileID < m_Tilesets[i].LastID)
                    {
                        // Adjust tile ID based on the tileset's properties
                        tileID = tileID + m_Tilesets[i].TileCount - m_Tilesets[i].LastID;
                        index = i;
                        break;
                    }
                }
            }

            Tileset tileset = m_Tilesets[index];

            // Calculate tile's row and column in the tileset
            int tileRow = (tileID - 1) / tileset.ColCount;
            int tileCol = (tileID - 1) % tileset.ColCount;
            
            // Handle special case where tileID is a multiple of the tileset's column count
            if (tileID % tileset.ColCount == 0)
            {
                tileRow--;
                tileCol = tileset.ColCount - 1;
            }

            // Render the tile using TextureManager
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

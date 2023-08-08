#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Camera/Camera.h"

#include <SDL_image.h>

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface)
    {
        SDL_Log("Failed to load texture: %s, %s", filePath.c_str(), SDL_GetError());
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (!texture)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();
    SDL_Log("texture map cleared!");
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    glm::vec2 camera = Camera::GetInstance()->GetPosition() * glm::vec2(0.25);
    SDL_Rect dstRect = {x - camera.x, y - camera.y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string id, int tilesize, int x, int y, int row, int col, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tilesize*col, tilesize*(row), tilesize, tilesize};
    glm::vec2 camera = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x - camera.x, y - camera.y, tilesize, tilesize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame,
                               SDL_RendererFlip flip)
{
    glm::vec2 camera = Camera::GetInstance()->GetPosition();
    SDL_Rect srcRect = {width * frame, height * (row-1), width, height};
    SDL_Rect dstRect = {x - camera.x, y - camera.y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

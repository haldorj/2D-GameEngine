#pragma once

#include <SDL.h>
#include <string>
#include <map>

class TextureManager
{
public:
    static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }
    
    bool Load(std::string id, const std::string& filePath);
    void Drop(std::string id);
    void Clean();

    void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE);
private:
    TextureManager() {};
    static TextureManager* s_Instance;
    std::map<std::string, SDL_Texture*> m_TextureMap;
};

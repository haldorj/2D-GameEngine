#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>

#include <string>

class Texture {
public:
    Texture(SDL_Renderer* renderer, const std::string& filePath);
    ~Texture();

    void Render(glm::vec2 pos);
    void Remove();
private:
    bool m_Active = true;

    SDL_Texture* texture;
    SDL_Renderer* renderer;
};



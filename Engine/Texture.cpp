#include "Texture.h"

#include <iostream>

Texture::Texture(SDL_Renderer* renderer, const std::string& filePath) : renderer(renderer), texture(nullptr) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        // Handle error
        std::cout << "surface error";
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        // Handle error
        std::cout << "tex error";
    }
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

void Texture::Render(glm::vec2 pos) 
{
    SDL_Rect destinationRect = { pos.x, pos.y, 0, 0 };
    SDL_QueryTexture(texture, nullptr, nullptr, &destinationRect.w, &destinationRect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &destinationRect);
}
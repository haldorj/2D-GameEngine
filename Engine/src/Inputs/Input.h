#pragma once

#include <SDL.h>

class Input
{
public:
    static Input* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }

    void HandleEvents();
    bool GetKeyDown(SDL_Scancode key);
    
private:
    Input() { m_KeyStates = SDL_GetKeyboardState(nullptr); }
    void KeyUp();
    void KeyDown();

    const Uint8* m_KeyStates;
    static Input* s_Instance;
};

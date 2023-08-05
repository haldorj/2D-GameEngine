#pragma once

#include <iostream>

#include <SDL.h>
#include <glm/glm.hpp>

#include "Systems.h"
#include "Player.h"

#include <vector>

class RenderWindow
{
public:

	RenderWindow();
	RenderWindow(int width, int height);

	void CreateWindow(int width, int height);
	void CreateRenderer();
	void ReadInput();
	void Update();
	void Render();

	~RenderWindow();

private:
	Player* m_Player;

	std::vector<Entity> m_Entities;
	// Create entities and add components
	RenderSystem m_RenderSystem;
	NPCMovementSystem m_NPCMovementSystem;

	bool m_Quit = false;

	SDL_Event m_Event;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	// Default window dimentions
	const static size_t WIDTH = 800;
	const static size_t HEIGHT = 600;
};
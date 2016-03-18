#pragma once

#ifndef _WINDOW_H
#define  _WINDOW_H

#include <SDL.h>
#include <string>
#include <memory>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_framerate.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include <sstream>
#include "Diode.h"

class Window
{
public:
	explicit Window(const float width, const float height, const float framerate);
	void InitSDL(Uint32 flags);
	void CreateMyWindow(const std::string& name_of_window, Uint32 flags);
	void CreateDioder();

	void HandleEvents();
	void Render();
	void Update();
	bool isRunning() noexcept { return running;  }

	~Window();

private:
	float m_width;
	float m_height;

private:
	std::string  m_windowName;
	SDL_Window   *m_window{ nullptr };
	SDL_Renderer* m_renderer;
	SDL_Event evt;
	float fps;
	bool running{ true };
	std::vector< std::shared_ptr<Diode> > m_dioder;
	SDL_Texture *m_image{ nullptr };
};

#endif
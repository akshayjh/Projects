#ifndef _SCREEN_H
#define _SCREEN_H

#include <SDL.h>
#include <Windows.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <functional>   // std::minus
#include <numeric>      // std::accumulate

class Diode
{
public:
	Diode(int posX, int posY, int startX, int startY, std::size_t screenWidth, std::size_t screenHeight);
	~Diode();

	unsigned int Calculate(std::vector <unsigned int> v);
	void Capture(int startX, int startY, int w, int h);
	void Render(SDL_Renderer* renderer);
	void Update();

private:
	std::vector<unsigned int> m_red;
	std::vector<unsigned int> m_green;
	std::vector<unsigned int> m_blue;
};


#endif // _SCREEN_H
#include <vector>
#include <iostream>
#include "Window.h"


// settings
constexpr float window_width{ 1024 };
constexpr float window_height{ 720 };
constexpr float fps{ 20 }; // default is 30 fps


int main(int argc, char *argv[])
{

	Window window{ window_width, window_height, fps};
	FPSmanager* fps_m = new FPSmanager;

	window.InitSDL(SDL_INIT_EVERYTHING);
	window.CreateMyWindow("Ambient Light Prototype", SDL_WINDOW_SHOWN);
	window.CreateDioder();

	SDL_initFramerate(fps_m);
	SDL_setFramerate(fps_m, fps);

	while (window.isRunning())
	{
		window.HandleEvents();
		window.Update();
		window.Render();
	    
		SDL_framerateDelay(fps_m);
	}

	delete fps_m;
	
	return 0;
}
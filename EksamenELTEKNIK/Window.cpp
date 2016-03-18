#include "Window.h"


Window::Window(const float width, const float height, const float framerate)
{
	m_width = width;
	m_height = height;
	fps = framerate;
}

void Window::InitSDL(Uint32 flags)
{
	if (SDL_Init(flags) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"SDL Error!",
			"Error While calling SDL Init: ",
			nullptr);
		running = false;
	}

}


void Window::CreateDioder()
{
	m_dioder.emplace_back(std::make_shared <Diode>(0, 0, 0, 0,100,100));
	//m_dioder.emplace_back(std::make_shared <Diode>(0 , -180, 0, GetSystemMetrics(SM_CYSCREEN) - 100, 100,GetSystemMetrics (SM_CYSCREEN)));
}


void Window::CreateMyWindow(const std::string & name_of_window, Uint32 flags)
{
	SDL_CreateWindowAndRenderer(
		m_width,
		m_height,
		flags,
		&m_window,
		&m_renderer
		);

	if (m_window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"SDL Error!",
			"Error While calling SDL_CreateWindow",
			nullptr);
		running = false;
	}
	m_windowName = name_of_window;

	SDL_SetWindowTitle(m_window, m_windowName.c_str ());
	
	m_image = IMG_LoadTexture(m_renderer, "bg.png");
	SDL_SetTextureBlendMode(m_image, SDL_BLENDMODE_NONE);

	if (m_image == nullptr)
	{
		std::stringstream ss;
		// generate our error message
		ss << "Error: " << IMG_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Loading The bg image",
			ss.str().c_str(),
			nullptr);
		exit(-1);
	}

}

void Window::HandleEvents()
{
	
	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			running = false;
		case SDL_MOUSEBUTTONDOWN:
		{

		}
		case SDL_KEYDOWN:
		{
			
		}
	  }
	}
	
}


void Window::Render()
{
	SDL_Rect info;

	info.x = 0;
	info.y = 0;
	info.w = m_width;
	info.h = m_height;

	SDL_RenderCopy(m_renderer, m_image, nullptr, &info );
	
	for (auto i : m_dioder)
	{
		i->Render(m_renderer);
	}
	
	SDL_RenderPresent(m_renderer);
	SDL_RenderClear(m_renderer);

}	

void Window::Update()
{
	//SDL_SetRenderDrawColor(m_renderer, 45, 35, 35, 255);
	//m_screenL.Capture();
	for (auto i : m_dioder)
	{
		i->Capture(0, 0, 100, 100);
	}


}


Window::~Window()
{

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

#include "Diode.h"


/*
    <Brief>
   >Når en diode bliver lavet startes denne funktion.
   ..................................................
   int startX: pos på x aksen, start pixel koord.
   int startY: pos på y aksen, start pixel koord.
   std::size_t screenWidth: skærments størelse, bredde.
   std::size_t screenHeight: skærments størelse, højde.
*/
Diode::Diode(int posX, int posY, int startX, int startY, std::size_t screenWidth, std::size_t screenHeight)
{
	/* 
	// placer den
	Place(posX, posY, startX, startY, screenWidth, screenHeight);

	// bmp fil struktur
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = m_screenWidth;
	bmi.bmiHeader.biHeight = m_screenHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

		 // ** Handle info **
		 // En handle er en intenger index til en pegepind, eller en resource. Ideen bag en handle type er
		 // at det giver os en type som er abtrakt. Så vi behøver ikke at vide meget om selve typen.

		 // Hent en handle til dekstop vinduet, desktop viduet dækker hele skærmem.
	//hDesktopWnd = GetDesktopWindow();

	// GetDC retunerer en handle enhed for hele vinduet.
	hDesktopDC = GetDC(nullptr);

	// hvis det fejler så retunerer GetDC en nullptr.
	if (hDesktopDC == nullptr)
	{

		MessageBox(nullptr,
			"Error While retrieving a handle to a device context (DC).",
			nullptr,
			MB_OK
			);
		exit(1);
	}

	// Laver en Kompatibel device enhed.
	hCaptureDC = CreateCompatibleDC(hDesktopDC);

	// hvis det fejler så retunerer den en nullptr.
	if (hCaptureDC == nullptr)
	{
		MessageBox(nullptr,
			"Error creating a memory device context (DC) compatible with the specified device.",
			nullptr,
			MB_OK
			);
		exit(1);
	}

	// Laver en bitmap i hukomelsen.
	hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, m_screenWidth, m_screenHeight);

	//hvis det fejler så retunerer den en nullptr
	if (hCaptureDC == nullptr)
	{
		MessageBox(nullptr,
			"Error creating a bitmap compatible with the device that is associated with the specified device context.",
			nullptr,
			MB_OK
			);

		exit(1);
	}

	// Vælg et objekt 
	SelectObject(hCaptureDC, hCaptureBitmap);

	m_pPixels = new RGBQUAD[bmi.bmiHeader.biSizeImage]; // vores kontainer, her skal vores pixels gemmes


	*/
}

/*
<Brief>
>Når en diode bliver ødelagt kaldes denne funktion.
*/

Diode::~Diode()
{
	/*
	// Slet alle unødvendige resourcer.
	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);
	DeleteObject(hCaptureBitmap);
	delete[] m_pPixels;
	*/
}


/*
<Brief>
>Placer en diode på skærmen.
..................................................
int startX: pos på x aksen, start pixel koord.
int startY: pos på y aksen, start pixel koord.
std::size_t screenWidth: skærments størelse, bredde.
std::size_t screenHeight: skærments størelse, højde.
*/

/* 
void Diode::Place(int posX, int posY, int startX, int startY, std::size_t screenWidth, std::size_t screenHeight)
{
	// Alle de nye værdier updateres.
	m_x = startX;
	m_y = startY;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_pos_x = posX;
	m_pos_y = posY;
}

*/


/*
<Brief>
> Tag et billede af skærmen og gem alle pixels i kontaineren: m_pPixels.
*/

// TODO make it faster! read a big chuch of memory! 
void Diode::Capture(int startX, int startY, int w, int h)
{
	HDC hdcScreen = GetDC(nullptr);

	m_red.clear();
	m_green.clear();
	m_blue.clear();

	for (int x = startX, y = startY;;)
	{

		COLORREF pixel = GetPixel(hdcScreen, x, y);

		assert(pixel != CLR_INVALID);

		m_red.push_back(GetRValue(pixel));
		m_green.push_back(GetGValue(pixel));
		m_blue.push_back(GetBValue(pixel));


		if (x < w) x++;
		if (y < h) y++;

		if (x == w && y == h) break;
	}



	/*

	// Hent bits fra området m_screenHeight, hDesktopDC.
	 BitBlt(hCaptureDC, 0, 0, m_screenWidth, m_screenHeight, hDesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);

	// tag billede af det og gem det i m_pPixels.
	GetDIBits(hCaptureDC,
		hCaptureBitmap,
		0,				  // starting scanline
		m_screenHeight,	  // scanlines to copy
		m_pPixels,        // buffer for your copy of the pixels
		&bmi,			  // format you want the data in
		DIB_RGB_COLORS);  // actual pixels, not palette references

		*/
}


unsigned int Diode::Calculate( std::vector <unsigned int> v)
{
	std::cout << "inside!" << std::endl;
	unsigned int sum = std::accumulate(std::begin(v), std::end(v), 0.0);
	return (sum / v.size ());
}


/*
<Brief>
> Render alle pixels ud på skærmen.
*/
void Diode::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, (Uint8)Calculate(m_red), (Uint8)Calculate(m_green), (Uint8)Calculate(m_blue), 255);

	//std::cout << "RED: " << (Uint8)Calculate(m_red) << " GREEN: " << (Uint8)Calculate(m_green) << "BLUE: " << (Uint8)Calculate(m_blue) << std::endl;

	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}


	/*
	for (int y = m_y; y < m_screenHeight; y++)
	{
		for (int x = m_x; x < m_screenWidth; x++)
		{
			int p = (m_screenHeight - y - 1) * m_screenWidth + x; // upside down

			unsigned char r = m_pPixels[p].rgbBlue;
			unsigned char g = m_pPixels[p].rgbGreen;
			unsigned char b = m_pPixels[p].rgbRed;

			SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
			SDL_RenderDrawPoint(renderer, x+ m_pos_x, y + m_pos_y );

		}
	}

	*/
}

void Diode::Update()
{

}

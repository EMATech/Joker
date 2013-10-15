#include <QtGlobal>

#include <SDL2/SDL.h>
#if defined(Q_OS_MAC)
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif


#include <string>
#include <cstring>
#include "string.h"
#include "iostream"
//#include "SDLMain.h"

#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QApplication>
#include <QTime>


#include "PhTools/PhDebug.h"

//Screen attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 780;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *image = NULL;
SDL_Surface *foo = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;

//The event
SDL_Event event;

using namespace std;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	QTime t;

	//PHDEBUG << "SDL_Init()";
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return false;

	//PHDEBUG << "SDL_SetVideoMode";
	//Set up the screen

	SDL_Window * window = SDL_CreateWindow("SDLTest", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_SWSURFACE);

	screen = SDL_GetWindowSurface(window);

	//PHDEBUG << "SDL_WM_SetCaption";

	//	PHDEBUG << "current path : " << QApplication::applicationDirPath();
	string ressourcesPath = QApplication::applicationDirPath().toStdString();
	//	PHDEBUG << "load_image";
	// Create a surface from picture:
	string lookPath = ressourcesPath + "/look.png";
	image = IMG_Load( lookPath.c_str());

	if( image == NULL )
	{
		return 1;
	}

	// Display the picture:
	SDL_Rect imageRect = {0, 0, image->w, image->h};

	//SDL_BlitSurface( image, NULL, screen, &imageRect );

	// Initialize TTF :
	if( TTF_Init() == -1 ) {
		PHDEBUG << "TTF error.";
		return 2;
	}

	//Create a font
	string fontPath = ressourcesPath + "/Bedizen.ttf";
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), 150 );
	if (font == NULL)
		return 3;

	//Font's color
	SDL_Color color={255,255,255};
	Uint16 ch;
#define TEST  2

#if TEST == 0
	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, "ABCDEFGHIJKL", textColor );
	SDL_Rect textRect = {0, 100, surface->w, surface->h};
	SDL_BlitSurface( surface, NULL, screen, &textRect);

#elif TEST == 1

	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;


	ch = 65;
	SDL_Surface * glyph = SDL_CreateRGBSurface(0,screen->w,screen->h,32,rmask,gmask,bmask,amask);
	SDL_Surface * car = TTF_RenderGlyph_Blended(font,ch,color);

	SDL_Rect glyphRect = {0, 0, 100, 100};
	SDL_Rect carRect = {100, 0, 300, 300};

	PHDEBUG << SDL_BlitSurface(car, NULL, glyph, &glyphRect);
	PHDEBUG << SDL_BlitSurface(glyph, NULL, screen, &glyphRect);


#elif TEST == 2

	// used to place the glyph on the surface
	int nbPixelX = 0;
	int nbPixelY = 0;

	// used to set the base surface
	Uint32 rmask, gmask, bmask, amask;
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;

	// Creation of the glyph surface
	SDL_Surface * glyph = SDL_CreateRGBSurface(0,2048,2048,32,rmask,gmask,bmask,amask);
	SDL_Rect glyphRect = {0, 0, 2048, 2048};

	// store the widht of each glyph
	int tab[255];

	for(ch = 1; ch <= 256; ++ch)
	{
		SDL_Surface * car = TTF_RenderGlyph_Blended(font,ch,color);
		SDL_Rect carRect = {nbPixelX, nbPixelY, car->w, car->h};
		if(SDL_BlitSurface( car, NULL, glyph, &carRect ))
			PHDEBUG << SDL_GetError();
		if (ch % 16 == 0)
		{
			nbPixelX = 0;
			nbPixelY += 128;
		}
		else
			nbPixelX += 128;
		int minx, maxx;
		if(TTF_GlyphIsProvided(font, ch)){
			TTF_GlyphMetrics(font, ch, &minx,&maxx, NULL, NULL, NULL );
			tab[ch - 1] = maxx-minx ;
		}
		else
			tab[ch - 1] = 0;
	}

	//This draw the entire glyph
	SDL_BlitSurface(glyph, NULL, screen, &glyphRect);



#endif




	//Update the screen
	if( SDL_UpdateWindowSurface(window))
		return -1;

	int ret = a.exec();

	//Free the surface and quit SDL
	SDL_FreeSurface( image );
	SDL_FreeSurface(message);
	SDL_FreeSurface(screen);

	//Quit SDL
	TTF_CloseFont( font );
	TTF_Quit();
	SDL_Quit();

	return ret;
}



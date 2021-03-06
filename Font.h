#ifndef __FONT__
#define __FONT__

#include "SDL.h"
#include "SDL_ttf.h"
#include "Canvas.h"

class Font {
public:
        static Font* GetInstance();
	void FontInit(const char* face, Uint32 size);
	~Font();

public:
	void DrawTextSolid(const Uint16* text, Uint32 color, SDL_Surface* dst_sur, Uint32 x, Uint32 y);
	void DrawTextShaded(const Uint16* text, Uint32 color, Uint32 shadowColor, SDL_Surface* dst_sur, Uint32 x, Uint32 y);
	void DrawTextBlended(const Uint16* text, Uint32 color, SDL_Surface* dst_sur, Uint32 x, Uint32 y);
	void GetTextSize(const Uint16* text, Uint32 &height, Uint32 &width);

	Canvas* createTextSurface(const Uint16* text, Uint32 color);

	static SDL_Color Conv2SDLcolor(Uint32 color);

private:
	Font();
	TTF_Font *font;
	static Uint32 refCount;
};

#endif

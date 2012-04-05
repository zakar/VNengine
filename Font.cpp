#include "Font.h"
#include "Canvas.h"
#include "Exception.h"

Uint32 Font::refCount = 0;

Font* Font::GetInstance()
{
  static Font* instance = new Font();
  return instance;
}

void Font::FontInit(const char* face, Uint32 size)
{
  font = TTF_OpenFont(face, size);  
  if (font == 0)
    throw Exception(SDL_GetError());

}

Font::Font() {
	if (!refCount) {
		if ( TTF_Init() < 0 )
			throw Exception("TTF_Init() failed!");
	}

	if (++refCount > 1) 
	  throw Exception("Mutiply Font instance");
}

Font::~Font(){
	TTF_CloseFont(font);
	font = NULL;
	if (--refCount==0) {
		TTF_Quit();
	}
}

void Font::DrawTextSolid( const Uint16* text, Uint32 color, SDL_Surface* dst_sur, Uint32 x, Uint32 y ) {
	SDL_Surface *sur;
	sur = TTF_RenderUNICODE_Solid(font, text, Conv2SDLcolor(color));
	if (sur == 0) 
		throw Exception("Failed Drawing Text Solid");

	SDL_Rect src, dst;
	src.x = src.y = 0;
	src.w = sur->w;
	src.h = sur->h;

	dst.x = x;
	dst.y = y;
	dst.w = sur->w;
	dst.h = sur->h;
	
	SDL_BlitSurface(sur, &src, dst_sur, &dst);

	SDL_FreeSurface(sur);
}

void Font::DrawTextShaded( const Uint16* text, Uint32 color, Uint32 shadowColor, SDL_Surface * dst_sur, Uint32 x, Uint32 y ) {
	SDL_Surface *sur;
	sur = TTF_RenderUNICODE_Shaded(font, text, Conv2SDLcolor(color), Conv2SDLcolor(shadowColor));
	if (sur == 0) 
		throw Exception("Failed Drawing Text Shaded");

	SDL_Rect src, dst;
	src.x = src.y = 0;
	src.w = sur->w;
	src.h = sur->h;

	dst.x = x;
	dst.y = y;
	dst.w = sur->w;
	dst.h = sur->h;

	SDL_BlitSurface(sur, &src, dst_sur, &dst);

	SDL_FreeSurface(sur);
}

void Font::DrawTextBlended( const Uint16* text, Uint32 color, SDL_Surface* dst_sur, Uint32 x, Uint32 y ) {
	SDL_Surface *sur;
	sur = TTF_RenderUNICODE_Blended(font, text, Conv2SDLcolor(color));
	if (sur == 0) {
	  throw Exception("Failed Drawing Text Blended");
	}

	SDL_Rect src, dst;
	src.x = src.y = 0;
	src.w = sur->w;
	src.h = sur->h;

	dst.x = x;
	dst.y = y;
	dst.w = sur->w;
	dst.h = sur->h;

	SDL_BlitSurface(sur, &src, dst_sur, &dst);

	SDL_FreeSurface(sur);
}

void Font::GetTextSize( const Uint16* text, Uint32 &height, Uint32 &width ) {
        SDL_Color color = {0};
	SDL_Surface *sur = TTF_RenderUNICODE_Blended(font, text, color);
	if (sur == 0) 
	  throw Exception("Failed Calc Text Size");
	height = sur->h;
	width  = sur->w;
	SDL_FreeSurface(sur);
}

SDL_Color Font::Conv2SDLcolor(Uint32 color) {
  SDL_Color sdl_color;
  sdl_color.r = Uint8((color & RMASK) >> RSHIFT);
  sdl_color.g = Uint8((color & GMASK) >> GSHIFT);
  sdl_color.b = Uint8((color & BMASK) >> BSHIFT);
  return sdl_color;
}

Canvas* Font::createTextSurface(const Uint16* text, Uint32 color)
{ 
  Uint32 h, w;
  GetTextSize(text, h, w);
  Canvas *sur = new Canvas;
  sur->LoadRaw(w, h);
  sur->clip.x = 0;
  sur->clip.y = 0;
  sur->clip.w = w;
  sur->clip.h = h;
  sur->ColorRect(0x00000000);
  DrawTextBlended(text, color, sur->surface, 0, 0);
  return sur;
}

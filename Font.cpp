#include "Font.h"
#include "Canvas.h"
#include "Exception.h"

Uint32 Font::refCount = 0;

Font::Font( const char* face, Uint32 size ) {
	if (!refCount) {
		if ( TTF_Init() < 0 )
			throw Exception("TTF_Init() failed!");
	}

	font = TTF_OpenFont(face, size);
	if (font == 0)
		throw Exception(SDL_GetError());
	++refCount;
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
	static SDL_Color color;
	SDL_Surface * sur = TTF_RenderUNICODE_Shaded(font, text, color, color);
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

SDL_Surface* Font::createTextSurface(const Uint16* text, Uint32 color)
{ 
  SDL_Surface *sur = NULL, *dst_sur = NULL;
  sur = TTF_RenderUNICODE_Solid(font, text, Conv2SDLcolor(color));
  if (sur == NULL) 
    throw Exception("Failed Drawing Text Solid");

  return sur;
  // Canvas::NewSurface(dst_sur, sur->w, sur->h, 0xffffffff);

  // SDL_Rect src, dst;
  // src.x = src.y = 0;
  // src.w = sur->w;
  // src.h = sur->h;
  
  // dst.x = 0;
  // dst.y = 0;
  // dst.w = sur->w;
  // dst.h = sur->h;
  
  // SDL_BlitSurface(sur, &src, dst_sur, &dst);
  
  // SDL_FreeSurface(sur);
  
  // return dst_sur;
}

#ifndef  __CANVAS__
#define  __CANVAS__

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#define BPP 32
#define RMASK 0x00ff0000
#define GMASK 0x0000ff00
#define BMASK 0x000000ff
#define AMASK 0xff000000
#define RSHIFT 16
#define GSHIFT 8
#define BSHIFT 0
#define ASHIFT 24
#define RBMASK 0x00ff00ff
#define RGBMASK 0x00ffffff
#define DEFAULT_SURFACE_FLAG SDL_SWSURFACE

#define DISABLE_ALPHA 0xffffffff
#define DISABLE_COLORKEY 0x00ffffff

class Canvas
{
 public:
  Canvas();
  Canvas(Canvas* cav);
  virtual ~Canvas();

 public:	 
  static bool ClipSurface(SDL_Rect &dst, SDL_Rect clip);
  static void BlendSurface(SDL_Surface *surface, SDL_Surface *dst, Uint32 dst_x, Uint32 dst_y, SDL_Rect clip, Uint32 global_alpha, Uint32 color_key);
  static void ColorRect(SDL_Surface *surface, Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 color);

 public:
  void LoadRaw(Uint32 width, Uint32 height);
  void LoadImage(const char* fileName);
  void ColorRect(Uint32 color);
  void BlendSurface(SDL_Surface *dst);

 public:
  void* operator new(size_t s);
  void operator delete(void* addr);
    
 public: 
  Uint32 color_key;
  Uint32 global_alpha;
  Uint32 dst_x, dst_y;
  SDL_Rect clip;

  SDL_Surface *surface;
  std::string cached_name;
};

#endif

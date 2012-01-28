#ifndef __SCREENLAYER__
#define __SCREENLAYER__

#include "SDL/SDL.h"
#include "Canvas.h"
#include <queue>
#include <vector>

class ScreenLayer
{
 public:
  static ScreenLayer* GetInstance();
  void SetWindowMode(Uint32 width, Uint32 height, bool fullScreen = false, int bpp=32);
  void SetTitle(const char* title);
  void Release();
  Uint32 getWidth();
  Uint32 getHeight();

 public:
  void AddCanvas(Canvas* obj);
  void FlushCanvas();

 public:
  SDL_Surface *screen;
  Uint32 width, height;
  
 public: //与全局屏幕相关的数据
  Canvas mix_canvas;

 private:
  std::queue<Canvas*> Canvas2blit;
  
 private:
  ScreenLayer();
  void operator=(ScreenLayer&);
};

inline Uint32 getWidth() { return width; }
inline Uint32 getHeight() { return height; }

#endif

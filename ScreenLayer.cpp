#include "ScreenLayer.h"
#include "Exception.h"
#include "Canvas.h"

ScreenLayer::ScreenLayer() {
  screen = NULL;
}

ScreenLayer* ScreenLayer::GetInstance() {
	static ScreenLayer instance;
	return &instance;
}

void ScreenLayer::SetWindowMode( Uint32 width, Uint32 height, bool fullScreen, int bpp) {

	if (screen) {
	  SDL_FreeSurface(screen);
	  screen = NULL;
	}

	screen = SDL_SetVideoMode(width, height, bpp, DEFAULT_SURFACE_FLAG | (fullScreen ? SDL_FULLSCREEN : 0));
	if (screen == NULL) {
	  throw(Exception("窗口设定失败!"));
	}

	mix_canvas.NewSurface(width, height, 0xff000000);
	mix_canvas.global_alpha = DISABLE_ALPHA;
	mix_canvas.color_key = DISABLE_COLORKEY;
	mix_canvas.dst_x = 0;
	mix_canvas.dst_y = 0;
	mix_canvas.clip.x = 0;
	mix_canvas.clip.y = 0;
	mix_canvas.clip.w = width;
	mix_canvas.clip.h = height;

	this->width = width;
	this->height = height;
}

void ScreenLayer::Release() {
	if (screen) {
	  SDL_FreeSurface(screen);
	  screen = NULL;
	}
}

void ScreenLayer::SetTitle( const char* title ) {
	SDL_WM_SetCaption(title, NULL);
}


void ScreenLayer::AddCanvas(Canvas* obj) 
{
  Canvas2blit.push(obj);
}

void ScreenLayer::FlushCanvas() 
{
  mix_canvas.ColorRect(0xff000000);
  
  for (Canvas *obj; !Canvas2blit.empty(); Canvas2blit.pop()) {
    obj = Canvas2blit.front();
    obj->BlendSurface(mix_canvas.surface);
  }

  mix_canvas.BlendSurface(screen);
  SDL_Flip(screen);
}

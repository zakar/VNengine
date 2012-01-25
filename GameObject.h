#ifndef  __GAMEOBJECT__
#define  __GAMEOBJECT__

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "LuaObject.h"
#include "Canvas.h"
#include <string>

class GameObject
{
 public:
  GameObject(int ref);
  virtual ~GameObject();

 public:
  virtual void OnFrame();
  virtual void OnKeyDown(SDLKey key);
  virtual void OnKeyUp(SDLKey key);
  virtual void OnMouseDown(Uint16 x, Uint16 y, Uint8 button);
  virtual void OnMouseUp(Uint16 x, Uint16 y, Uint8 button);
  virtual void OnMouseMove(Uint16 x, Uint16 y);
  
 public:
  Canvas* get_canvas() { return canvas; }

 public:
  LuaObject handler;
  Canvas *canvas;
};

#endif

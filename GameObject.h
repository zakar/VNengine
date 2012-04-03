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
  
  //Canvas wrapper
 public:
  bool doClip(SDL_Rect &dst);

  enum { FLIP = 0, SET, UNSET };
  int checkVisible();
  void setVisible(int flag, int mask);
  Canvas *canvas2Render(const SDL_Rect &dst);
  
 public:
  LuaObject handler;
  Canvas *canvas;
  int visiable;
};

#endif

#ifndef __SPIRTE__
#define __SPIRTE__

#include "Canvas.h"
#include "GameObject.h"
#include "LuaObject.h"
#include <string>

class Sprite : public GameObject
{
 public:
  Sprite(int ref);
  static Sprite* create(int ref);
  virtual ~Sprite();

 public:
  void OnFrame();
  void OnKeyDown(SDLKey key);
  void OnKeyUp(SDLKey key);
  void OnMouseDown(Uint16 x, Uint16 y, Uint8 button);
  void OnMouseUp(Uint16 x, Uint16 y, Uint8 button);
  void OnMouseMove(Uint16 x, Uint16 y);
};

#endif

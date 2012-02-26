#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__

#include "SDL/SDL.h"
#include "GameObject.h"
#include "Exception.h"
#include <vector>
#include <map>
#include <string>

class EventHandler
{
 public:
  static EventHandler* GetInstance();
  void initL(lua_State *L);

 public:
  void OnFrame();
  void OnScript();
  void OnNetwork();
  void OnKeyDown(SDLKey key);
  void OnKeyUp(SDLKey key);
  void OnMouseDown(Uint16 x, Uint16 y, Uint8 button);
  void OnMouseUp(Uint16 x, Uint16 y, Uint8 button);
  void OnMouseMove(Uint16 x, Uint16 y);

 private:
  lua_State *L;
};

#endif


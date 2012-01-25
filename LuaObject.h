#ifndef __LUAOBJECT__
#define __LUAOBJECT__

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

#include "SDL/SDL.h"
#include <string>

class LuaObject
{
 public:
  LuaObject(int ref);
  ~LuaObject();
  static void initL(lua_State *L);
  void LoadClip(SDL_Rect &clip);
  void LoadLocation(Uint32 &x, Uint32 &y);
  void LoadGlobalAlpha(Uint32 &alpha);
  void LoadColorKey(Uint32 &color);
  void LoadImgName(std::string &img);
  void LoadAttribute(std::string &attr);
  void LoadWordLayer(std::string &imgName, Uint32 &width, Uint32 &height, Uint32 &BoxColor, Uint32 &TextColor, \
		     Uint32 &WLoffX, Uint32 &WLoffY, Uint32 &WLwidth, Uint32 &WLheight, \
		     std::string &fontName, Uint32 &fontSize);
  
  int ExecOnMouseRange(Uint32 x, Uint32 y);

  void registerAPI(const std::string &obj);

 public:
  static int GetFrameInterval(Uint32 last_ti);

 private:
  static lua_State *L;
  int ref;
};

#endif

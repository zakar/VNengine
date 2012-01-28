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
  void LoadClip(SDL_Rect &clip, const char* cmd);
  void LoadLocation(Uint32 &x, Uint32 &y, const char* cmd);
  void LoadGlobalAlpha(Uint32 &alpha, const char* cmd);
  void LoadColorKey(Uint32 &color, const char* cmd);
  void LoadImgName(std::string &img, const char* cmd);
  void LoadAttribute(std::string &attr, const char* cmd);
  void LoadWordLayer(std::string &imgName, Uint32 &width, Uint32 &height, Uint32 &BoxColor, Uint32 &TextColor, \
		     Uint32 &WLoffX, Uint32 &WLoffY, Uint32 &WLwidth, Uint32 &WLheight, \
		     std::string &fontName, Uint32 &fontSize, const char* cmd);
  void LoadFrameTime(Uint32 &ti, const char* cmd);
  
  int ExecOnMouseRange(Uint32 x, Uint32 y, const char* cmd);

  void registerAPI(const std::string &obj);

 private:
  static lua_State *L;
  int ref;
};

#endif

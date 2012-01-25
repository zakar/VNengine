#ifndef __TEXTBOXLUAAPI__
#define __TEXTBOXLUAAPI__

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

namespace TextBoxLuaAPI {
  void luaopen_textboxapi(lua_State *L, int ref);
}

#endif

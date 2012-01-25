#ifndef __GAMESYSTEMLUAAPI__
#define __GAMESYSTEMLUAAPI__

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

namespace GameSystemLuaAPI {
  void luaopen_gamesystem(lua_State *L);
}

#endif

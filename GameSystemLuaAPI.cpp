#include "GameSystemLuaAPI.h"
#include "GameSystem.h"

static int resetScriptEvent(lua_State *L) {
  int ti = lua_tointeger(L, 1);
  GameSystem::resetTimer(ti, SCRIPT_EVENT);
  return 0;
}

static const luaL_Reg gamesystemFunc[] = {
  {"resetScriptEvent", resetScriptEvent},
  {NULL, NULL}
};

void GameSystemLuaAPI::luaopen_gamesystem(lua_State *L) {
  lua_getglobal(L, "TimerFunc");
  luaL_register(L, NULL, gamesystemFunc);
  lua_settop(L, 0);
}

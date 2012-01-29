#include "SceneManager.h"
#include "SceneManagerLuaAPI.h"

static void stackDump (lua_State *L) { 
  int i; 
  int top = lua_gettop(L); 
  for (i = 1; i <= top; i++) {  /* repeat for each level */ 
    int t = lua_type(L, i); 
    switch (t) { 
      
    case LUA_TSTRING:  /* strings */ 
      printf("`%s'", lua_tostring(L, i)); 
      break; 
      
    case LUA_TBOOLEAN:  /* booleans */ 
      printf(lua_toboolean(L, i) ? "true" : "false"); 
      break; 
      
    case LUA_TNUMBER:  /* numbers */ 
      printf("%g", lua_tonumber(L, i)); 
      break; 
      
    default:  /* other values */ 
      printf("%s", lua_typename(L, t)); 
      break; 
      
    } 
    printf("  ");  /* put a separator */ 
  } 
  printf("\n");   /* end the listing */
}

static int insert(lua_State *L) {
  lua_pushvalue(L, 2);
  lua_pushvalue(L, 3);
  lua_settable(L, 1);
  luaL_getmetatable(L, "SceneMetatable");
  lua_setmetatable(L, 3);

  lua_pushvalue(L, 3);
  int ref = luaL_ref(L, LUA_REGISTRYINDEX);
  SceneNode *cur = new SceneNode(ref);
  lua_pushlightuserdata(L, (void*)cur);
  lua_rawseti(L, 3, 0);
  lua_rawgeti(L, 1, 0);
  SceneNode* fa = (SceneNode*)lua_touserdata(L, -1);

  SceneManager::GetInstance()->Insert(fa, cur);
  
  return 0;
}

static int remove(lua_State *L) {

  // lua_rawgeti(L, 1, 0);
  // SceneNode *cur = (SceneNode*)lua_touserdata(L, -1);
  // SceneManager::GetInstance()->Remove(cur);
  

  lua_pushvalue(L, 2);
  lua_gettable(L, 1);
  lua_rawgeti(L, 3, 0);
  SceneNode* cur = (SceneNode*)lua_touserdata(L, -1);
  SceneManager::GetInstance()->Remove(cur);
  lua_settop(L, 2);
  lua_pushnil(L);
  lua_settable(L, 1);
  
  return 0;
}

static int update(lua_State *L) {
  lua_setfield(L, 1, "data");
  lua_rawgeti(L, 1, 0);

  return 0;
}

static const luaL_Reg scene_func[] = {
  {"insert", insert}, 
  {"remove", remove},
  {"update", update},
  {NULL, NULL}
};

static int create(lua_State *L) {
  lua_newtable(L);
  luaL_getmetatable(L, "SceneMetatable");
  lua_setmetatable(L, 1);

  lua_pushvalue(L, 1);
  int ref = luaL_ref(L, LUA_REGISTRYINDEX);

  SceneNode *cur = new SceneNode(ref);
  lua_pushlightuserdata(L, (void*)cur);
  lua_rawseti(L, 1, 0);
  SceneManager::GetInstance()->SetRoot(cur);
 
  return 1;
}

static const luaL_Reg scene_manager_func[] = {
  {"create", create},
  {NULL, NULL}
};

void SceneManagerLuaAPI::luaopen_scene(lua_State *L) {
  luaL_newmetatable(L, "SceneMetatable");
  lua_newtable(L);
  luaL_register(L, NULL, scene_func);
  lua_setfield(L, 1, "__index");
  lua_pop(L, 1);
  
  lua_newtable(L);
  luaL_register(L, NULL, scene_manager_func);
  lua_setglobal(L, "SceneManager");

  lua_settop(L, 0);
}


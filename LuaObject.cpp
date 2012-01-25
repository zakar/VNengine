#include "LuaObject.h"
#include "TextBoxLuaAPI.h"
#include <string>
#include <assert.h>

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

lua_State* LuaObject::L = NULL;

LuaObject::LuaObject(int ref) {
  this->ref = ref;
}

LuaObject::~LuaObject() {
}

void LuaObject::initL(lua_State *L) {
  LuaObject::L = lua_newthread(L);
}

void LuaObject::LoadClip(SDL_Rect &clip) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "clip");

  if (lua_isfunction(L, 3)) {
    if (lua_pcall(L, 0, 1, 0))
      puts("cha, the script is Invalid");
  }

  assert( lua_istable(L, 3) );

  lua_getfield(L, 3, "x");
  clip.x = lua_tointeger(L, -1);
  lua_getfield(L, 3, "y");
  clip.y = lua_tointeger(L, -1);
  lua_getfield(L, 3, "w");
  clip.w = lua_tointeger(L, -1);
  lua_getfield(L, 3, "h");
  clip.h = lua_tointeger(L, -1);

  lua_settop(L, 0);
}

void LuaObject::LoadLocation(Uint32 &x, Uint32 &y) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "location");

  if (lua_isfunction(L, 3)) {
    if (lua_pcall(L, 0, 1, 0))
      puts("cha, the script is Invalid");
  }

  assert( lua_istable(L, 3) );

  lua_getfield(L, 3, "x");
  x = lua_tointeger(L, -1);
  lua_getfield(L, 3, "y");
  y = lua_tointeger(L, -1);

  lua_settop(L, 0);
}

void LuaObject::LoadGlobalAlpha(Uint32 &alpha) {
  alpha = 255;
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "global_alpha");

  if (lua_isnil(L, 3)) {
    lua_settop(L, 0);
    return;
  }

  if (lua_isfunction(L, 3)) {
    if (lua_pcall(L, 0, 1, 0))
      puts("cha, the script is Invalid");
  }

  assert( lua_isnumber(L, 3) );

  alpha = lua_tointeger(L, 3);

  lua_settop(L, 0);
}

void LuaObject::LoadColorKey(Uint32 &color) {
  color = -1;
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "color_key");

  if (lua_isnil(L, 3)) {
    lua_settop(L, 0);
    return;
  }

  if (lua_isfunction(L, 3)) {
    if (lua_pcall(L, 0, 1, 0))
      puts("cha, the script is Invalid");
  }

  assert( lua_isnumber(L, 3) );
  
  color = lua_tointeger(L, 3);

  lua_settop(L, 0);
}

void LuaObject::LoadAttribute(std::string &attr) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "attribute");

  assert( lua_isstring(L, 3) );

  attr = lua_tostring(L, 3);

  lua_settop(L, 0);
}

void LuaObject::LoadImgName(std::string &img) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "img");

  assert( lua_isstring(L, 3) );

  img = lua_tostring(L, 3);

  lua_settop(L, 0);
}

int LuaObject::GetFrameInterval(Uint32 last_ti) {
  lua_getglobal(L, "SceneFunc");
  lua_getfield(L, 1, "GetNextFrameTime");
  lua_getglobal(L, "Scene");
  lua_pushinteger(L, last_ti);
  
  if (lua_pcall(L, 2, 1, 0)) 
    puts("cha, the script is Invalid");

  assert( lua_isnumber(L, 2) );

  int ti = lua_tointeger(L, 2);

  lua_settop(L, 0);
  return ti;
}

int LuaObject::ExecOnMouseRange(Uint32 x, Uint32 y) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "OnMouseRange");
  
  assert( lua_isfunction(L, 3) );

  lua_pushinteger(L, (int)x);
  lua_pushinteger(L, (int)y);
  
  if (lua_pcall(L, 2, 1, 0))
    puts("cha, the script is Invalid");

  assert( lua_isboolean(L, 3) );

  int tmp = lua_toboolean(L, 3);

  lua_settop(L, 0);

  return tmp;
}

void LuaObject::LoadWordLayer(std::string &imgName, Uint32 &width, Uint32 &height, Uint32 &BoxColor, Uint32 &TextColor, \
		   Uint32 &WLoffX, Uint32 &WLoffY, Uint32 &WLwidth, Uint32 &WLheight, \
		   std::string &fontName, Uint32 &fontSize)
{
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, 1, "data");
  lua_getfield(L, 2, "wordlayer");

  lua_getfield(L, 3, "font_name");
  fontName = lua_tostring(L, -1);
  lua_settop(L, 3);

  lua_getfield(L, 3, "font_size");
  fontSize = lua_tointeger(L, -1);
  lua_settop(L, 3);

  lua_getfield(L, 3, "box");
  if (lua_istable(L, -1)) {
    lua_getfield(L, 4, "width");
    width = lua_tointeger(L, -1);
    lua_getfield(L, 4, "height");
    height = lua_tointeger(L, -1);
    lua_getfield(L, 4, "color");
    BoxColor = lua_tointeger(L, -1);
    imgName.clear();
  } else 
    imgName = lua_tostring(L, 4);
  lua_settop(L, 3);

  lua_getfield(L, 3, "x");
  WLoffX = lua_tointeger(L, -1);
  lua_settop(L, 3);

  lua_getfield(L, 3, "y");
  WLoffY = lua_tointeger(L, -1);
  lua_settop(L, 3);

  lua_getfield(L, 3, "width");
  WLwidth = lua_tointeger(L, -1);
  lua_settop(L, 3);
  
  lua_getfield(L, 3, "height");
  WLheight = lua_tointeger(L, -1);
  lua_settop(L, 3);

  lua_getfield(L, 3, "text_color");
  TextColor = lua_tointeger(L, -1);
  
  lua_settop(L, 0);
}

void LuaObject::registerAPI(const std::string &obj) {
  if (obj == "textbox")
    TextBoxLuaAPI::luaopen_textboxapi(L, ref);
}

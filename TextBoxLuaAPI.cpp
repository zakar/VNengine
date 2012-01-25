#include "TextBoxLuaAPI.h"
#include "TextBox.h"
#include "Helper.h"
#include "SceneNode.h"

static int SendText(lua_State *L) {
  const char* str = lua_tostring(L, 2);
  std::basic_string<Uint16> text = Helper::GetUTF16(str);
  
  lua_rawgeti(L, 1, 0);
  SceneNode *node = static_cast<SceneNode*>(lua_touserdata(L, 3));
  TextBox *pt = dynamic_cast<TextBox*>(node->obj);

  pt->SetWordsToRender(text);
  pt->SetPerformState(TextBox::running);
  
  return 0;
}

static const luaL_Reg textFunc[] = {
  {"sendtext", SendText},
  {NULL, NULL}
};

void TextBoxLuaAPI::luaopen_textboxapi(lua_State *L, int ref) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getmetatable(L, 1);
  lua_getfield(L, 2, "__index");
  luaL_register(L, NULL, textFunc);
  
  lua_getglobal(L, "TextFunc");
  lua_getfield(L, 4, "text");
  lua_setfield(L, 3, "text");

  lua_settop(L, 0);
}

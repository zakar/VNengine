#include "EventHandler.h"
#include "GameSystem.h"
#include "ScreenLayer.h"
#include "SceneManager.h"
#include "LuaObject.h"

EventHandler* EventHandler::GetInstance() {
  static EventHandler instance;
  return &instance;
}

void EventHandler::initL(lua_State *L) {
  this->L = lua_newthread(L);
}

void EventHandler::OnFrame() {
  SceneManager::GetInstance()->checkActiveObject();
  SceneManager::GetInstance()->drawDirtyRect();
  ScreenLayer::GetInstance()->FlushCanvas();
}

void EventHandler::OnScript() {
  lua_getglobal(L, "Script");
  if (lua_pcall(L, 0, 0, 0)) 
    throw Exception("cha, Script is corrupt");
  lua_settop(L, 0);
}

void EventHandler::OnNetwork() {
  lua_getglobal(L, "Server");
  if (lua_pcall(L, 0, 0, 0))
    throw Exception("cha, Script is corrupt");
  lua_settop(L, 0);
  GameSystem::resetTimer(1, NETWORK_EVENT);
}

void EventHandler::OnKeyDown(SDLKey key) {
}

void EventHandler::OnKeyUp(SDLKey key) {
}

void EventHandler::OnMouseDown(Uint16 x, Uint16 y, Uint8 button) {
  std::vector<GameObject*> obj = SceneManager::GetInstance()->GetObjects();

  for (int ti, i = 0; i < obj.size(); ++i)
    obj[i]->OnMouseDown(x, y, button);
}

void EventHandler::OnMouseUp(Uint16 x, Uint16 y, Uint8 button) {
}

void EventHandler::OnMouseMove(Uint16 x, Uint16 y) {
}



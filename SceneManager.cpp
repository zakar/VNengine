#include "SceneManager.h"
#include "EventHandler.h"
#include "GameSystem.h"

#include "Sprite.h"
#include "TextBox.h"

SceneManager::SceneManager() {
  
}

SceneManager::~SceneManager() {

}

SceneManager* SceneManager::GetInstance() {
  static SceneManager instance;
  return &instance;
}

void SceneManager::clear(SceneNode *cur) {
  if (cur == NULL) return;

  for (std::vector<SceneNode*>::iterator it = cur->son.begin(); it != cur->son.end(); ++it)
    clear(*it);

  delete cur;
}

void SceneManager::initL(lua_State *L) {
  this->L = lua_newthread(L);
  root = NULL;
}

void SceneManager::Remove(SceneNode* cur) {
  std::vector<SceneNode*> &fa_son = cur->father->son;
  fa_son.erase( std::find(fa_son.begin(), fa_son.end(), cur) );
  
  for (std::vector<SceneNode*>::iterator it = cur->son.begin(); it != cur->son.end(); ++it) {
    (*it)->father = cur->father;
    fa_son.push_back(*it);
  }

  luaL_unref(L, LUA_REGISTRYINDEX, cur->ref);
  delete cur;

  GameSystem::resetFrameTimer(0);
}

void SceneManager::Insert(SceneNode *fa, SceneNode *cur) {
  cur->obj = NewObject(cur);
  fa->son.push_back(cur);
  cur->father = fa;

  GameSystem::resetFrameTimer(0);
}

void SceneManager::Updata(SceneNode *cur) {
  GameSystem::resetFrameTimer(0);
}

void SceneManager::Release() {
  clear(root);
}

SceneNode* SceneManager::GetRoot() {
  return root;
}

void SceneManager::SetRoot(SceneNode *root) {
  this->root = root;
}

GameObject *SceneManager::NewObject(SceneNode *cur) {
  
  std::string attr;
  LuaObject handler(cur->ref);
  handler.LoadAttribute(attr);
  
  if (attr == "sprite")
    return dynamic_cast<GameObject*> (Sprite::create(cur->ref)); 

  if (attr == "background")
    return dynamic_cast<GameObject*> (Sprite::create(cur->ref)); 

  if (attr == "textbox")
    return dynamic_cast<GameObject*> (TextBox::create(cur->ref));
}

void SceneManager::GetObjects(std::vector<GameObject*> &obj, SceneNode *cur) {
  if (cur != root)
    obj.push_back( cur->obj );
  
  for (std::vector<SceneNode*>::iterator it = cur->son.begin(); it != cur->son.end(); ++it)  
    GetObjects(obj, *it);
}


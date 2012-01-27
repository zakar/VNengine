#include "SceneManager.h"
#include "GameSystem.h"
#include "ScreenLayer.h"
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

  obj.erase(std::find(obj.begin, obj.end(), cur->obj));

  luaL_unref(L, LUA_REGISTRYINDEX, cur->ref);
  delete cur;

  GameSystem::resetFrameTimer(0);
}

void SceneManager::Insert(SceneNode *fa, SceneNode *cur) {
  cur->obj = NewObject(cur);
  fa->son.push_back(cur);
  cur->father = fa;

  obj.push_back(cur->obj);

  GameSystem::resetFrameTimer(0);
}

void SceneManager::Updata(SceneNode *cur) {
  GameSystem::resetFrameTimer(0);
}

void SceneManager::Release() {
  clear(root);
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

std::vector<GameObject*>& SceneManager::GetObjects() {
  return obj;
}

void SceneManager::drawDirtyRect()
{
  // TODO: use dirtyinfo to calculate canvas
}

void SceneManager::fillDirtyRect()
{
  dw = ScreenLayer::GetInstance()->width / DW_WIDTH;
  dh = ScreenLayer::GetInstance()->height / DW_HEIGHT;
  memset(dirtyinfo, 0, sizeof(dirtyinfo));
  for (int i = 0; i < obj.size(); ++i) {
    LuaObject &handler = obj[i].handler;
    
    int x, y, w, h;
    handler.LoadClip(x, y, w, h);
    handler.LoadLocation(x, y);
    for (int l0 = x/dw, l1 = (x+w)/dw, l = l0; l <= l1; ++l) {
      for (int k0 = y/dh, k1 = (y+w)/dh, k = k0; k <= k1; ++k) {
	dirtyinfo[l][k] = 1;
      }
    }
  }
}

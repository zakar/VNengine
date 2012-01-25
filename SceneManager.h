#ifndef __SCENEMANAGER__
#define __SCENEMANAGER__

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <algorithm>

#include "SceneNode.h"

class SceneManager 
{
 public:
  ~SceneManager();
  static SceneManager* GetInstance();
  void Release();
  void initL(lua_State *L);
  void clear(SceneNode *cur);
  void Remove(SceneNode *cur);
  void Insert(SceneNode *fa, SceneNode *cur);
  void Updata(SceneNode *cur);
  void SetRoot(SceneNode *root);
  SceneNode* GetRoot();

 public:
  static GameObject *NewObject(SceneNode *cur); 
  void GetObjects(std::vector<GameObject*> &obj, SceneNode *cur);

 private:
  lua_State *L;
  SceneNode *root;

 private:
  SceneManager();
};

#endif

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

const int DW_WIDTH = 20;
const int DW_HEIGHT = 20;

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

  void dirtyInit();
  void drawDirtyRect();
  void fillDirtyRect();

 public:
  static GameObject *NewObject(SceneNode *cur); 
  std::vector<GameObject*>& GetObjects();

 private:
  lua_State *L;
  SceneNode *root;
  std::vector<GameObject*> obj;
  
  int dw, dh;
  int dirtyinfo[DW_WIDTH][DW_HEIGHT];

 private:
  SceneManager();
};

#endif

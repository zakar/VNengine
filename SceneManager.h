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
#include "Font.h"

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
  void Update(SceneNode *cur);
  void SetRoot(SceneNode *root);

  void drawDirtyRect();
  void checkActiveObject();

  //
  void createBulletText(const char* text, Uint32 color);
  void setBulletTextSpeed(Uint32 speed);
  void setBulletTextFont(const char* face, Uint32 size);
  //

 public:
  static GameObject *NewObject(SceneNode *cur); 
  std::vector<GameObject*>& GetObjects();

 private: 
  void getDirtyRect(SceneNode *root, const SDL_Rect &rect);
  void fillDirtyRect(Uint32 x, Uint32 y, Uint32 w, Uint32 h);

 private:
  lua_State *L;
  SceneNode *root;
  std::vector<GameObject*> obj;
  std::vector<GameObject*> activeObj;

  //
  std::vector<Canvas*> bulletText;
  Font *font;
  Uint32 bulletTextSpeed;
  Uint32 bulletTextWait;
  //
  
  int dw, dh;
  int dirtyinfo[DW_WIDTH][DW_HEIGHT];

 private:
  SceneManager();
};

#endif

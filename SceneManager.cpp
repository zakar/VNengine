#include "SceneManager.h"
#include "GameSystem.h"
#include "ScreenLayer.h"
#include "Sprite.h"
#include "TextBox.h"
#include "Helper.h"
#include <string>
#include <cstdlib>
#include <algorithm>

SceneManager::SceneManager() {
  memset(dirtyinfo, 0, sizeof(dirtyinfo));
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

void SceneManager::Move(SceneNode *src, SceneNode *des)
{
  std::vector<SceneNode*> &fa_son = src->father->son;
  fa_son.erase( std::find(fa_son.begin(), fa_son.end(), src) );

  src->father = des;
  des->son.push_back(src);

  SDL_Rect rect;
  Uint32 x, y;
  LuaObject handler(src->ref);
  handler.LoadClip(rect, "query");
  handler.LoadLocation(x, y, "query");
  fillDirtyRect(x, y, rect.w, rect.h);  
}

void SceneManager::Remove(SceneNode* cur) {
  std::vector<SceneNode*> &fa_son = cur->father->son;
  fa_son.erase( std::find(fa_son.begin(), fa_son.end(), cur) );
  
  for (std::vector<SceneNode*>::iterator it = cur->son.begin(); it != cur->son.end(); ++it) {
    (*it)->father = cur->father;
    fa_son.push_back(*it);
  }

  obj.erase(std::find(obj.begin(), obj.end(), cur->obj));

  SDL_Rect rect;
  Uint32 x, y;
  LuaObject handler(cur->ref);
  handler.LoadClip(rect, "query");
  handler.LoadLocation(x, y, "query");
  fillDirtyRect(x, y, rect.w, rect.h);  

  luaL_unref(L, LUA_REGISTRYINDEX, cur->ref);
  delete cur;

  GameSystem::resetTimer(0, FRAME_EVENT);
}

void SceneManager::Insert(SceneNode *fa, SceneNode *cur) {
  cur->obj = NewObject(cur);
  cur->obj->OnFrame(); //initialize frame
  fa->son.push_back(cur);
  cur->father = fa;

  obj.push_back(cur->obj);

  SDL_Rect rect;
  Uint32 x, y;
  LuaObject handler(cur->ref);
  handler.LoadClip(rect, "query");
  handler.LoadLocation(x, y, "query");
  fillDirtyRect(x, y, rect.w, rect.h);

  GameSystem::resetTimer(0, FRAME_EVENT);
}

void SceneManager::Update(SceneNode *cur) {
  cur->obj->OnFrame();
  LuaObject &handler = cur->obj->handler;
  SDL_Rect rect;
  Uint32 x, y;
  handler.LoadClip(rect, "query");
  handler.LoadLocation(x, y, "query");
  fillDirtyRect(x, y, rect.w, rect.h);
  
  GameSystem::resetTimer(0, FRAME_EVENT);
}

void SceneManager::Release() {
  clear(root);
  obj.clear();
}

void SceneManager::SetRoot(SceneNode *root) {
  this->root = root;
}

GameObject *SceneManager::NewObject(SceneNode *cur) {
  std::string attr;
  LuaObject handler(cur->ref);
  handler.LoadAttribute(attr, "query");
  
  if (attr == "sprite")
    return dynamic_cast<GameObject*> (Sprite::create(cur->ref)); 

  if (attr == "textbox")
    return dynamic_cast<GameObject*> (TextBox::create(cur->ref));

}

std::vector<GameObject*>& SceneManager::GetObjects() {
  return obj;
}

void SceneManager::fillDirtyRect(Uint32 x, Uint32 y, Uint32 w, Uint32 h)
{
  x = std::max(x, (Uint32)0);
  x = std::min(x, ScreenLayer::GetInstance()->getWidth());
  y = std::max(y, (Uint32)0);
  y = std::min(y, ScreenLayer::GetInstance()->getHeight());

  dw = ScreenLayer::GetInstance()->getWidth() / DW_WIDTH;
  dh = ScreenLayer::GetInstance()->getHeight() / DW_HEIGHT;

  for (int l0 = x/dw, l1 = (x+w-1)/dw+1, l = l0; l < l1; ++l)
    for (int k0 = y/dh, k1 = (y+h-1)/dh+1, k = k0; k < k1; ++k) {
      dirtyinfo[l][k] = 1;
    }
}

void SceneManager::getDirtyRect(SceneNode* cur, const SDL_Rect &rect)
{
  GameObject* obj = cur->obj;
  SDL_Rect dst = rect;
  if (obj->doClip(dst) && obj->checkVisible()) {
    ScreenLayer::GetInstance()->AddCanvas(obj->canvas2Render(dst));
  }

  std::vector<SceneNode*> &son = cur->son;
  for (int i = 0; i < son.size(); ++i) 
    getDirtyRect(son[i], rect);
}

void SceneManager::drawDirtyRect()
{
  // bulletText dirty handle
  if (--bulletTextWait <= 0) {
    for (int i = 0; i < bulletText.size(); ++i) {
      Uint32 &x = bulletText[i]->dst_x;
      Uint32 &y = bulletText[i]->dst_y;
      SDL_Rect &rect = bulletText[i]->clip;
      fillDirtyRect(x, y, rect.w, rect.h);
      x -= 4;
      fillDirtyRect(x, y, rect.w, rect.h);
    }

    bulletTextWait = bulletTextSpeed;
  }
  //
  
  for (int i = 0; i < activeObj.size(); ++i) {
    activeObj[i]->OnFrame(); //active then change new frame
    LuaObject &handler = activeObj[i]->handler;
    SDL_Rect rect;
    Uint32 x, y;
    handler.LoadClip(rect, "query");
    handler.LoadLocation(x, y, "query");
    fillDirtyRect(x, y, rect.w, rect.h);
    
    handler.LoadClip(rect, "update");
    handler.LoadLocation(x, y, "update");
    fillDirtyRect(x, y, rect.w, rect.h);
  }

  std::vector<SceneNode*> &son = root->son;
  for (int i = 0; i < DW_WIDTH; ++i) {
    for (int j = 0; j < DW_HEIGHT; ++j) {
      if (dirtyinfo[i][j]) {
	SDL_Rect rect = { dw*i, dh*j, dw, dh };
	for (int l = 0; l < son.size(); ++l) {
	  getDirtyRect(son[l], rect);
	}
      }
    }
  }
  
  // last to render bullet
  for (int i = 0; i < bulletText.size(); ++i) {
    Canvas *toDraw = new Canvas(bulletText[i]);
    ScreenLayer::GetInstance()->AddCanvas(toDraw);
  }

  memset(dirtyinfo, 0, sizeof(dirtyinfo));

  // clear passed bulletText may trigger fill dirty rect event
  while (bulletText.size() && bulletText[0]->dst_x + bulletText[0]->clip.w < 0) {
    Uint32 &x = bulletText[0]->dst_x;
    Uint32 &y = bulletText[0]->dst_y;
    SDL_Rect &rect = bulletText[0]->clip;
    fillDirtyRect(x, y, rect.w, rect.h);
    delete bulletText[0];
    bulletText.erase(bulletText.begin());
  }
}

void SceneManager::checkActiveObject()
{
  activeObj.clear();

  Uint32 next_ti = -1;
  for (int i = 0; i < obj.size(); ++i) {
    LuaObject &handler = obj[i]->handler;
    Uint32 cur_ti;
    handler.LoadFrameTime(cur_ti, "query");
    if (cur_ti == -1) continue;
    if (next_ti == -1 || cur_ti < next_ti) {
      next_ti = cur_ti;
      activeObj.clear();
      activeObj.push_back(obj[i]);
    } else if (cur_ti == next_ti) {
      activeObj.push_back(obj[i]);
    }
  }

  if (next_ti != -1) {
    for (int i = 0; i < obj.size(); ++i) {
      LuaObject &handler = obj[i]->handler;
      Uint32 tmp_ti = next_ti;
      handler.LoadFrameTime(tmp_ti, "update");
    }
    GameSystem::resetTimer(next_ti, FRAME_EVENT);
  }
}

//
void SceneManager::createBulletText(const char* text, Uint32 color)
{
  std::basic_string<Uint16> utext = Helper::GetUTF16(text);
  Canvas *bt;
  for (int i = utext.size()-1; i >= 0; --i)  //simple fliter -_-
    if (utext[i] <= 32) utext.erase(i, 1);

  bt = Font::GetInstance()->createTextSurface(utext.c_str(), color);
  bt->dst_x = ScreenLayer::GetInstance()->getWidth();
  bt->dst_y = rand()%(ScreenLayer::GetInstance()->getHeight()/2)+20;  // just for test -_-
  bt->clip.x = 0;
  bt->clip.y = 0;
  bt->clip.w = bt->surface->w;
  bt->clip.h = bt->surface->h;
  bt->global_alpha = DISABLE_ALPHA;
  bt->color_key = DISABLE_COLORKEY;
  bulletText.push_back(bt);
}

void SceneManager::setBulletTextSpeed(Uint32 speed)
{
  bulletTextSpeed = speed;
  bulletTextWait = speed;
}


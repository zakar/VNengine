#include "ImagePool.h"
#include "Canvas.h"
#include <map>
#include <vector>
#include <assert.h>
using namespace std;

enum {
  IMG_FILE = 0,
  IMG_RAW,
};

static const int LRU_MAX = 100;

struct ImageInfo
{
  int type;
  int w, h;
  int lru_time;
  int count;
  SDL_Surface* image;
  ImageInfo(){};
  ImageInfo(int type, int w = 0, int h = 0):
    type(type), w(w), h(h) {
    image = NULL;
    count = 0;
    lru_time = LRU_MAX;
  }
};

typedef map<string, ImageInfo>::iterator ImgPoolIter;

static ImgPoolIter lru_idx;
static map<string, ImageInfo> image_pool;
static int IMG_RAW_ID = 0;

static void lruStep()
{
  if (lru_idx != image_pool.end()) {
    if (lru_idx->second.count == 0 &&
	lru_idx->second.image != NULL && --lru_idx->second.lru_time == 0) {
      SDL_FreeSurface(lru_idx->second.image);
      lru_idx->second.image = NULL;
    }
    ++lru_idx;
  } else {
    lru_idx = image_pool.begin();
  }
}

void ImagePool::Init()
{
  image_pool.clear();
  lru_idx = image_pool.begin();
}

void ImagePool::ShutDown()
{
  lru_idx = image_pool.begin();
  for (; lru_idx != image_pool.end(); ++lru_idx) {
    if (lru_idx->second.image == NULL) continue;
    SDL_FreeSurface(lru_idx->second.image);
  }
}

SDL_Surface* ImagePool::loadImageFile(const string& name)
{
  lruStep();
  if (image_pool.count(name) == 0) {
    image_pool[name] = ImageInfo(IMG_FILE);
    lru_idx = image_pool.begin();
  }

  return getImage(name);
}

SDL_Surface* ImagePool::loadImageRaw(std::string& name, int w, int h)
{
  lruStep();
  char buf[32]={0};
  sprintf(buf, "RAW%d", IMG_RAW_ID++);
  name = buf;
  if (image_pool.count(name) == 0) {
    image_pool[name] = ImageInfo(IMG_RAW, w, h);
    lru_idx = image_pool.begin();
  }

  return getImage(name);
}

SDL_Surface* ImagePool::getImage(const std::string& name)
{
  if (image_pool.count(name) == 0) return NULL;
  ImgPoolIter cur = image_pool.find(name);

  SDL_Surface* surface = cur->second.image;
  SDL_Surface* pixel;
  SDL_Surface* tmp;
  if (surface == NULL) {
    switch (cur->second.type) {
    case IMG_FILE : 
      pixel = SDL_CreateRGBSurface(DEFAULT_SURFACE_FLAG, 1, 1, BPP, RMASK, GMASK, BMASK, AMASK);
      tmp = IMG_Load(name.c_str());
      surface = SDL_ConvertSurface(tmp, pixel->format, NULL);
      SDL_FreeSurface(pixel);
      SDL_FreeSurface(tmp);
      break;
      
    case IMG_RAW :
      surface = SDL_CreateRGBSurface(DEFAULT_SURFACE_FLAG, cur->second.w, cur->second.h, BPP, RMASK, GMASK, BMASK, AMASK);
      break;
    }
  }
  
  cur->second.image = surface;
  cur->second.lru_time = LRU_MAX;
  assert(cur->second.count >= 0);
  ++cur->second.count;

  lruStep();

  return surface;
}

void ImagePool::freeImage(const std::string& name)
{
  if (image_pool.count(name) == 0) return;
  ImgPoolIter cur = image_pool.find(name);

  --cur->second.count;
  assert(cur->second.count >= 0);

  lruStep();

  return;
}


#include <cstdio>
#include <algorithm>
#include "Exception.h"
#include "Canvas.h"
#include "BlockAllocator.h"
#include "ImagePool.h"

Canvas::Canvas() {
  surface = NULL;
}

Canvas::Canvas(Canvas* cav) {
  *this = *cav;
  surface = NULL;
  if (cav->surface) {
    cached_name = cav->cached_name;
    surface = ImagePool::getImage(cached_name);
  }
}

Canvas::~Canvas() {
  if (surface) {
    ImagePool::freeImage(cached_name);
  }
}

void Canvas::ColorRect(SDL_Surface *surface, Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 color) {
  SDL_Rect rec;
  rec.x = x;
  rec.y = y;
  rec.w = width;
  rec.h = height;
  SDL_FillRect(surface, &rec, color);
}


bool Canvas::ClipSurface(SDL_Rect &dst, SDL_Rect clip)
{
  Uint32 dx0 = dst.x, dx1 = dst.x+dst.w-1, dy0 = dst.y, dy1 = dst.y+dst.h-1;
  Uint32 cx0 = clip.x, cx1 = clip.x+clip.w-1 , cy0 = clip.y, cy1 = clip.y+clip.h-1;

  if (cx1 < dx0 || dx1 < cx0 || cy1 < dy0 || dy1 < cy0) return false;
  
  Uint32 ux, uy, dx, dy;
  ux = std::max(dx0, cx0);
  uy = std::max(dy0, cy0);
  dx = std::min(dx1, cx1);
  dy = std::min(dy1, cy1);

  dst.x = ux;
  dst.y = uy;
  dst.w = dx - ux + 1;
  dst.h = dy - uy + 1;

  return true;
}

void Canvas::BlendSurface(SDL_Surface *surface, SDL_Surface *dst, Uint32 dst_x, Uint32 dst_y, SDL_Rect clip, Uint32 global_alpha, Uint32 color_key)
{
  if (surface == NULL || dst == NULL) return;

  SDL_Rect dst_clip = { dst_x, dst_y, clip.w, clip.h }, rect = { 0, 0, dst->w, dst->h };
  ClipSurface(dst_clip, rect);
  SDL_Rect src_clip = { 0, 0, surface->w, surface->h };
  ClipSurface(src_clip, clip);
  
  Uint32 width = std::min(src_clip.w, dst_clip.w), height = std::min(src_clip.h, dst_clip.h);
  
  src_clip.w = width;  src_clip.h = height;
  dst_clip.w = width;  dst_clip.h = height;
  if (global_alpha != DISABLE_ALPHA) SDL_SetAlpha(surface, SDL_SRCALPHA, global_alpha);
  if (color_key != DISABLE_COLORKEY) SDL_SetColorKey(surface, SDL_SRCCOLORKEY, color_key);
  SDL_BlitSurface(surface, &src_clip, dst, &dst_clip);
  if (global_alpha == DISABLE_ALPHA) SDL_SetAlpha(surface, 0, 0);
  if (color_key == DISABLE_COLORKEY) SDL_SetColorKey(surface, 0, 0);
}

void Canvas::BlendSurface(SDL_Surface *dst)
{
  if (surface == NULL || dst == NULL) return;

  SDL_Rect dst_clip = { dst_x, dst_y, clip.w, clip.h }, rect = { 0, 0, dst->w, dst->h };
  ClipSurface(dst_clip, rect);

  SDL_Rect src_clip = { 0, 0, surface->w, surface->h };
  ClipSurface(src_clip, clip);
  
  Uint32 width = std::min(src_clip.w, dst_clip.w), height = std::min(src_clip.h, dst_clip.h);

  src_clip.w = width;  src_clip.h = height;
  dst_clip.w = width;  dst_clip.h = height;

  if (global_alpha != DISABLE_ALPHA) SDL_SetAlpha(surface, SDL_SRCALPHA, global_alpha);
  if (color_key != DISABLE_COLORKEY) SDL_SetColorKey(surface, SDL_SRCCOLORKEY, color_key);
  SDL_BlitSurface(surface, &src_clip, dst, &dst_clip);
  if (global_alpha == DISABLE_ALPHA) SDL_SetAlpha(surface, 0, 0);
  if (color_key == DISABLE_COLORKEY) SDL_SetColorKey(surface, 0, 0);
}


void Canvas::LoadRaw(Uint32 width, Uint32 height ) {
  if (surface) {
    ImagePool::freeImage(cached_name);
    surface = NULL;
  }
  surface = ImagePool::loadImageRaw(cached_name, width, height);
}

void Canvas::LoadImage(const char* fileName) {
  if (surface) {
    ImagePool::freeImage(cached_name);
    surface = NULL;
  }
  cached_name = fileName;
  surface = ImagePool::loadImageFile(cached_name);
}

void Canvas::ColorRect(Uint32 color) {
  SDL_FillRect(surface, &clip, color);
}

static BlockAllocator<Canvas, 400> canvasAllocator;

void* Canvas::operator new(size_t s)
{
  return (void*)canvasAllocator.Allocate();
}

void Canvas::operator delete(void* addr)
{
  canvasAllocator.Free((Canvas*)addr);
}

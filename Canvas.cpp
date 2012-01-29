#include <cstdio>
#include <algorithm>
#include "Exception.h"
#include "Canvas.h"

Canvas::Canvas() {
  surface = NULL;
}

Canvas::~Canvas() {
  // if ( surface ) {
  //   SDL_FreeSurface(surface);
  // }
}

void Canvas::NewSurface(SDL_Surface *&surface, Uint32 width, Uint32 height, Uint32 color) {
  if (surface) {
    SDL_FreeSurface(surface);
    surface = NULL;
  }
  
  surface = SDL_CreateRGBSurface(DEFAULT_SURFACE_FLAG, width, height, BPP, RMASK, GMASK, BMASK, AMASK);
  ColorRect(surface, 0, 0, width, height, color);
}


void Canvas::LoadImage(SDL_Surface *&surface, const char* fileName) {
  if (surface) {
    SDL_FreeSurface(surface);
    surface = 0;
  }

  SDL_Surface *pixel = SDL_CreateRGBSurface(DEFAULT_SURFACE_FLAG, 1, 1, BPP, RMASK, GMASK, BMASK, AMASK);
  SDL_Surface *tmp = IMG_Load(fileName);
  surface = SDL_ConvertSurface(tmp, pixel->format, NULL);
  SDL_FreeSurface(pixel);
  SDL_FreeSurface(tmp);
	
  if (!surface) {
    char buf[256];
    sprintf(buf, "Load file failed: %s", fileName);
    throw Exception(buf);
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

void Canvas::BlendSurface(SDL_Surface *surface, SDL_Surface *dst, Uint32 dst_x, Uint32 dst_y, SDL_Rect clip, Uint32 global_alpha, Uint32 color_key)
{
  if (surface == NULL || dst == NULL) return;

  SDL_Rect dst_clip = { dst_x, dst_y, clip.w, clip.h }, rect = { 0, 0, dst->w, dst->h };
  ClipSurface(dst_clip, rect);

  SDL_Rect src_clip = { 0, 0, surface->w, surface->h };
  ClipSurface(src_clip, clip);
  
  Uint32 width = std::min(src_clip.w, dst_clip.w), height = std::min(src_clip.h, dst_clip.h);

  //
  src_clip.w = width;  src_clip.h = height;
  dst_clip.w = width;  dst_clip.h = height;

  if (global_alpha != DISABLE_ALPHA) SDL_SetAlpha(surface, SDL_SRCALPHA, global_alpha);
  if (color_key != DISABLE_COLORKEY) SDL_SetColorKey(surface, SDL_SRCCOLORKEY, color_key);
  SDL_BlitSurface(surface, &src_clip, dst, &dst_clip);
  if (global_alpha == DISABLE_ALPHA) SDL_SetAlpha(surface, 0, 0);
  if (color_key == DISABLE_COLORKEY) SDL_SetColorKey(surface, 0, 0);

  
  //

  
  // SDL_LockSurface(surface);
  // SDL_LockSurface(dst);

  // //此处假设像素是32位的,即pitch和w是相等的
  // Uint32* dst_pt = (Uint32*)dst->pixels + dst->w * dst_clip.y + dst_clip.x;
  // Uint32* src_pt = (Uint32*)surface->pixels + surface->w * src_clip.y + src_clip.x;
  // Uint8* alpha_pt = (Uint8*)src_pt + 3;

  // Uint32 pixelrb, pixelg, mask1, mask2;
  // for (Uint32 i = 0; i < height; ++i) {
    
  //   for (Uint32 j = 0; j < width; ++j, ++dst_pt, ++src_pt, alpha_pt += 4) {

  //     if ((*src_pt & RGBMASK) == color_key) continue;

  //     mask1 = (*alpha_pt * global_alpha) >> 8;
  //     mask2 = mask1 ^ 0xff;
  //     pixelrb = ((*dst_pt & RBMASK) * mask2 + (*src_pt & RBMASK) * mask1) >> 8;
  //     pixelg = ((*dst_pt & GMASK) * mask2 + (*src_pt & GMASK) * mask1) >> 8;
  //     *dst_pt = (pixelrb & RBMASK) | (pixelg & GMASK) | (*dst_pt & AMASK);
  //   }

  //   dst_pt += dst->w - width;
  //   src_pt += surface->w - width;
  // }

  // SDL_UnlockSurface(dst);
  // SDL_UnlockSurface(surface);
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


void Canvas::BlendSurface(SDL_Surface *dst)
{
  if (surface == NULL || dst == NULL) return;

  SDL_Rect dst_clip = { dst_x, dst_y, clip.w, clip.h }, rect = { 0, 0, dst->w, dst->h };
  ClipSurface(dst_clip, rect);

  SDL_Rect src_clip = { 0, 0, surface->w, surface->h };
  ClipSurface(src_clip, clip);
  
  Uint32 width = std::min(src_clip.w, dst_clip.w), height = std::min(src_clip.h, dst_clip.h);

  //
  src_clip.w = width;  src_clip.h = height;
  dst_clip.w = width;  dst_clip.h = height;

  if (global_alpha != DISABLE_ALPHA) SDL_SetAlpha(surface, SDL_SRCALPHA, global_alpha);
  if (color_key != DISABLE_COLORKEY) SDL_SetColorKey(surface, SDL_SRCCOLORKEY, color_key);
  SDL_BlitSurface(surface, &src_clip, dst, &dst_clip);
  if (global_alpha == DISABLE_ALPHA) SDL_SetAlpha(surface, 0, 0);
  if (color_key == DISABLE_COLORKEY) SDL_SetColorKey(surface, 0, 0);
}


void Canvas::NewSurface(Uint32 width, Uint32 height, Uint32 color) {
  if (surface) {
    SDL_FreeSurface(surface);
    surface = NULL;
  }
  
  surface = SDL_CreateRGBSurface(DEFAULT_SURFACE_FLAG, width, height, BPP, RMASK, GMASK, BMASK, AMASK);
  ColorRect(surface, 0, 0, width, height, color);
}


void Canvas::LoadImage(const char* fileName) {
  if (surface) {
    SDL_FreeSurface(surface);
    surface = 0;
  }

  SDL_Surface *pixel = SDL_CreateRGBSurface(DEFAULT_SURFACE_FLAG, 1, 1, BPP, RMASK, GMASK, BMASK, AMASK);
  SDL_Surface *tmp = IMG_Load(fileName);
  surface = SDL_ConvertSurface(tmp, pixel->format, NULL);
  SDL_FreeSurface(pixel);
  SDL_FreeSurface(tmp);
	
  if (!surface) {
    char buf[256];
    sprintf(buf, "Load file failed: %s", fileName);
    throw Exception(buf);
  }
}

void Canvas::ColorRect(Uint32 color) {
  SDL_FillRect(surface, &clip, color);
}


#include "GameObject.h"

GameObject::GameObject(int ref):handler(ref) {
  canvas = new Canvas;
}

GameObject::~GameObject() {
  delete canvas;
}

void GameObject::OnFrame() {
}

void GameObject::OnKeyDown(SDLKey key) {
}

void GameObject::OnKeyUp(SDLKey key) {
}

void GameObject::OnMouseDown(Uint16 x, Uint16 y, Uint8 button) {
}

void GameObject::OnMouseUp(Uint16 x, Uint16 y, Uint8 button) {
}

void GameObject::OnMouseMove(Uint16 x, Uint16 y) {
}

bool GameObject::doClip(SDL_Rect &dst)
{
  SDL_Rect rect = { canvas->dst_x, canvas->dst_y, canvas->clip.w, canvas->clip.h };
  return Canvas::ClipSurface(dst, rect);
}

bool GameObject::checkCover(const SDL_Rect &dst)
{
  SDL_Rect rect = { canvas->dst_x, canvas->dst_y, canvas->clip.w, canvas->clip.h };
  if (!(rect.x <= dst.x && dst.x+dst.w <= rect.x+rect.w)) return 0;
  if (!(rect.y <= dst.y && dst.y+dst.h <= rect.y+rect.h)) return 0;
  if (canvas->global_alpha != DISABLE_ALPHA) return 0;
  return 1;
}

Canvas *GameObject::canvas2Render(const SDL_Rect &dst)
{
  Canvas* cur = new Canvas;
  *cur = *canvas;
  cur->clip.x = dst.x - cur->dst_x;
  cur->clip.y = dst.y - cur->dst_y;
  cur->clip.w = dst.w;
  cur->clip.h = dst.h;
  cur->dst_x = dst.x;
  cur->dst_y = dst.y;
  return cur;
}

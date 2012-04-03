#include "GameObject.h"

GameObject::GameObject(int ref):handler(ref) {
  canvas = new Canvas;
  visiable = 0;
}

GameObject::~GameObject() {
  if (canvas->surface) {
    SDL_FreeSurface(canvas->surface);
  }
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

Canvas *GameObject::canvas2Render(const SDL_Rect &dst)
{
  Canvas* cur = new Canvas;
  *cur = *canvas;
  cur->clip.x += dst.x - cur->dst_x;
  cur->clip.y += dst.y - cur->dst_y;
  cur->clip.w = dst.w;
  cur->clip.h = dst.h;
  cur->dst_x = dst.x;
  cur->dst_y = dst.y;
  return cur;
}

int GameObject::checkVisible()
{
  return visiable == 0;
}

void GameObject::setVisible(int flag, int mask)
{
  switch (flag) {
  case FLIP : visiable ^= mask; break;
  case SET : visiable |= mask; break;
  case UNSET : visiable &= (~mask); break;
  }
}

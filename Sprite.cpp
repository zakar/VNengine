#include "Sprite.h"
#include "ScreenLayer.h"

Sprite::Sprite(int ref):GameObject(ref) {
}

Sprite* Sprite::create(int ref) {
  Sprite *pt = new Sprite(ref);
  return pt;
}

Sprite::~Sprite() {
}

void Sprite::OnFrame() {
  handler.LoadClip(canvas->clip, "query");
  handler.LoadLocation(canvas->dst_x, canvas->dst_y, "query");
  handler.LoadColorKey(canvas->color_key, "query");
  handler.LoadGlobalAlpha(canvas->global_alpha, "query");

  std::string img_name;
  handler.LoadImgName(img_name, "query");
  canvas->LoadImage(img_name.c_str());
}

void Sprite::OnKeyDown(SDLKey key) {
}

void Sprite::OnKeyUp(SDLKey key) {
}

void Sprite::OnMouseDown(Uint16 x, Uint16 y, Uint8 button) {
}

void Sprite::OnMouseUp(Uint16 x, Uint16 y, Uint8 button) {
}

void Sprite::OnMouseMove(Uint16 x, Uint16 y) {
}

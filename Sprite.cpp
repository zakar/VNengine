#include "Sprite.h"
#include "ScreenLayer.h"

Sprite::Sprite(int ref):GameObject(ref) {
}

Sprite* Sprite::create(int ref) {
  Sprite *pt = new Sprite(ref);
  pt->image_name.clear();
  return pt;
}

Sprite::~Sprite() {
}

void Sprite::OnFrame() {
  handler.LoadClip(canvas->clip, "query");
  handler.LoadLocation(canvas->dst_x, canvas->dst_y, "query");
  handler.LoadColorKey(canvas->color_key, "query");
  handler.LoadGlobalAlpha(canvas->global_alpha, "query");

  std::string tmp_name;
  handler.LoadImgName(tmp_name, "query");
  if (tmp_name == image_name) return;
  image_name = tmp_name;
  canvas->LoadImage(image_name.c_str());
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

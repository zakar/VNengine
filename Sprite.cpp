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
  handler.LoadClip(canvas->clip);
  handler.LoadLocation(canvas->dst_x, canvas->dst_y);
  handler.LoadColorKey(canvas->color_key);
  handler.LoadGlobalAlpha(canvas->global_alpha);

  std::string tmp_name;
  handler.LoadImgName(tmp_name);
  if (tmp_name != image_name) {
    image_name = tmp_name;
    canvas->LoadImage(image_name.c_str());
  }

  ScreenLayer::GetInstance()->AddCanvas(canvas);
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

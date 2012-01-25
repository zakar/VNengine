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


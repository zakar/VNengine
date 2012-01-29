#include "TextBox.h"
#include "TextBoxLuaAPI.h"
#include "GameSystem.h"
#include "ScreenLayer.h"

#include <iostream>

#define HEIGHT_DELTA 2
#define WIDTH_DELTA 3
#define DEFAULT_DRAW_INTERVAL 5

static Uint16 CHN[2] = {0x554a, 0};

TextBox:: ~TextBox() {
}

TextBox* TextBox::create(int ref) {

  LuaObject handler(ref);
  handler.registerAPI(std::string("textbox"));

  Uint32 width, height, WLoffX, WLoffY, WLwidth, WLheight, fontSize, BoxColor, TextColor;
  std::string imgName, fontName;
  handler.LoadWordLayer(imgName, width, height, BoxColor, TextColor, WLoffX, WLoffY, WLwidth, WLheight, \
			fontName, fontSize, "query");

  if (imgName.empty()) {
    return new TextBox(width, height, BoxColor, TextColor, fontName.c_str(), fontSize, \
			      WLoffX, WLoffY, WLwidth, WLheight, ref);
  }else {
    return new TextBox(imgName.c_str(), TextColor, fontName.c_str(), fontSize, \
			      WLoffX, WLoffY, WLwidth, WLheight, ref);
  }

}

TextBox::TextBox(Uint32 width, Uint32 height, \
		 Uint32 BoxColor, Uint32 TextColor, const char* fontName, Uint32 fontSize, \
		 Uint32 WLoffX, Uint32 WLoffY, Uint32 WLwidth, Uint32 WLheight, int ref)
  : GameObject(ref), 
    font(fontName, fontSize), 
    TextColor(TextColor),
    WLoffX(WLoffX),
    WLoffY(WLoffY),
    WLwidth(WLwidth),
    WLheight(WLheight)
{
  canvas->NewSurface(width, height, BoxColor);
  Canvas::NewSurface(cleanlayer = NULL, WLwidth, WLheight, BoxColor);
  SDL_SetAlpha(cleanlayer, 0, 255);

  font.GetTextSize(CHN, wordH, wordW);
  SetDrawInterval(DEFAULT_DRAW_INTERVAL);
  SetPerformState(suspend);
}

TextBox::TextBox(const char* imageName, \
		 Uint32 TextColor, const char* fontName, Uint32 fontSize, \
		 Uint32 WLoffX, Uint32 WLoffY, Uint32 WLwidth, Uint32 WLheight, int ref)
  : GameObject(ref),
    font(fontName, fontSize), 
    TextColor(TextColor),
    WLoffX(WLoffX),
    WLoffY(WLoffY),
    WLwidth(WLwidth),
    WLheight(WLheight)
{
  canvas->LoadImage(imageName);
  Canvas::NewSurface(cleanlayer = NULL, WLwidth, WLheight);
  SDL_Rect clip = { WLoffX, WLoffY, WLwidth, WLheight };
  SDL_SetAlpha(canvas->surface, 0, 255);
  Canvas::BlendSurface(canvas->surface, cleanlayer, 0, 0, clip, DISABLE_ALPHA, DISABLE_COLORKEY);
  SDL_SetAlpha(canvas->surface, SDL_SRCALPHA, 255);
  SDL_SetAlpha(cleanlayer, 0, 255);

  font.GetTextSize(CHN, wordH, wordW);
  SetDrawInterval(DEFAULT_DRAW_INTERVAL);
  SetPerformState(suspend);
}

void TextBox::Clear() //此处清空文本的策略是染一种色，然后将ColorKey设为这种颜色，得到透明的surface
{
  SDL_Rect clip = { 0, 0, WLwidth, WLheight };
  Canvas::BlendSurface(cleanlayer, canvas->surface, WLoffX, WLoffY, clip, DISABLE_ALPHA, DISABLE_COLORKEY);
}

void TextBox::SetDrawInterval(Uint32 draw_interval) {
  this->draw_interval = draw_interval;
}

void TextBox::SetWordsToRender(std::basic_string<Uint16> word)
{
  nowX = WLoffX;
  nowY = WLoffY;
  wordsToRender = word;
  draw_current = draw_interval;
  visiable = 1;
}

void TextBox::SetPerformState(PerformState state) {
  performState = state;
}

void TextBox::ProcessWord(Uint16 word)
{
  Uint16 str[2] = {0, 0};
  str[0] = word;
  
  if (wordW + nowX + WIDTH_DELTA > WLwidth) {
    NewLine();
  }

  if (nowY + wordH > WLheight) return;
  
  font.DrawTextBlended(str, TextColor, canvas->surface, nowX, nowY);
  nowX += wordW + WIDTH_DELTA;
}

void TextBox::NewLine()
{
  nowY += wordH + HEIGHT_DELTA;
  nowX = WLoffX;
}

void TextBox::DrawText()
{
  if (performState == suspend) return;
 
  if (performState == running && visiable) {
    if (--draw_current <= 0) {
      if (wordsToRender[0] == '/') { //部分文字输出结束，等待用户继续，'/p'为不换行，'/n'为换行
	wordsToRender.erase(0, 1);
	if (wordsToRender[0] == 'n') {
	  NewLine();
	}
	wordsToRender.erase(0, 1);
	performState = waiting;
      } else {
	ProcessWord(wordsToRender[0]);
	wordsToRender.erase(0, 1);
	if (wordsToRender.empty()) 
	  performState = suspend;
      }
      draw_current = draw_interval;
    }
  }
}

void TextBox::OnFrame() {
  handler.LoadLocation(canvas->dst_x, canvas->dst_y, "query");
  handler.LoadClip(canvas->clip, "query");
  handler.LoadGlobalAlpha(canvas->global_alpha, "query");
  handler.LoadColorKey(canvas->color_key, "query"); 
  DrawText();  
}

void TextBox::OnKeyDown(SDLKey key) {
}

void TextBox::OnKeyUp(SDLKey key) {
}

void TextBox::OnMouseDown(Uint16 x, Uint16 y, Uint8 button) {
  if (!handler.ExecOnMouseRange(x, y, "query"))
    return;

  if (button == SDL_BUTTON_LEFT) {
    switch (performState) {
    case suspend:
      Clear();
      GameSystem::resetScriptTimer(0);
      break;
    case running: 
      while (performState == running) DrawText();
      break;
    case waiting:
      performState = running;
      break;
    }
  }

  if (button == SDL_BUTTON_RIGHT) 
    visiable ^= 1;
}

void TextBox::OnMouseUp(Uint16 x, Uint16 y, Uint8 button) {
}

void TextBox::OnMouseMove(Uint16 x, Uint16 y) {
}

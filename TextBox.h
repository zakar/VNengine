#ifndef __TEXTBOX__
#define __TEXTBOX__

#include "GameObject.h"
#include "Font.h"
#include <string>
#include <algorithm>


class TextBox : public GameObject
{
 public:
  void OnFrame();
  void OnKeyDown(SDLKey key);
  void OnKeyUp(SDLKey key);
  void OnMouseDown(Uint16 x, Uint16 y, Uint8 button);
  void OnMouseUp(Uint16 x, Uint16 y, Uint8 button);
  void OnMouseMove(Uint16 x, Uint16 y);

 public:
  ~TextBox();
  static TextBox* create(int ref);
  TextBox(Uint32 width, Uint32 height,					\
	  Uint32 BoxColor, Uint32 TextColor, \
	  Uint32 WLoffX, Uint32 WLoffY, Uint32 WLwidth, Uint32 WLheight, int ref);
    
  TextBox(const char* imageName, \
	  Uint32 TextColor, \
	  Uint32 WLoffX, Uint32 WLoffY, Uint32 WLwidth, Uint32 WLheight, int ref);

 public:
  void SetDrawInterval(Uint32 draw_interval);
  void SetWordsToRender(std::basic_string<Uint16> word);
  void Clear();
  void ProcessWord(Uint16 word);
  void NewLine();
  void DrawText(); 

 public:
  enum PerformState { suspend, running, waiting };
  void SetPerformState(PerformState state);
  PerformState performState; //0等待脚本载入文字，1正在输出文字，2文字输出完毕等待用户继续反应
  
 private:
  std::basic_string<Uint16> wordsToRender;
  Uint32 draw_interval, draw_current; 

 private:
  Canvas cleanlayer;
  Uint32 WLoffX, WLoffY;
  Uint32 WLwidth, WLheight;
  
 private:
  Uint32 TextColor;
  Uint32 wordH, wordW;
  Uint32 nowX, nowY;
};

#endif

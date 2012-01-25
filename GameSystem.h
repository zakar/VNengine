#ifndef  __GAMESYSTEM__
#define  __GAMESYSTEM__

#include "SDL/SDL.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

#define FRAME_EVENT  SDL_USEREVENT
#define SCRIPT_EVENT SDL_USEREVENT+1

class GameSystem
{
public:
	~GameSystem();
	static GameSystem* GetInstance();

public: 
	//初始化各个模块
	void Initialize(Uint32 width, Uint32 height, bool fullScreen = false, int bpp = 32, const char* title = "test");
	void Run();
	void Release();

public:
	static void resetFrameTimer(int ti);
	static void resetScriptTimer(int ti);

public:
	static Uint32 frame_event_interval;
	static Uint32 script_event_interval;

private:
	lua_State *L; //脚本机的主线程

private:
	GameSystem();
};

#endif

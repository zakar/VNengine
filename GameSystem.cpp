#include "GameSystem.h"
#include "GameSystemLuaAPI.h"
#include "ScreenLayer.h"
#include "SceneManager.h"
#include "SceneManagerLuaAPI.h"
#include "EventHandler.h"
#include "LuaObject.h"
#include "Exception.h"

static SDL_TimerID frame_timer_id = NULL;
static SDL_TimerID script_timer_id = NULL;

Uint32 GameSystem::frame_event_interval = 0;
Uint32 GameSystem::script_event_interval = 0;

extern "C" Uint32 SDLCALL FrameCallback( Uint32 interval, void *param )
{
  SDL_RemoveTimer( frame_timer_id );
  
  SDL_Event event;
  event.type = FRAME_EVENT;
  SDL_PushEvent( &event );
}

extern "C" Uint32 SDLCALL ScriptCallback( Uint32 interval, void *param )
{
  SDL_RemoveTimer( script_timer_id );

  SDL_Event event;
  event.type = SCRIPT_EVENT;
  SDL_PushEvent( &event );
}

void GameSystem::resetFrameTimer(int ti)
{
  if (frame_timer_id != NULL)
    SDL_RemoveTimer( frame_timer_id );

  GameSystem::frame_event_interval = ti;
  
  if (ti > 0) {
    SDL_AddTimer(ti, FrameCallback, NULL);
    return;
  }

  SDL_Event event;
  event.type = FRAME_EVENT;
  SDL_PushEvent( &event );
}

void GameSystem::resetScriptTimer(int ti)
{
  if (script_timer_id != NULL)
    SDL_RemoveTimer( script_timer_id );

  GameSystem::script_event_interval = ti;
  
  if (ti > 0) {
    SDL_AddTimer(ti, ScriptCallback, NULL);
    return;
  }

  SDL_Event event;
  event.type = SCRIPT_EVENT;
  SDL_PushEvent( &event );
}

GameSystem* GameSystem::GetInstance() {
	static GameSystem instance;
	return &instance;
}

GameSystem::GameSystem() {

}

GameSystem::~GameSystem() {
  lua_close(L);
}

void GameSystem::Initialize(Uint32 width, Uint32 height, bool fullScreen, int bpp, const char* title) {

	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)  == -1) {
		throw Exception("GameSystem:: Failed to initialize SDL");
	}

	ScreenLayer::GetInstance()->SetWindowMode(width, height, fullScreen, bpp);
	ScreenLayer::GetInstance()->SetTitle(title);

	L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "commond_header.lua");

	GameSystemLuaAPI::luaopen_gamesystem(L);	
	SceneManagerLuaAPI::luaopen_scene(L);
	SceneManager::GetInstance()->initL(L);
	EventHandler::GetInstance()->initL(L);
	LuaObject::initL(L);

	luaL_dofile(L, "commond.lua");
	luaL_dofile(L, "test.lua"); 
}

void GameSystem::Run() {

  resetScriptTimer(0);
  
  SDL_Event gameEvent;
  while (SDL_WaitEvent(&gameEvent)) {
    switch(gameEvent.type) {

    case SDL_QUIT : 
      return;

    case SDL_KEYDOWN : 
      EventHandler::GetInstance()->OnKeyDown(gameEvent.key.keysym.sym); break;

    case SDL_KEYUP : 
      EventHandler::GetInstance()->OnKeyUp(gameEvent.key.keysym.sym); break;

    case SDL_MOUSEBUTTONDOWN : 
      EventHandler::GetInstance()->OnMouseDown(gameEvent.button.x, gameEvent.button.y, gameEvent.button.button); break;

    case SDL_MOUSEBUTTONUP :  
      EventHandler::GetInstance()->OnMouseUp(gameEvent.button.x, gameEvent.button.y, gameEvent.button.button); break;

    case SDL_MOUSEMOTION : 
      EventHandler::GetInstance()->OnMouseMove(gameEvent.motion.x, gameEvent.motion.y); break;
      
    case FRAME_EVENT :
      EventHandler::GetInstance()->OnFrame(); break;

    case SCRIPT_EVENT :
      EventHandler::GetInstance()->OnScript(); break;
    }	
  }
}

void GameSystem::Release() {
  	ScreenLayer::GetInstance()->Release();
	SceneManager::GetInstance()->Release();
}


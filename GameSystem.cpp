#include "GameSystem.h"
#include "GameSystemLuaAPI.h"
#include "ScreenLayer.h"
#include "SceneManager.h"
#include "SceneManagerLuaAPI.h"
#include "EventHandler.h"
#include "LuaObject.h"
#include "ImagePool.h"
#include "Exception.h"

static SDL_TimerID frame_timer_id = NULL;
static SDL_TimerID script_timer_id = NULL;
static SDL_TimerID network_timer_id = NULL;

Uint32 GameSystem::frame_event_interval = 0;
Uint32 GameSystem::script_event_interval = 0;
Uint32 GameSystem::network_event_interval = 0;

extern "C" Uint32 SDLCALL TimerCallback( Uint32 interval, void *param )
{
  Uint32 type = (Uint32)param;
  SDL_Event event;

  switch (type) {
  case FRAME_EVENT : 
    SDL_RemoveTimer( frame_timer_id );
    event.type = FRAME_EVENT;
    break;

  case SCRIPT_EVENT :
    SDL_RemoveTimer( script_timer_id );
    event.type = SCRIPT_EVENT;
    break;

  case NETWORK_EVENT :
    SDL_RemoveTimer( network_timer_id );
    event.type = NETWORK_EVENT;
    break;
  }

  SDL_PushEvent( &event );
}

void GameSystem::resetTimer(int ti, Uint32 type)
{
  SDL_Event event;  
  switch (type) {
  case FRAME_EVENT : 
    if (frame_timer_id != NULL) SDL_RemoveTimer( frame_timer_id );
    GameSystem::frame_event_interval = ti;
    if (ti > 0) { SDL_AddTimer(ti, TimerCallback, (void*)FRAME_EVENT); break; }
    event.type = FRAME_EVENT;
    SDL_PushEvent( &event );
    break;

  case SCRIPT_EVENT :
    if (script_timer_id != NULL) SDL_RemoveTimer( script_timer_id );
    GameSystem::script_event_interval = ti;
    if (ti > 0) { SDL_AddTimer(ti, TimerCallback, (void*)SCRIPT_EVENT); break; }
    event.type = SCRIPT_EVENT;
    SDL_PushEvent( &event );
    break;

  case NETWORK_EVENT :
    if (network_timer_id != NULL) SDL_RemoveTimer( network_timer_id );
    GameSystem::network_event_interval = ti;
    if (ti > 0) { SDL_AddTimer(ti, TimerCallback, (void*)NETWORK_EVENT); break; }
    event.type = NETWORK_EVENT;
    SDL_PushEvent( &event );
    break;
  }
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

	ImagePool::Init();
	ScreenLayer::GetInstance()->SetWindowMode(width, height, fullScreen, bpp);
	ScreenLayer::GetInstance()->SetTitle(title);


	L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "commond.lua");

	GameSystemLuaAPI::luaopen_gamesystem(L);	
	SceneManagerLuaAPI::luaopen_scene(L);
	SceneManager::GetInstance()->initL(L);
	EventHandler::GetInstance()->initL(L);
	LuaObject::initL(L);

	luaL_dofile(L, "test.lua"); 
}

void GameSystem::Run() {

  resetTimer(0, SCRIPT_EVENT);
  resetTimer(0, NETWORK_EVENT);
  
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

    case NETWORK_EVENT :
      EventHandler::GetInstance()->OnNetwork(); break;
    }	
  }
}

void GameSystem::Release() {
  	ScreenLayer::GetInstance()->Release();
	SceneManager::GetInstance()->Release();
	ImagePool::ShutDown();
}


#include "GameSystem.h"
#include "Exception.h"
#include <cstdio>

int main()
{
  GameSystem *game = GameSystem::GetInstance();
  game->Initialize(800, 600, false, 32, "test");

  try {
    game->Run();
  } catch (Exception &e) {
    fprintf(stderr, "%s\n", e.what());
  }

  game->Release();

  return 0;
}
 

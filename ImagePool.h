#ifndef __IMAGEPOOL__
#define __IMAGEPOOL__

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
 
namespace ImagePool
{
  void Init();
  void ShutDown();
  SDL_Surface* getImage(const std::string& name);
  SDL_Surface* loadImageFile(const std::string& name);
  SDL_Surface* loadImageRaw(std::string& name, int w, int h);
  void freeImage(const std::string& name);
}

#endif

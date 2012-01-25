#ifndef __SCENENODE__
#define __SCENENODE__

#include "GameObject.h"
#include <vector>

struct SceneNode {
  int ref;
  GameObject *obj;

  SceneNode *father;
  std::vector<SceneNode*> son;
  
  SceneNode(int ref) {
    this->ref = ref;
    obj = NULL;

    father = NULL;
    son.clear();
  }
  ~SceneNode() {
    if (obj) 
      delete obj;
  }
};


#endif

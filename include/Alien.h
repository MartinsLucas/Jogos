#ifndef ALIEN_H
#define ALIEN_H

#include <iostream>
#include <memory>
#include <queue>

#include "Component.h"
#include "GameObject.h"

using namespace std;

class Alien : public Component {
private:
  class Action {
  public:
    enum ActionType {MOVE, SHOOT};

    Vec2 position;
    ActionType type;

    Action(ActionType type, float x, float y);
  };

  int hp;
  Vec2 speed;
  int minionsAmount;

  std::queue<Action> taskQueue;
  std::vector<std::weak_ptr<GameObject>> minionArray;


public:
  Alien(GameObject &associated, int minionsAmount);
  ~Alien();

  void Start();
  void Render();
  void Update(float dt);
  bool Is(const char *type);
  Vec2 MoveTo(Vec2 target, float dt);
  GameObject& GetNearestMinion(Vec2 target);
};
#endif

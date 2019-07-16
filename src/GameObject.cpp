#include <algorithm>

#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() {
  this->isDead = false;
  this->box = Rect();
  this->started = false;
  this->angleDeg = 0;
}

void GameObject::Start() {
  for(auto &component : this->components) {
    component->Start();
  }
  this->started = true;
}

GameObject::~GameObject() {
  for (
    auto component = this->components.rbegin();
    component != this->components.rend();
    ++component
  ) {
    delete *component;
  }
  this->components.clear();
}

void GameObject::Update(float dt) {
  for(auto &component : this->components) {
    component->Update(dt);
  }
}

void GameObject::Render() {
  for(auto &component : this->components) {
    component->Render();
  }
}

bool GameObject::IsDead() {
    return(this->isDead);
}

void GameObject::RequestDelete() {
  this->isDead = true;
}

void GameObject::AddComponent(Component *component) {
  this->components.insert(this->components.begin(), component);
}


void GameObject::RemoveComponent(Component *component) {
  auto currentComponent = find(
    this->components.begin(),
    this->components.end(),
    component
  );

  if(currentComponent != this->components.end()) {
    this->components.erase(currentComponent);
  }
}

Component *GameObject::GetComponent(const char *type) {
  for(auto &component : this->components) {
    if(component->Is(type)){
      return(component);
    }
  }
  return(nullptr);
}

#include "State.h"

#define PI 3.1415926535

State::State() : music("assets/audio/stageState.ogg"){
  this->quitRequested = false;
  this->music.Play(-1);

  this->objectArray = std::vector<std::shared_ptr<GameObject>>();

  this->LoadAssets();
}

State::~State() {
  for (int index = this->objectArray.size() - 1 ; index >= 0 ; --index) {
    delete this->objectArray[index].get();
  }
  this->objectArray.clear();
}

void State::Render() {
  for(auto &object : this->objectArray) {
    object->Render();
  }
}

void State::LoadAssets() {
  GameObject *spriteObject = new GameObject();
  Sprite *background = new Sprite(*spriteObject, "assets/img/ocean.jpg");

  spriteObject->box.SetXPosition(0);
  spriteObject->box.SetYPosition(0);
  spriteObject->box.SetWidth(background->GetWidth());
  spriteObject->box.SetHeight(background->GetHeight());

  spriteObject->AddComponent(background);
  this->objectArray.emplace_back(spriteObject);

  // this->music = Music("assets/audio/stageState.ogg");
}

void State::Update(float delta) {
  this->Input();
  for(auto &object : this->objectArray) {
    object->Update(delta);
  }
  for(unsigned int index = 0 ; (index < this->objectArray.size()) ; index++) {
    if (this->objectArray[index].get()->IsDead()) {
      this->objectArray.erase(this->objectArray.begin() + index);
    }
  }
}

void State::AddObject(int mouseX, int mouseY) {
  // GameObject *object = new GameObject();
  // Sprite *sprite = new Sprite(*object, "assets/img/penguinface.png");
  // Sound *sound = new Sound(*object, "assets/audio/boom.wav");
  // Face *face = new Face(*object);
  //
  // object->box.SetXPosition(mouseX);
  // object->box.SetYPosition(mouseY);
  // object->box.SetWidth(sprite->GetWidth());
  // object->box.SetHeight(sprite->GetHeight());
  //
  // object->AddComponent(sprite);
  // object->AddComponent(sound);
  // // object->AddComponent(face);
  //
  // this->objectArray.emplace_back(object);
}

bool State::QuitRequested() {
  return(this->quitRequested);
}

// Third-party code begin
void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent returns 1 if events are found, otherwise zero
	while (SDL_PollEvent(&event)) {

		if(event.type == SDL_QUIT) {
			this->quitRequested = true;
		}

		// if(event.type == SDL_MOUSEBUTTONDOWN) {
    //
		// 	// Iterates backwards to always click on the object above
		// 	for(int index = this->objectArray.size() - 1 ; index >= 0 ; --index) {
		// 		GameObject* gameObject = (GameObject*) this->objectArray[index].get();
    //
		// 		if(gameObject->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
		// 			Face* face = (Face*)gameObject->GetComponent( "Face" );
		// 			if ( nullptr != face ) {
		// 				face->Damage(std::rand() % 10 + 10);
		// 				// Gets out of the loop (we only wants to hit one time)
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
		// if( event.type == SDL_KEYDOWN ) {
		// 	if( event.key.keysym.sym == SDLK_ESCAPE ) {
		// 		this->quitRequested = true;
		// 	}
		// 	else {
		// 		Vec2 objectPosition = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
		// 		AddObject((int)objectPosition.GetXPosition(), (int)objectPosition.GetYPosition());
		// 	}
		// }
	}
}
// Third-party code end

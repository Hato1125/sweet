#include "game_controller_test.hpp"
#include "game_controller_manager.hpp"

namespace sweet::test {
void game_controller_test::update() noexcept {
  if(sweet::game_controller_manager::get(0).is_pushing(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
    std::cout << "pushing LEFT key.\n";

  if(sweet::game_controller_manager::get(0).is_pushed(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
    std:: cout << "pushed DOWN key.\n";

  if(sweet::game_controller_manager::get(0).is_separate(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
    std::cout << "separate RIGHT key.\n";

  if(sweet::game_controller_manager::get(1).is_separate(SDL_CONTROLLER_BUTTON_DPAD_UP))
      std::cout << "separate UP key.\n";
}
}

#ifndef _LIBSWEET_TEST_GAME_CONTROLLER_TEST_HPP
#define _LIBSWEET_TEST_GAME_CONTROLLER_TEST_HPP

#include <iostream>

#include <scene.hpp>
#include <game_controller_manager.hpp>

namespace test {
struct game_controller_test : public sweet::scene_element {
  void update() override {
    if(sweet::game_controller_manager::get(0).is_pushing(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A))
      std::cout << "Pushing \"A\"Button.\n";

    if(sweet::game_controller_manager::get(0).is_pushed(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B))
      std::cout << "Pushed \"B\"Button.\n";

    if(sweet::game_controller_manager::get(0).is_separate(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X))
      std::cout << "Separate \"X\"Button.\n";

    if(sweet::game_controller_manager::get(1).is_pushing(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP))
      std::cout << "Pushing \"Up\"Button.\n";

    if(sweet::game_controller_manager::get(1).is_pushed(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN))
      std::cout << "Pushed \"Down\"Button.\n";

    if(sweet::game_controller_manager::get(1).is_separate(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT))
      std::cout << "Separate \"Left\"Button.\n";
  }
};
}

#endif

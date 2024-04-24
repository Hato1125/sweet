#ifndef _LIBSWEET_TEST_GAME_CONTROLLER_TEST_HPP
#define _LIBSWEET_TEST_GAME_CONTROLLER_TEST_HPP

#include <iostream>

#include <scene.hpp>
#include <gamecontroller_manager.hpp>

namespace test {
struct gamecontroller_test : public sweet::scene_element {
  void update() override {
    if(sweet::gamecontroller_manager::get(0).is_pushing(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A))
      std::cout << "Pushing \"A\"Button.\n";

    if(sweet::gamecontroller_manager::get(0).is_pushed(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B))
      std::cout << "Pushed \"B\"Button.\n";

    if(sweet::gamecontroller_manager::get(0).is_upped(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X))
      std::cout << "Upped \"X\"Button.\n";

    if(sweet::gamecontroller_manager::get(1).is_pushing(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP))
      std::cout << "Pushing \"Up\"Button.\n";

    if(sweet::gamecontroller_manager::get(1).is_pushed(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN))
      std::cout << "Pushed \"Down\"Button.\n";

    if(sweet::gamecontroller_manager::get(1).is_upped(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT))
      std::cout << "Upped \"Left\"Button.\n";
  }
};
}

#endif

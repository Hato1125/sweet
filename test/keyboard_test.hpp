#ifndef _LIBSWEET_TEST_KEYBOARD_TEST_HPP
#define _LIBSWEET_TEST_KEYBOARD_TEST_HPP

#include <iostream>

#include <scene.hpp>
#include <keyboard.hpp>

namespace test {
struct keyboard_test : public sweet::scene_element {
  void update() override {
    if(sweet::keyboard::is_pushing(SDL_SCANCODE_A))
      std::cout << "Pushing \"A\"Key.\n";

    if(sweet::keyboard::is_pushed(SDL_SCANCODE_W))
      std::cout << "Pushed \"W\"Key.\n";

    if(sweet::keyboard::is_upped(SDL_SCANCODE_S))
      std::cout << "Upped \"S\"Key.\n";
  }
};
}

#endif

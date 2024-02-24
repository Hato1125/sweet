#include "keyboard_test.hpp"

namespace sweet::test {
void keyboard_test::update() noexcept {
  if(sweet::keyboard::is_pushing(SDL_SCANCODE_A))
    std::cout << "pushing A key.\n";

  if(sweet::keyboard::is_pushed(SDL_SCANCODE_B))
    std:: cout << "pushed B key.\n";

  if(sweet::keyboard::is_separate(SDL_SCANCODE_C))
    std::cout << "separate C key.\n";
}
}

#include "game_controller_test.hpp"

namespace sweet::test {
void game_controller_test::update() noexcept {
  if(sweet::game_controller_manager::is_pushing(0, SDL_CONTROLLER_BUTTON_A))
    std::cout << "pushing A key.\n";

  if(sweet::game_controller_manager::is_pushed(0, SDL_CONTROLLER_BUTTON_B))
    std:: cout << "pushed B key.\n";

  if(sweet::game_controller_manager::is_separate(0, SDL_CONTROLLER_BUTTON_X))
    std::cout << "separate C key.\n";
}
}

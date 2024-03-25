#include <iostream>

#include <keyboard.hpp> 

#include "main.hpp"
#include "resource_manager_test.hpp"

namespace sweet::test {
void resource_manager_test::init() noexcept {
  if(auto rs = texture_manager.load(); !rs)
    std::cout << "test > " << rs.error();
}

void resource_manager_test::render() noexcept {
  if(sweet::keyboard::is_separate(SDL_SCANCODE_R)) {
    std::cout << "test > Running hot reload.\n";
    if(auto rs = texture_manager.hot_reload(); !rs)
      std::cout << "test > " << rs.error() << std::endl;
  }

  texture_manager["Test1"]->render(000, 000);
  texture_manager["Test2"]->render(100, 100);
  texture_manager["Test3"]->render(200, 200);
  texture_manager["Test4"]->render(300, 300);
}
}

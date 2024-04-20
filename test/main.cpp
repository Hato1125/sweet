#include <keyboard.hpp>
#include <game_controller_manager.hpp>
#include <scene_manager.hpp>

#include "main.hpp"
#include "test.hpp"

#ifdef main
# undef main
#endif

namespace test {
sweet::app app_state::app{};
sweet::frame_monitor app_state::monitor{};
}

int main(int argc, char **argv) {
  if(argc <= 1)
    return EXIT_FAILURE;

  test::app_state::app.init(argc, argv, {
    .on_inited = [&argv](){
      try {
        sweet::scene_manager::regist("test", std::make_shared<test::test_scene>(argv[1]));
        sweet::scene_manager::change("test");
      } catch(std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
      }
    }
  });

  test::app_state::app.run({
    .loop {
      .on_begin = [](){
        test::app_state::monitor.begin();
      },
      .on_event = [](SDL_Event &e){
        sweet::keyboard::update_event(e);
        sweet::game_controller_manager::update_event(e);
      },
      .on_update = [](){
        sweet::keyboard::update();
        sweet::game_controller_manager::update();

        if(sweet::keyboard::is_separate(SDL_SCANCODE_ESCAPE))
          test::app_state::app.end();

        sweet::scene_manager::update();
      },
      .on_render = [](){
        sweet::scene_manager::render();
      },
      .on_end = [](){
        test::app_state::monitor.end();
      },
    }
  });

  return EXIT_SUCCESS;
}

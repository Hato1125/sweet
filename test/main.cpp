#include <iostream>

#include <keyboard.hpp>
#include <gamecontroller_manager.hpp>
#include <scene_manager.hpp>

#include "main.hpp"
#include "test.hpp"

#ifdef main
# undef main
#endif

namespace test {
sweet::app app_state::app{};
sweet::frame app_state::monitor{};
}

int main(int argc, char **argv) {
  if(argc <= 1)
    return EXIT_FAILURE;

  try {
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
  } catch(std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  test::app_state::app.window
    .enable_resize()
    .set_size({ 1280, 720 })
    .set_min_size({ 1280, 720 })
    .set_max_size({ 1920, 1080 });

  test::app_state::app.renderer
    .disable_vsync();

  test::app_state::monitor
    .set_max_frame_rate(0.f)
    .set_update_frame_rate_sec(5.f);

  test::app_state::app.run({
    .loop {
      .on_begin = [](){
        test::app_state::monitor.begin();
      },
      .on_event = [](SDL_Event &e){
        sweet::keyboard::update_event(e);
        sweet::gamecontroller_manager::update_event(e);
      },
      .on_update = [](){
        sweet::keyboard::update();
        sweet::gamecontroller_manager::update();

        if(sweet::keyboard::is_upped(SDL_SCANCODE_ESCAPE))
          test::app_state::app.exit();
        else if(sweet::keyboard::is_upped(SDL_SCANCODE_Q))
          test::app_state::app.window.maximize();
        else if(sweet::keyboard::is_upped(SDL_SCANCODE_W))
          test::app_state::app.window.minimize();
        else if(sweet::keyboard::is_upped(SDL_SCANCODE_E))
          test::app_state::app.window.restore();
        else if(sweet::keyboard::is_upped(SDL_SCANCODE_R))
          test::app_state::app.window.enable_resize();
        else if(sweet::keyboard::is_upped(SDL_SCANCODE_T))
          test::app_state::app.window.disable_resize();

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

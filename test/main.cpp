#include "main.hpp"
#include "font_test.hpp"
#include "frame_monitor.hpp"
#include "texture_test.hpp"
#include "keyboard_test.hpp"
#include "game_controller_test.hpp"
#include "resource_bundle_test.hpp"

namespace sweet::test {
sweet::app main::app{ };
sweet::frame_monitor main::frame_monitor{ };
std::string main::run_test_name{ };
std::map<std::string, std::shared_ptr<sweet::test::test>> main::tests {
  { "font_test", std::make_shared<sweet::test::font_test>() },
  { "texture_test", std::make_shared<sweet::test::texture_test>() },
  { "keyboard_test", std::make_shared<sweet::test::keyboard_test>() },
  { "game_controller_test", std::make_shared<sweet::test::game_controller_test>() },
  { "resource_bundle_test", std::make_shared<sweet::test::resource_bundle_test>() },
};

std::expected<void, std::string> main::init(int argc, char **argv) noexcept {
  if(tests.empty())
    return std::unexpected{ "No tests defined." };

  if(argc < 2)
    return std::unexpected{ "No test specified." };
  run_test_name = argv[1];

  if(!tests.contains(run_test_name))
    return std::unexpected{ "The specified test does not exist." };

  if(auto result = app.init(argc, argv, { .on_inited = _init }); !result)
    return std::unexpected{ result.error() };

  app.is_auto_finish = false;
  app.window.set_title("sweet engine test")
    .set_max_size({ 1920, 1080 })
    .set_min_size({ 1280, 720 })
    .set_size(app.window.get_min_size());

  frame_monitor.set_max_frame_rate(60.);

  std::cout << "info > sdl_ver: " << sweet::get_sdl_version() << std::endl;
  std::cout << "info > sdl_image_ver: " << sweet::get_sdl_image_version() << std::endl;
  std::cout << "info > sdl_ttf_ver: " << sweet::get_sdl_ttf_version() << std::endl;
  std::cout << "info > sweet_ver: " << sweet::get_sweet_version() << std::endl;

  return{ };
}

std::expected<void, std::string> main::run() noexcept {
  sweet::game_controller ct{ 0 };
  app.run({
    .loop {
      .on_event = _event,
      .on_update = _update,
      .on_render = _render
    },
    .end {
      .on_finishing = _finish
    }
  });
  return{ };
}

void main::_init() noexcept {
  tests[run_test_name]->init();
}

void main::_update() noexcept {
  frame_monitor.begin();
  sweet::keyboard::update();
  sweet::game_controller_manager::update();

  tests[run_test_name]->update();
}

void main::_render() noexcept {
  tests[run_test_name]->render();
  frame_monitor.end();
}

void main::_finish() noexcept {
  tests[run_test_name]->finish();
}

void main::_event(SDL_Event &e) noexcept {
  sweet::keyboard::update_event(e);
  sweet::game_controller_manager::update_event(e);

  switch(e.type) {
    case SDL_KEYUP: {
      if(e.key.keysym.sym == SDLK_ESCAPE)
        app.end();
    } break;
  }
}
}

int main(int argc, char **argv) {
  if(auto result = sweet::test::main::init(argc, argv); !result) {
    std::cerr << "test > " << result.error() << std::endl;
    return EXIT_FAILURE;
  }

  if(auto result = sweet::test::main::run(); !result) {
    std::cerr << "test > " << result.error() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

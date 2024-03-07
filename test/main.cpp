#include "main.hpp"
#include "version.hpp"

#include <resource_bundle.hpp>

namespace sweet::test {
std::unique_ptr<sweet::app> main::app{ nullptr };
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

  app = std::make_unique<sweet::app>(argc, argv);
  if(auto result = app->init(); !result)
    return std::unexpected{ result.error() };

  app->is_auto_finish = false;
  app->window.set_title("sweet engine test")
    .set_max_size({ 1920, 1080 })
    .set_min_size({ 1280, 720 })
    .set_size(app->window.get_min_size());

  std::cout << "info > sdl_ver: " << sweet::get_sdl_version() << std::endl;
  std::cout << "info > sdl_image_ver: " << sweet::get_sdl_image_version() << std::endl;
  std::cout << "info > sdl_ttf_ver: " << sweet::get_sdl_ttf_version() << std::endl;
  std::cout << "info > sweet_ver: " << sweet::get_sweet_version() << std::endl;

  return{ };
}

std::expected<void, std::string> main::run() noexcept {
  app->run({
    .on_init = _init,
    .on_update = _update,
    .on_render = _render,
    .on_event = _event
  });
  return{ };
}

void main::_init() noexcept {
  tests[run_test_name]->init();
}

void main::_update() noexcept {
  sweet::keyboard::update();
  sweet::game_controller_manager::update();

  tests[run_test_name]->update();
}

void main::_render() noexcept {
  tests[run_test_name]->render();
}

void main::_finish() noexcept {
  tests[run_test_name]->finish();
}

void main::_event(SDL_Event &e) noexcept {
  sweet::keyboard::update_event(e);
  sweet::game_controller_manager::update_event(e);

  switch(e.type) {
    case SDL_QUIT: {
      goto FINISH;
    } break;
    case SDL_KEYUP: {
      if(e.key.keysym.sym == SDLK_ESCAPE)
        goto FINISH;
    } break;
    FINISH: {
      app->end({
        .on_finishing = _finish
      });
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

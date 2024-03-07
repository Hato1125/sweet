#ifndef _LIBSWEET_TEST_MAIN_HPP
#define _LIBSWEET_TEST_MAIN_HPP

#include <map>
#include <memory>
#include <string>
#include <expected>
#include <iostream>

#include <app.hpp>
#include <version.hpp>
#include <keyboard.hpp>
#include <game_controller_manager.hpp>

#include "test.hpp"
#include "font_test.hpp"
#include "texture_test.hpp"
#include "keyboard_test.hpp"
#include "game_controller_test.hpp"
#include "resource_bundle_test.hpp"

namespace sweet::test {
class main final {
public:
  main() = default;
  ~main() = default;

  static std::unique_ptr<sweet::app> app;
  static std::string run_test_name;
  static std::map<std::string, std::shared_ptr<sweet::test::test>> tests;

  static std::expected<void, std::string> init(int argc, char **argv) noexcept;
  static std::expected<void, std::string> run() noexcept;

private:
  static void _init() noexcept;
  static void _update() noexcept;
  static void _render() noexcept;
  static void _finish() noexcept;
  static void _event(SDL_Event &e) noexcept;
};
}

#endif

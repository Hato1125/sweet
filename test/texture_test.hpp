#ifndef _LIBSWEET_TEST_TEXTURE_TEST
#define _LIBSWEET_TEST_TEXTURE_TEST

#include <iostream>
#include <memory>

#include <scene.hpp>
#include <texture.hpp>

#include "main.hpp"

namespace test {
struct texture_test : public sweet::scene_element {
  std::unique_ptr<sweet::texture> texture;

  void active() override {
    texture = std::make_unique<sweet::texture>(
      test::app_state::app.renderer,
      test::app_state::app.get_current_dire() + "/test.png"
    );

    try {
      texture->load();
    } catch(std::runtime_error &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  void inactive() override {
    try {
      texture->unload();
    } catch(std::runtime_error &e) {
    }
  }

  void render() override {
    texture->render(100, 100);
  }
};
}

#endif

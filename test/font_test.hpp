#ifndef _LIBSWEET_TEST_FONT_TEST
#define _LIBSWEET_TEST_FONT_TEST

#include <iostream>
#include <memory>

#include <scene.hpp>
#include <font.hpp>

#include "main.hpp"

namespace test {
struct font_test : public sweet::scene_element {
  std::unique_ptr<sweet::font> font;
  std::unique_ptr<sweet::texture> font_texture;

  void active() override {
    font = std::make_unique<sweet::font>(
      test::app_state::app.renderer,
      test::app_state::app.get_current_dire() + "/test.ttf"
    );

    try {
      font->load();
      font_texture = std::move(font->create_text_font("Tst font.", { .size = 30 }));
    } catch(std::runtime_error &e) {
      std::cout << e.what() << std::endl;
    }
  }

  void inactive() override {
    try {
      font->unload();
    } catch(std::runtime_error &e) {
      std::cout << e.what() << std::endl;
    }
  }

  void render() override {
    font_texture->render(100, 100);
  }
};
}

#endif

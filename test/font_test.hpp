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
      test::app_state::app.get_current_dire_s() + "/test.ttf"
    );

    if(auto rs = font->load(); !rs)
      std::cout << "font test > " << rs.error() << std::endl;

    if(auto rs = font->create_text_font("Test font.", { .size = 30 }); !rs)
      std::cout << "font test > " << rs.error() << std::endl;
    else
      font_texture = std::move(rs.value());
  }

  void inactive() override {
    if(auto rs = font->unload(); !rs)
      std::cout << rs.error() << std::endl;
  }

  void render() override {
    font_texture->render(100, 100);
  }
};
}

#endif

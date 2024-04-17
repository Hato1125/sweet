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
      test::app_state::app.get_current_dire_s() + "/test.png"
    );

    if(auto rs = texture->load(); !rs)
      std::cout << "texture test > " << rs.error() << std::endl;
  }

  void inactive() override {
    if(auto rs = texture->unload(); !rs)
      std::cout << rs.error() << std::endl;
  }

  void render() override {
    texture->render(100, 100);
  }
};
}

#endif

#ifndef _LIBSWEET_TEST_BOX_TEST_HPP
#define _LIBSWEET_TEST_BOX_TEST_HPP

#include <scene.hpp>
#include <box.hpp>

#include "main.hpp"

namespace test {
struct box_test : public sweet::scene_element {
  sweet::box box{ test::app_state::app.renderer };

  void active() override {
    box
      .set_size({ 200, 200 })
      .set_color(sweet::pallet::white);
  }

  void render() override {
    box.fill_render(100, 100);
    box.border_render(100, 310);
  }
};
}

#endif

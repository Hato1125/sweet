#ifndef _LIBSWEET_TEST_TEST_HPP
#define _LIBSWEET_TEST_TEST_HPP

#include <stdexcept>
#include <string>
#include <map>

#include <scene.hpp>

#include "box_test.hpp"
#include "font_test.hpp"
#include "texture_test.hpp"
#include "keyboard_test.hpp"

namespace test {
class test_scene : public sweet::scene {
  public:
  test_scene(const std::string &name) {
    std::map<std::string, std::shared_ptr<sweet::scene_element>> tests {
      { "Box", std::make_shared<test::box_test>() },
      { "Font", std::make_shared<test::font_test>() },
      { "Texture", std::make_shared<test::texture_test>() },
      { "Keyboard", std::make_shared<test::keyboard_test>() },
    };

    if(!tests.contains(name))
      throw std::runtime_error("There is no \"" + name +"\" test.");
    elements.push_back(tests[name]);
  }
};
}

#endif

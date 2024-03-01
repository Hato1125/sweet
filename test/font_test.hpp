#ifndef _LIBSWEET_TEST_FONT_TEST_HPP
#define _LIBSWEET_TEST_FONT_TEST_HPP

#include <memory>
#include <iostream>

#include <font.hpp>

#include "test.hpp"

namespace sweet::test {
struct font_test : public sweet::test::test {
  sweet::font *font{ };
  std::unique_ptr<sweet::texture> font_text{ };

  void init() noexcept override;
  void render() noexcept override;
  void finish() noexcept override;
};
}

#endif

#ifndef _LIBSWEET_TEST_TEXTURE_TEST_HPP
#define _LIBSWEET_TEST_TEXTURE_TEST_HPP

#include <iostream>

#include <texture.hpp>

#include "test.hpp"

namespace sweet::test {
struct texture_test : public sweet::test::test {
  sweet::texture *texture{ };

  void init() noexcept override;
  void render() noexcept override;
  void finish() noexcept override;
};
}

#endif

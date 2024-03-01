#ifndef _LIBSWEET_TEST_RESOURCE_BUNDLE_TEST_HPP
#define _LIBSWEET_TEST_RESOURCE_BUNDLE_TEST_HPP

#include <iostream>

#include <texture.hpp>
#include <keyboard.hpp>
#include <resource_bundle.hpp>

#include "test.hpp"

namespace sweet::test {
struct resource_bundle_test : public sweet::test::test {
  sweet::resource_bundle<sweet::texture> bundle;

  void init() noexcept override;
  void render() noexcept override;
  void finish() noexcept override;
};
}

#endif

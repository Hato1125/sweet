#ifndef _LIBSWEET_TEST_KEYBOARD_TEST_HPP
#define _LIBSWEET_TEST_KEYBOARD_TEST_HPP

#include <iostream>

#include <keyboard.hpp>

#include "test.hpp"

namespace sweet::test {
struct keyboard_test : public sweet::test::test {
  void update() noexcept override;
};
}

#endif

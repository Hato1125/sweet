#ifndef _LIBSWEET_TEST_GAME_CONTROLLER_TEST_HPP
#define _LIBSWEET_TEST_GAME_CONTROLLER_TEST_HPP

#include <iostream>

#include <game_controller.hpp>

#include "test.hpp"

namespace sweet::test {
struct game_controller_test : public sweet::test::test {
  void update() noexcept override;
};
}

#endif

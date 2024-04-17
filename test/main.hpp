#ifndef _LIBSWEET_TEST_MAIN_HPP
#define _LIBSWEET_TEST_MAIN_HPP

#include <app.hpp>
#include <frame_monitor.hpp>

namespace test {
struct app_state {
  app_state() = delete;
  ~app_state() = delete;

  static sweet::app app;
  static sweet::frame_monitor monitor;
};
}

#endif

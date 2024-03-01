#ifndef _LIBSWEET_TEST_TEST_HPP
#define _LIBSWEET_TEST_TEST_HPP

namespace sweet::test {
struct test {
  virtual void init() noexcept { }
  virtual void update() noexcept { }
  virtual void render() noexcept { }
  virtual void finish() noexcept { }
};
}

#endif

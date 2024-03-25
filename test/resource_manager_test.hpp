#ifndef _LIBSWEET_TEST_RESOURCE_MANAGER_TEST_HPP
#define _LIBSWEET_TEST_RESOURCE_MANAGER_TEST_HPP

#include <resource_manager.hpp>
#include <texture.hpp>

#include "test.hpp"
#include "main.hpp"

namespace sweet::test {
struct resource_manager_test : public sweet::test::test {
  sweet::texture_manager<> texture_manager {
    std::make_shared<sweet::texture>(main::app.renderer),
    {
      { "Test1", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "Test2", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "Test3", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "Test4", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "Test5", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "Test6", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "Test7", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "Test8", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
    }
  };

  void init() noexcept override;
  void render() noexcept override;
};
}

#endif

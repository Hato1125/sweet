#include "resource_bundle_test.hpp"
#include "main.hpp"

namespace sweet::test {
void resource_bundle_test::init() noexcept {
  bundle = sweet::texture_bundle<>(
    std::make_shared<sweet::texture>(main::app.renderer),
    std::unordered_map<std::string, std::shared_ptr<sweet::texture>> {
      { "test_texture0", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test0.png") },
      { "test_texture1", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test1.png") },
      { "test_texture2", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test2.png") },
      { "test_texture3", std::make_shared<sweet::texture>(main::app.renderer, main::app.get_current_dire_s() + "/test3.png") },
    }
  );

  if(auto result = bundle.load(); !result)
    std::cout << "test > " << result.error() << std::endl;
}


void resource_bundle_test::render() noexcept {
  if(sweet::keyboard::is_separate(SDL_SCANCODE_R)) {
    std::cout << "test > Perform a hot reload!!!\n";
    if(auto result = bundle.hot_reload(); !result)
      std::cout << "test > " << result.error() << std::endl;
  }

  if(bundle["test_texture0"].has_value())
    bundle["test_texture0"].value().value->render(000, 000);

  if(bundle["test_texture1"].has_value())
    bundle["test_texture1"].value().value->render(100, 000);

  if(bundle["test_texture2"].has_value())
    bundle["test_texture2"].value().value->render(200, 000);

  if(bundle["test_texture3"].has_value())
    bundle["test_texture3"].value().value->render(300, 000);
}

void resource_bundle_test::finish() noexcept {
  if(auto result = bundle.unload(); !result)
    std::cout << "test > " << result.error() << std::endl;
}
}

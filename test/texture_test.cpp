#include "texture_test.hpp"

namespace sweet::test {
void texture_test::init() noexcept {
  texture = new sweet::texture(
    main::app->renderer,
    main::app->get_current_dire_s() + "/test.png"
  );
  if(auto result = texture->load(); !result)
    std::cerr << "test > " << result.error() << std::endl;
}

void texture_test::render() noexcept {
  if(!texture)
    return;

  texture->render(0, 0);
}

void texture_test::finish() noexcept {
  if(!texture)
    return;

  if(auto result = texture->unload(); !result)
    std::cerr << "test > " << result.error() << std::endl;
  delete texture;
}
}

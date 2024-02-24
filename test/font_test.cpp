#include "font_test.hpp"

namespace sweet::test {
void font_test::init() noexcept {
  font = new sweet::font(
    main::app->renderer,
    main::app->get_current_dire_s() + "/test.otf"
  );
  if(auto result = font->load(); !result) {
    std::cerr << "test > " << result.error() << std::endl;
    return;
  }

  auto result = font->create_utf8_text_font("TestString", {
    .size = 50
  });
  if(!result) {
    std::cerr << "test > " << result.error() << std::endl;
    return;
  }
  font_text = std::move(result.value());
}

void font_test::render() noexcept {
  if(!font || !font_text)
    return;

  font_text->
     set_render_h_pos(sweet::horizontal::center)
    .set_render_v_pos(sweet::vertical::center)
    .render(
       main::app->window.get_size_width() / 2.f,
       main::app->window.get_size_height() / 2.f
     );
}

void font_test::finish() noexcept {
  if(!font)
    return;

  if(auto result = font->unload(); !result)
    std::cerr << "test > " << result.error() << std::endl;
  delete font;
}
}

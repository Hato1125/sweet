#include <iostream>

#include <app.hpp>
#include <texture.hpp>
#include <resource_bundle.hpp>

int main(int argc, char **argv) {
  sweet::app app{ argc, argv };

  if(auto result = app.init(); !result) {
    std::cerr << result.error();
    return EXIT_FAILURE;
  }

  app.window
    .set_title("sweet_engine")
    .set_size({ 1280, 720 })
    .set_max_size({ 1280, 720 })
    .set_min_size({ 1280, 720 });

  app.renderer
    .enable_vsync()
    .set_color({ 255, 0, 0 });

  sweet::resource_bundle<sweet::texture> bundle {
    std::make_shared<sweet::texture>(app.renderer),
    {
      { "Test0", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
    }
  };

  app.run({
    .on_init = [&app, &bundle]() {
      auto results = bundle.load();
      if(!results) {
        for(const auto error : results.error())
          std::cerr << error << std::endl;
      }
    },
    .on_render = [&app, &bundle]() {
      bundle["Test0"]->set_scale_mode(sweet::scale_mode::linear)
        .set_render_h_pos(sweet::horizontal::center)
        .set_render_v_pos(sweet::vertical::center)
        .set_scale_width(0.25f)
        .set_scale_height(0.25f)
        .render(
          app.window.get_size().width / 2.f,
          app.window.get_size().height / 2.f
        );
    },
    .on_event = [&app, &bundle](SDL_Event &event) {
      if(event.type != SDL_KEYUP)

      switch(event.key.keysym.sym) {
        case SDLK_ESCAPE: {
          app.end({
            .on_finishing = [&bundle]() {
              auto results = bundle.unload();
              if(!results) {
                for(const auto error : results.error())
                  std::cerr << error << std::endl;
              }
            }
          });
          break;
        }
        case SDLK_SPACE: {
          auto results = bundle.release();
          if(!results) {
            for(const auto error : results.error())
              std::cerr << error << std::endl;
          }
          break;
        }
      }
    },
  });
}

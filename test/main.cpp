#include <iostream>

#include <app.hpp>
#include <texture.hpp>

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

  sweet::texture image{ app.renderer, std::string{"/home/hato/画像/fm.png" } };
  image.set_scale_width(0.4f)
    .set_scale_height(0.4f);

  app.run({
    .on_init = [&app, &image]() {
      image.load();
    },
    .on_render = [&image]() {
      image.render(0.f, 0.f);
    },
    .on_event = [&app](SDL_Event &event) {
      if(event.type == SDL_KEYDOWN)
        app.renderer.set_color({ 0, 0, 255 });
      else if(event.type == SDL_KEYUP)
        app.end();
    },
  });
}

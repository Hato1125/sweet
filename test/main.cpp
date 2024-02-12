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

  sweet::texture image{
    app.renderer, std::string{ "/Users/toha/Pictures/fw.png" }
  };

  image
    .set_scale_width(1.5f)
    .set_scale_height(1.5f);

  app.run({
    .on_init = [&app, &image]() {
      if(auto result = image.load(); !result)
        std::cerr << result.error() << std::endl;
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

#include <iostream>

#include <app.hpp>

int main(int argc, char **argv) {
  sweet::app app{ argc, argv };

  if(auto result = app.init(); !result) {
    std::cout << "--Error Log--\n";
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

  app.run({
    .on_event = [&app](SDL_Event &event){
      if(event.type == SDL_KEYDOWN)
        app.renderer.set_color({ 0, 0, 255 });
      else if(event.type == SDL_KEYUP)
        app.end();
    }
  });
}

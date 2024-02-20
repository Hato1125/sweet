#include <iostream>

#include <app.hpp>
#include <font.hpp>
#include <keyboard.hpp>
#include <resource_bundle.hpp>
#include <game_controller_manager.hpp>

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
    .set_color({ 0, 0, 0 });

  sweet::font font{
    app.renderer,
    std::string{ "/Users/toha/Library/Fonts/RobotoMonoNerdFont-Bold.ttf" }
  };
  std::unique_ptr<sweet::texture> font_texture;

  app.run({
    .on_init = [&app, &font, &font_texture]() {
      if(auto result = font.load();  !result) {
        std::cerr << result.error() << std::endl;
        app.end();
        return;
      }
      {
        auto result = font.create_utf8_text_font(
          "TestString",
          {
            .size = 50,
            .color = { 255, 255, 255 },
            .style = sweet::font_style::normal,
          }
        );
        if(!result) {
          std::cerr << result.error() << std::endl;
          app.end();
          return;
        }
        font_texture = std::move(result.value());
      }
    },
    .on_update = [&app]() {
    	sweet::game_controller_manager::update();
      sweet::keyboard::update();
      if(sweet::keyboard::is_pushing(SDL_SCANCODE_A))
        std::cout << "A\n";

      if(sweet::keyboard::is_pushed(SDL_SCANCODE_B))
        std::cout << "B\n";

      if(sweet::keyboard::is_separate(SDL_SCANCODE_C))
        std::cout << "C\n";

      if(sweet::game_controller_manager::is_pushed(0, SDL_CONTROLLER_BUTTON_A))
        std::cout << "P1 A Button\n";

      if(sweet::game_controller_manager::is_pushed(1, SDL_CONTROLLER_BUTTON_A))
      	std::cout << "P2 A Button\n";
    },
    .on_render = [&app, &font_texture]() {
      if(font_texture)
        font_texture->render(0, 0);
    },
    .on_event = [&app, &font, &font_texture](SDL_Event &event) {
    	sweet::game_controller_manager::update_event(event);
      sweet::keyboard::update_event(event);
      if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
        app.end({
          .on_finishing = [&font, &font_texture](){
            font.unload();
            font_texture->unload();
          }
        });
      }
    },
  });
}

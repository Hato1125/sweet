#include <mutex>
#include <iostream>

#include <app.hpp>
#include <resource_loader.hpp>

#include <SDL_image.h>

class texture : sweet::resource {
public:
  texture(sweet::renderer &rend) : _renderer{ rend } {}

  std::expected<void, std::string> load() noexcept override {
    if(!_renderer.get_sdl_renderer())
      return std::unexpected{ "れんだらーがぬるぽー" };

    _texture = IMG_LoadTexture(
      _renderer.get_sdl_renderer(),
      "/home/hato/画像/fm.png"
    );

    if(!_texture)
      return std::unexpected{ "よみこみしっぱい" };

    return{ };
  }

  std::expected<void, std::string> unload() noexcept override {
    if(!_texture)
      return std::unexpected{ "はきするてくすちゃがねえ" };
    return{ };
  }

  std::expected<void, std::string> release() noexcept override {
    if(!_texture)
      return std::unexpected{ "はきするてくすちゃがねえ" };
    return{ };
  }

private:
  sweet::renderer &_renderer;
  SDL_Texture *_texture;
};

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

  app.run({
    .on_init = [&app]() {
      sweet::basic_resource_loader<texture> _loader {
        std::make_shared<texture>(app.renderer),
        {
          { "TEST0", std::make_shared<texture>(app.renderer) },
          { "TEST1", std::make_shared<texture>(app.renderer) },
          { "TEST2", std::make_shared<texture>(app.renderer) },
        }
      };
      auto result = _loader.load();
      if(!result) {
        for(const auto err : result.error())
          std::cout << err << std::endl;
      }
    },
    .on_event = [&app](SDL_Event &event) {
      if(event.type == SDL_KEYDOWN)
        app.renderer.set_color({ 0, 0, 255 });
      else if(event.type == SDL_KEYUP)
        app.end();
    }
  });
}

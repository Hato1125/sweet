#include <mutex>
#include <iostream>

#include <resource.hpp>
#include <resource_bundle.hpp>

#include <app.hpp>
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
    std::cout << "よみこみせいこう\n";

    return{ };
  }

  std::expected<void, std::string> unload() noexcept override {
    if(!_texture)
      return std::unexpected{ "はきするてくすちゃがねえ" };
    std::cout << "はきせいこう\n";
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
      std::cout << "loading...\n";
      sweet::resource_bundle<texture> bundle {
        std::make_shared<texture>(app.renderer),
        {
          { "TEST1", std::make_shared<texture>(app.renderer) },
          { "TEST2", std::make_shared<texture>(app.renderer) },
          { "TEST3", std::make_shared<texture>(app.renderer) },
          { "TEST4", std::make_shared<texture>(app.renderer) },
          { "TEST5", std::make_shared<texture>(app.renderer) },
        }
      };

      // load
      {
        auto results = bundle.load();
        if(!results) {
          for(const auto error : results.error())
            std::cout << error << std::endl;
        }
      }

      // unload
      {
        auto results = bundle.unload();
        if(!results) {
          for(const auto error : results.error())
            std::cout << error << std::endl;
        }
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

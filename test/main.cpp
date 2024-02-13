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
      { "Test1", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test2", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test3", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test4", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test5", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test6", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test7", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test8", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
      { "Test9", std::make_shared<sweet::texture>(app.renderer, std::string{ "/Users/toha/Pictures/4CAB7F45-EFBF-4EC2-B8E9-26F506FC99FB.png" }) },
    }
  };

  app.run({
    .on_init = [&app, &bundle]() {
      auto results = bundle.load();
      if(!results) {
        for(const auto error : results.error())
          std::cout << error << std::endl;
      }
    },
    .on_render = [&app, &bundle]() {
      //bundle.get("Test0").render(0, 0);
    },
    .on_event = [&app](SDL_Event &event) {
      if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        app.end();
    },
  });
}

/*--------------------------------------------------------------------------------*/
/*                                   MIT License                                  */
/*                          Copyright (c) 2024 Hato1125                           */
/*--------------------------------------------------------------------------------*/
/* Permission is hereby granted, free of charge, to any person obtaining a copy   */
/* of this software and associated documentation files (the "Software"), to deal  */
/* in the Software without restriction, including without limitation the rights   */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      */
/* copies of the Software, and to permit persons to whom the Software is          */
/* furnished to do so, subject to the following conditions:                       */
/*                                                                                */
/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software.                                */
/*                                                                                */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/* SOFTWARE.                                                                      */
/*--------------------------------------------------------------------------------*/

#include "app.hpp"

namespace sweet {
app::app(int argc, char **argv)
  noexcept : window{ },
    renderer{ window },
    is_auto_finish{ true },
    _is_finish{ false } {
  _current_path = std::filesystem::path{ argv[0] };
  _current_dire = _current_path.parent_path();
}

app::~app() noexcept {
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
}

std::expected<void, std::string> app::init() noexcept {
  if(auto result = window.create(); !result)
    return std::unexpected{ result.error() };

  if(auto result = renderer.create(); !result)
    return std::unexpected{ result.error() };

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    return std::unexpected{ "Failed to initialize SDL." };

  if(IMG_Init(IMG_INIT_PNG) < 0)
    return std::unexpected{ "Failed to initialize SDL_image." };

  if(TTF_Init() < 0)
    return std::unexpected{ "Failed to initialize SDL_ttf." };

  return{ };
}

void app::run(const app_loop &loop) noexcept {
  if(!window || !renderer)
    return;

  if(loop.on_init)
    loop.on_init();

  SDL_Event sdl_event;
  while(!_is_finish) {
    while(SDL_PollEvent(&sdl_event)) {
      if(is_auto_finish && sdl_event.type == SDL_QUIT)
        return;

      if(loop.on_event)
        loop.on_event(sdl_event);
    }

    if(loop.on_update)
      loop.on_update();

    renderer.clear();
    if(loop.on_render)
      loop.on_render();
    renderer.present();
  }
}

void app::end(const app_end &end) noexcept {
  if(end.on_finishing)
    end.on_finishing();

  [[maybe_unused]] auto wd = window.destroy();
  [[maybe_unused]] auto rd = renderer.destroy();
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();

  if(end.on_finished)
    end.on_finished();

  _is_finish = true;
}

std::filesystem::path app::get_current_path() const noexcept {
  return _current_path;
}

std::filesystem::path app::get_current_dire() const noexcept {
  return _current_dire;
}

std::string app::get_current_path_s() const noexcept {
  return _current_path.string();
}

std::string app::get_current_dire_s() const noexcept {
  return _current_dire.string();
}
}

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
app::app()
  noexcept : window{ },
    renderer{ window },
    is_auto_finish{ true },
    _is_finish{ false } {
}

app::~app() noexcept {
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
}

std::expected<void, std::string> app::init(
  int argc,
  char **argv,
  const app_init_callbacks &init
) noexcept {
  _current_path = std::filesystem::path{ argv[0] };
  _current_dire = _current_path.parent_path();

  if(init.on_initing)
    init.on_initing();

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

  if(init.on_inited)
    init.on_inited();

  return{ };
}

void app::run(const app_run_callbacks &run) noexcept {
  if(!window || !renderer)
    return;

  SDL_Event sdl_event;
  while(!_is_finish) {
    if(run.loop.on_begin)
      run.loop.on_begin();

    while(SDL_PollEvent(&sdl_event)) {
      if(is_auto_finish && sdl_event.type == SDL_QUIT)
        goto FINISH;

      if(run.loop.on_event)
        run.loop.on_event(sdl_event);
    }

    if(run.loop.on_update)
      run.loop.on_update();

    renderer.rendering(run.loop.on_render);

    if(run.loop.on_end)
      run.loop.on_end();
  }
FINISH:

  if(run.end.on_finishing)
    run.end.on_finishing();

  SDL_Quit();
  IMG_Quit();
  TTF_Quit();

  if(run.end.on_finished)
      run.end.on_finished();
}

void app::end() noexcept {
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

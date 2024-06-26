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

#include <filesystem>
#include <stdexcept>

#include <SDL_hints.h>

#include "app.hpp"

namespace sweet {
app::app()
  noexcept:  _is_exit{ false },
             _is_auto_exit{ true },
             window{ },
             renderer{ window } {
}

app::~app() noexcept {
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
}

void app::init(
  int argc,
  char **argv,
  const app_init_callbacks &init
) {
  _current_path = argv[0];
  std::filesystem::path current{ argv[0] };
  _current_dire = current.parent_path().string();

  if(init.on_initing)
    init.on_initing();

  window.create();
  renderer.create();

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw std::runtime_error("Failed to initialize SDL.");

  if(IMG_Init(IMG_INIT_PNG) < 0)
    throw std::runtime_error("Failed to initialize SDL_image.");

  if(TTF_Init() < 0)
    throw std::runtime_error("Failed to initialize SDL_ttf.");

  if(init.on_inited)
    init.on_inited();

}

app &app::enable_auto_exit() noexcept {
  _is_auto_exit = true;
  return *this;
}

app &app::disable_auto_exit() noexcept {
  _is_auto_exit = false;
  return *this;
}

void app::run(const app_run_callbacks &run) noexcept {
  if(!window || !renderer)
    return;

  SDL_Event sdl_event;
  while(!_is_exit) {
    if(run.loop.on_begin)
      run.loop.on_begin();

    while(SDL_PollEvent(&sdl_event)) {
      if(_is_auto_exit && sdl_event.type == SDL_QUIT)
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

void app::exit() noexcept {
  _is_exit = true;
}

std::string app::get_current_path() const noexcept {
  return _current_path;
}

std::string app::get_current_dire() const noexcept {
  return _current_dire;
}
}

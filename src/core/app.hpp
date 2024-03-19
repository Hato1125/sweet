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

#ifndef _LIBSWEET_CORE_APP_HPP
#define _LIBSWEET_CORE_APP_HPP

#include <string>
#include <expected>
#include <functional>
#include <filesystem>

#include <SDL_ttf.h>
#include <SDL_video.h>
#include <SDL_image.h>

#include "window.hpp"
#include "renderer.hpp"

namespace sweet {
struct app_init_callbacks {
  std::function<void()> on_initing;
  std::function<void()> on_inited;
};

struct app_loop_callbacks {
  std::function<void()> on_begin;
  std::function<void(SDL_Event&)> on_event;
  std::function<void()> on_update;
  std::function<void()> on_render;
  std::function<void()> on_end;
};

struct app_end_callbacks {
  std::function<void()> on_finishing;
  std::function<void()> on_finished;
};

struct app_run_callbacks {
  app_loop_callbacks loop;
  app_end_callbacks end;
};

class app {
public:
  bool is_auto_finish;

  sweet::window window;
  sweet::renderer renderer;

  app() noexcept;
  ~app() noexcept;

  std::expected<void, std::string> init(
    int argc,
    char **argv,
    const app_init_callbacks &init = { }
  ) noexcept;

  void run(const app_run_callbacks &run = { }) noexcept;
  void end() noexcept;

  std::filesystem::path get_current_path() const noexcept;
  std::filesystem::path get_current_dire() const noexcept;

  std::string get_current_path_s() const noexcept;
  std::string get_current_dire_s() const noexcept;

private:
  bool _is_finish;

  std::filesystem::path _current_path;
  std::filesystem::path _current_dire;
};
}

#endif

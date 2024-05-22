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

#include <stdexcept>

#include "window.hpp"

namespace sweet {
void window::create() {
  if(_sdl_window)
    return;

  _sdl_window.reset(SDL_CreateWindow(
    nullptr,
    1280,
    720,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOW_SHOWN
  ));
  if(!_sdl_window)
    throw std::runtime_error("Failed to create SDL_Window.");
}

void window::destroy() {
  if(!_sdl_window)
    throw std::runtime_error("Window has not been created yet.");
  _sdl_window.reset();
}

window &window::show() noexcept {
  SDL_ShowWindow(get_sdl_window());
  return *this;
}

window &window::hide() noexcept {
  SDL_ShowWindow(get_sdl_window());
  return *this;
}

window &window::enable_resize() noexcept {
  SDL_SetWindowResizable(get_sdl_window(), SDL_TRUE);
  return *this;
}

window &window::disable_resize() noexcept {
  SDL_SetWindowResizable(get_sdl_window(), SDL_FALSE);
  return *this;
}

window &window::maximize() noexcept {
  SDL_MaximizeWindow(get_sdl_window());
  return *this;
}

window &window::minimize() noexcept {
  SDL_MinimizeWindow(get_sdl_window());
  return *this;
}

window &window::restore() noexcept {
  SDL_RestoreWindow(get_sdl_window());
  return *this;
}

window &window::set_title(const std::string &title) noexcept {
  SDL_SetWindowTitle(get_sdl_window(), title.c_str());
  return *this;
}

window &window::set_pos(const sweet::point<int32_t> &pos) noexcept {
  SDL_SetWindowPosition(get_sdl_window(), pos.x, pos.y);
  return *this;
}

window &window::set_size(const sweet::size<uint32_t> &size) noexcept {
  SDL_SetWindowSize(get_sdl_window(), size.width, size.height);
  return *this;
}

window &window::set_min_size(const sweet::size<uint32_t> &size) noexcept {
  SDL_SetWindowMinimumSize(get_sdl_window(), size.width, size.height);
  return *this;
}

window &window::set_max_size(const sweet::size<uint32_t> &size) noexcept {
  SDL_SetWindowMaximumSize(get_sdl_window(), size.width, size.height);
  return *this;
}

std::string window::get_title() const noexcept {
  return SDL_GetWindowTitle(get_sdl_window());
}

sweet::point<int32_t> window::get_pos() const noexcept {
  int32_t x;
  int32_t y;
  SDL_GetWindowPosition(get_sdl_window(), &x, &y);

  return{ x, y };
}

sweet::size<uint32_t> window::get_size() const noexcept {
  int32_t width;
  int32_t height;
  SDL_GetWindowSize(get_sdl_window(), &width, &height);

  return {
    static_cast<uint32_t>(width),
    static_cast<uint32_t>(height)
  };
}

sweet::size<uint32_t> window::get_min_size() const noexcept {
  int32_t width;
  int32_t height;
  SDL_GetWindowMinimumSize(get_sdl_window(), &width, &height);

  return {
    static_cast<uint32_t>(width),
    static_cast<uint32_t>(height)
  };
}

sweet::size<uint32_t> window::get_max_size() const noexcept {
  int32_t width;
  int32_t height;
  SDL_GetWindowMaximumSize(get_sdl_window(), &width, &height);

  return {
    static_cast<uint32_t>(width),
    static_cast<uint32_t>(height)
  };
}

SDL_Window *window::get_sdl_window() const noexcept {
  return _sdl_window.get();
}

bool window::operator ==(const window &window) const noexcept {
  return get_sdl_window() == window.get_sdl_window();
}

bool window::operator !=(const window &window) const noexcept {
  return get_sdl_window() != window.get_sdl_window();
}

window::operator bool() const noexcept {
  return get_sdl_window() != nullptr;
}
}

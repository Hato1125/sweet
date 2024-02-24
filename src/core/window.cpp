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

#include "window.hpp"
#include <SDL_video.h>

namespace sweet {
window::window()
  noexcept : _sdl_window{ nullptr, SDL_DestroyWindow } {
}

std::expected<void, std::string> window::create() noexcept {
  if(_sdl_window)
    return std::unexpected{ "The window has already been created." };

  constexpr sweet::rect32_t window_rect {
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    1280,
    720
  };

  SDL_Window *sdl_window = SDL_CreateWindow(
    nullptr,
    window_rect.x,
    window_rect.y,
    window_rect.width,
    window_rect.height,
    SDL_WINDOW_SHOWN
  );

  if(!sdl_window)
    return std::unexpected{ "Failed to create SDL_Window." };

  _sdl_window.reset(sdl_window);
  return{ };
}

std::expected<void, std::string> window::destroy() noexcept {
  if(!_sdl_window)
    return std::unexpected{ "Window has not been created yet." };

  _sdl_window.reset();
  return{ };
}

void window::show() noexcept {
  SDL_ShowWindow(get_sdl_window());
}

void window::hide() noexcept {
  SDL_ShowWindow(get_sdl_window());
}

window &window::set_title(const std::string &title) noexcept {
  SDL_SetWindowTitle(get_sdl_window(), title.c_str());
  return *this;
}

window &window::set_pos(const sweet::point32_t &pos) noexcept {
  SDL_SetWindowPosition(get_sdl_window(), pos.x, pos.y);
  return *this;
}

window &window::set_size(const sweet::usize32_t &size) noexcept {
  SDL_SetWindowSize(get_sdl_window(), size.width, size.height);
  return *this;
}

window &window::set_min_size(const sweet::usize32_t &size) noexcept {
  SDL_SetWindowMinimumSize(get_sdl_window(), size.width, size.height);
  return *this;
}

window &window::set_max_size(const sweet::usize32_t &size) noexcept {
  SDL_SetWindowMaximumSize(get_sdl_window(), size.width, size.height);
  return *this;
}

window &window::set_pos(int32_t x, int32_t y) noexcept {
  SDL_SetWindowPosition(get_sdl_window(), x, y);
  return *this;
}

window &window::set_size(uint32_t width, uint32_t height) noexcept {
  SDL_SetWindowSize(get_sdl_window(), width, height);
  return *this;
}

window &window::set_min_size(uint32_t width, uint32_t height) noexcept {
  SDL_SetWindowMinimumSize(get_sdl_window(), width, height);
  return *this;
}

window &window::set_max_size(uint32_t width, uint32_t height) noexcept {
  SDL_SetWindowMaximumSize(get_sdl_window(), width, height);
  return *this;
}

std::string window::get_title() const noexcept {
  return SDL_GetWindowTitle(get_sdl_window());
}

sweet::point32_t window::get_pos() const noexcept {
  int32_t x;
  int32_t y;
  SDL_GetWindowPosition(get_sdl_window(), &x, &y);

  return{ x, y };
}

sweet::usize32_t window::get_size() const noexcept {
  int32_t width;
  int32_t height;
  SDL_GetWindowSize(get_sdl_window(), &width, &height);

  return {
    static_cast<uint32_t>(width),
    static_cast<uint32_t>(height)
  };
}

sweet::usize32_t window::get_min_size() const noexcept {
  int32_t width;
  int32_t height;
  SDL_GetWindowMinimumSize(get_sdl_window(), &width, &height);

  return {
    static_cast<uint32_t>(width),
    static_cast<uint32_t>(height)
  };
}

sweet::usize32_t window::get_max_size() const noexcept {
  int32_t width;
  int32_t height;
  SDL_GetWindowMaximumSize(get_sdl_window(), &width, &height);

  return {
    static_cast<uint32_t>(width),
    static_cast<uint32_t>(height)
  };
}

int32_t window::get_pos_x() const noexcept {
  return get_pos().x;
}

int32_t window::get_pos_y() const noexcept {
  return get_pos().y;
}

uint32_t window::get_size_width() const noexcept {
  return get_size().width;
}

uint32_t window::get_size_height() const noexcept {
  return get_size().height;
}

uint32_t window::get_min_size_width() const noexcept {
  return get_min_size().width;
}

uint32_t window::get_min_size_height() const noexcept {
  return get_min_size().height;
}

uint32_t window::get_max_size_width() const noexcept {
  return get_max_size().width;
}

uint32_t window::get_max_size_height() const noexcept {
  return get_max_size().height;
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

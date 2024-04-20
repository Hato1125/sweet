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

#ifndef _LIBSWEET_CORE_WINDOW_HPP
#define _LIBSWEET_CORE_WINDOW_HPP

#include <string>
#include <memory>
#include <expected>

#include <SDL_video.h>

#include "point.hpp"
#include "size.hpp"
#include "rect.hpp"

namespace sweet {
class window {
public:
  window() noexcept;

  std::expected<void, std::string> create() noexcept;
  std::expected<void, std::string> destroy() noexcept;

  window &show() noexcept;
  window &hide() noexcept;
  window &enable_resize() noexcept;
  window &disable_resize() noexcept;
  window &maximize() noexcept;
  window &minimize() noexcept;
  window &restore() noexcept;
  window &set_title(const std::string &title) noexcept;
  window &set_pos(const sweet::point32_t &pos) noexcept;
  window &set_size(const sweet::usize32_t &size) noexcept;
  window &set_min_size(const sweet::usize32_t &size) noexcept;
  window &set_max_size(const sweet::usize32_t &size) noexcept;

  std::string get_title() const noexcept;
  sweet::point32_t get_pos() const noexcept;
  sweet::usize32_t get_size() const noexcept;
  sweet::usize32_t get_min_size() const noexcept;
  sweet::usize32_t get_max_size() const noexcept;

  [[nodiscard]]
  SDL_Window *get_sdl_window() const noexcept;

  bool operator ==(const window &window) const noexcept;
  bool operator !=(const window &window) const noexcept;

  explicit operator bool() const noexcept;

private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _sdl_window;
};
}

#endif

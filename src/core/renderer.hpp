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

#ifndef _LIBSWEET_CORE_RENDERER_HPP
#define _LIBSWEET_CORE_RENDERER_HPP

#include <memory>
#include <functional>

#include <SDL_render.h>

#include "color.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "window.hpp"

namespace sweet {
class renderer {
public:
  renderer(sweet::window &window) noexcept;

  void create();
  void destroy();

  void rendering(const std::function<void()> &rendering) noexcept;

  renderer &flush() noexcept;
  renderer &clear() noexcept;
  renderer &present() noexcept;
  renderer &enable_vsync() noexcept;
  renderer &disable_vsync() noexcept;
  renderer &set_color(const sweet::color &color) noexcept;
  renderer &set_scale(const sweet::point<float> &scale) noexcept;
  renderer &set_viewport(const sweet::rect<int32_t> &rect) noexcept;

  sweet::color get_color() const noexcept;
  sweet::point<float> get_scale() const noexcept;
  sweet::rect<int32_t> get_viewport() const noexcept;

  [[nodiscard]]
  SDL_Renderer *get_sdl_renderer() const noexcept;

  bool operator ==(const renderer &renderer) const noexcept;
  bool operator !=(const renderer &renderer) const noexcept;

  explicit operator bool() const noexcept;

private:
  sweet::window &_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _sdl_renderer {
    nullptr,
    SDL_DestroyRenderer
  };
};
}

#endif

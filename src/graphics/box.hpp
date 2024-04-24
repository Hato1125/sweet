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

#ifndef _LIBSWEET_GRAPHICS_BOX_HPP
#define _LIBSWEET_GRAPHICS_BOX_HPP

#include "size.hpp"
#include "point.hpp"
#include "color.hpp"
#include "renderer.hpp"

namespace sweet {
class box {
public:
  box(sweet::renderer &renderer) noexcept;

  void fill_render(float x, float y) noexcept;
  void border_render(float x, float y) noexcept;
  void fill_render(const sweet::point<float> &pos) noexcept;
  void border_render(const sweet::point<float> &pos) noexcept;

  box &set_color(const sweet::color &color) noexcept;
  box &set_size(const sweet::size<float> &size) noexcept;
  box &set_width(float width) noexcept;
  box &set_height(float height) noexcept;

  sweet::color get_color() const noexcept;
  sweet::size<float> get_size() const noexcept;
  float get_width() const noexcept;
  float get_height() const noexcept;

private:
  sweet::renderer &_renderer;
  sweet::color _color;

  float _width;
  float _height;

  template <int RenderRect(SDL_Renderer *, const SDL_FRect*)>
  void _render_rect(float x, float y) noexcept;
};
}

#endif

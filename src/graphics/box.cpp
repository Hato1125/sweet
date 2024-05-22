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

#include "box.hpp"

namespace sweet {
box::box(sweet::renderer &renderer)
  noexcept : _renderer{ renderer },
             _color{ sweet::pallet::white },
             _width{ 100 },
             _height{ 100 } {
}

void box::fill_render(float x, float y) noexcept {
  _render_rect<SDL_RenderFillRectF>(x, y);
}

void box::border_render(float x, float y) noexcept {
  _render_rect<SDL_RenderDrawRectF>(x, y);
}

void box::fill_render(const sweet::point<float> &pos) noexcept {
  _render_rect<SDL_RenderFillRectF>(pos.x, pos.y);
}

void box::border_render(const sweet::point<float> &pos) noexcept {
  _render_rect<SDL_RenderDrawRectF>(pos.x, pos.y);
}

box &box::set_color(const sweet::color &color) noexcept {
  _color = color;
  return *this;
}

box &box::set_size(const sweet::size<float> &size) noexcept {
  _width = size.width;
  _height = size.height;
  return *this;
}

box &box::set_width(float width) noexcept {
  _width = width;
  return *this;
}

box &box::set_height(float height) noexcept {
  _height = height;
  return *this;
}

sweet::color box::get_color() const noexcept {
  return _color;
}

sweet::size<float> box::get_size() const noexcept {
  return { _width, _height };
}

float box::get_width() const noexcept {
  return _width;
}

float box::get_height() const noexcept {
  return _height;
}

template <int RenderRect(SDL_Renderer*, const SDL_FRect*)>
void box::_render_rect(float x, float y) noexcept {
  auto color = _renderer.get_color();

  SDL_FRect rect {
    .x = x,
    .y = y,
    .w = static_cast<float>(_width),
    .h = static_cast<float>(_height),
  };

   _renderer.set_color(_color);
   RenderRect(_renderer.get_sdl_renderer(), &rect);
   _renderer.set_color(color);
}
}

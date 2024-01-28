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

#include "renderer.hpp"

namespace sweet {
renderer::renderer(sweet::window &window)
  noexcept : _sdl_renderer{ nullptr, SDL_DestroyRenderer },
    _window{ window } {
}

std::expected<void, std::string> renderer::create() noexcept {
  if(_sdl_renderer)
    return std::unexpected{ "The renderer has already been created." };

  if(!_window)
    return std::unexpected{ "Window has not been created yet." };

  constexpr int32_t index = -1;
  constexpr uint32_t flags = SDL_RENDERER_PRESENTVSYNC
    | SDL_RENDERER_ACCELERATED
    | SDL_RENDERER_TARGETTEXTURE;

  SDL_Window *sdl_window = _window.get_sdl_window();
  SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window, index, flags);

  if(!sdl_renderer)
    return std::unexpected{ "Failed to create SDL_Renderer." };

  _sdl_renderer.reset(sdl_renderer);
  return{ };
}

std::expected<void, std::string> renderer::destroy() noexcept {
  if(!_sdl_renderer)
    return std::unexpected{ "Renderer has not been created yet." };

  _sdl_renderer.reset();
  return{ };
}

void renderer::flush() noexcept {
  SDL_RenderFlush(get_sdl_renderer());
}

void renderer::clear() noexcept {
  SDL_RenderClear(get_sdl_renderer());
}

void renderer::present() noexcept {
  SDL_RenderPresent(get_sdl_renderer());
}

renderer &renderer::enable_vsync() noexcept {
  SDL_RenderSetVSync(get_sdl_renderer(), true);
  return *this;
}

renderer &renderer::disable_vsync() noexcept {
  SDL_RenderSetVSync(get_sdl_renderer(), false);
  return *this;
}

renderer &renderer::set_color(const sweet::color &color) noexcept {
  SDL_SetRenderDrawColor(get_sdl_renderer(), color.r, color.g, color.b, color.a);
  return *this;
}

renderer &renderer::set_scale(const sweet::fpoint32_t &scale) noexcept {
  SDL_RenderSetScale(get_sdl_renderer(), scale.x, scale.y);
  return *this;
}

renderer &renderer::set_viewport(const sweet::rect32_t &rect) noexcept {
  SDL_Rect viewport{ rect.x, rect.y, rect.width, rect.height };
  SDL_RenderSetViewport(get_sdl_renderer(), &viewport);
  return *this;
}

sweet::color renderer::get_color() const noexcept {
  sweet::color color;
  SDL_GetRenderDrawColor(
    get_sdl_renderer(),
    &color.r,
    &color.g,
    &color.b,
    &color.a
  );
  return color;
}

sweet::fpoint32_t renderer::get_scale() const noexcept {
  sweet::fpoint32_t scale;
  SDL_RenderGetScale(
    get_sdl_renderer(),
    &scale.x,
    &scale.y
  );
  return scale;
}

sweet::rect32_t renderer::get_viewport() const noexcept {
  SDL_Rect viewport;
  SDL_RenderGetViewport(get_sdl_renderer(), &viewport);

  return {
    viewport.x,
    viewport.y,
    viewport.w,
    viewport.h
  };
}

SDL_Renderer *renderer::get_sdl_renderer() const noexcept {
  return _sdl_renderer.get();
}

bool renderer::operator ==(const renderer &renderer) const noexcept {
  return get_sdl_renderer() == renderer.get_sdl_renderer();
}

bool renderer::operator !=(const renderer &renderer) const noexcept {
  return get_sdl_renderer() != renderer.get_sdl_renderer();
}

renderer::operator bool() const noexcept {
  return get_sdl_renderer() != nullptr;
}
}

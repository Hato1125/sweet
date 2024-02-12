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

#ifndef _LIBSWEET_GRAPHICS_TEXTURE_HPP
#define _LIBSWEET_GRAPHICS_TEXTURE_HPP

#include <mutex>
#include <memory>
#include <string>
#include <cstdint>
#include <filesystem>

#include <SDL_image.h>
#include <SDL_render.h>

#include "size.hpp"
#include "rect.hpp"
#include "color.hpp"
#include "point.hpp"
#include "direction.hpp"
#include "scale_mode.hpp"
#include "blend_mode.hpp"
#include "renderer.hpp"
#include "resource.hpp"

namespace sweet {
class texture : sweet::resource {
public:
  sweet::color color;
  float angle;
  float scale_width;
  float scale_height;
  scale_mode scale_mode;
  blend_mode blend_mode;
  vertical render_v_pos;
  horizontal render_h_pos;

  texture(sweet::renderer &renderer) noexcept;
  texture(sweet::renderer &renderer, const std::string &path) noexcept;
  texture(sweet::renderer &renderer, const std::filesystem::path &path) noexcept;

  std::expected<void, std::string> load() noexcept override;
  std::expected<void, std::string> unload() noexcept override;
  std::expected<void, std::string> release() noexcept override;

  void render(
    float x,
    float y,
    sweet::rect32_t rect = { }
  ) noexcept;

  void render(
    float x,
    float y,
    const sweet::point32_t &pos,
    const sweet::size32_t &size
  ) noexcept;

  void render(
    const sweet::fpoint32_t &point,
    sweet::rect32_t rect = { }
  ) noexcept;

  void render(
    const sweet::fpoint32_t &point,
    const sweet::point32_t &pos,
    const sweet::size32_t &size
  ) noexcept;

  texture &set_color(const sweet::color &color) noexcept;
  texture &set_alpha(uint32_t alpha) noexcept;
  texture &set_angle(float angle) noexcept;
  texture &set_scale_width(float scale) noexcept;
  texture &set_scale_height(float scale) noexcept;
  texture &set_scale_mode(sweet::scale_mode mode) noexcept;
  texture &set_blend_mode(sweet::blend_mode mode) noexcept;
  texture &set_render_v_pos(sweet::vertical pos) noexcept;
  texture &set_render_h_pos(sweet::horizontal pos) noexcept;

  uint64_t get_byte() const noexcept;
  uint32_t get_width() const noexcept;
  uint32_t get_height() const noexcept;

  [[nodiscard]]
  SDL_Texture *get_sdl_texture() const noexcept;

  bool operator ==(const texture &texture) const noexcept;
  bool operator !=(const texture &texture) const noexcept;

  explicit operator bool() const noexcept;

private:
  sweet::renderer &_renderer;

  std::mutex _mutex;
  std::filesystem::path _path;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _sdl_texture;

  uint64_t _byte;
  uint32_t _width;
  uint32_t _height;

  void _set_info() noexcept;
  void _clear_info() noexcept;

private:
  static SDL_Rect _s_clip_rect;
  static SDL_FRect _s_render_rect;
  static SDL_FPoint _s_render_point;
};
}

#endif

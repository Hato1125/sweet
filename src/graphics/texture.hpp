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
class texture : public sweet::resource {
public:
  float angle;
  float scale_width;
  float scale_height;
  sweet::color color;
  sweet::scale_mode scale_mode;
  sweet::blend_mode blend_mode;
  sweet::vertical render_v_pos;
  sweet::horizontal render_h_pos;
  sweet::vertical rotation_v_pos;
  sweet::horizontal rotation_h_pos;

  texture(sweet::renderer &renderer) noexcept;
  texture(sweet::renderer &renderer, const char *path) noexcept;
  texture(sweet::renderer &renderer, const std::string &path) noexcept;
  texture(sweet::renderer &renderer, const std::filesystem::path &path) noexcept;
  texture(sweet::renderer &renderer, SDL_Surface *sdl_surface) noexcept;

  void render(
    float x,
    float y,
    int32_t rect_x = 0,
    int32_t rect_y = 0,
    int32_t rect_width = 0,
    int32_t rect_height = 0
  ) noexcept;

  void render(
    const sweet::point<float> &point,
    int32_t rect_x = 0,
    int32_t rect_y = 0,
    int32_t rect_width = 0,
    int32_t rect_height = 0
  ) noexcept;

  void render(
    float x,
    float y,
    const sweet::point<int32_t> &clip_point,
    const sweet::size<int32_t> &clip_size
  ) noexcept;

  void render(
    const sweet::point<float> &point,
    const sweet::point<int32_t> &clip_point,
    const sweet::size<int32_t> &clip_size
  ) noexcept;

  void render(
    float x,
    float y,
    const sweet::rect<int32_t> &clip
  ) noexcept;

  void render(
    const sweet::point<float> &point,
    const sweet::rect<int32_t> &clip
  ) noexcept;

  texture &set_alpha(uint32_t alpha) noexcept;
  texture &set_angle(float angle) noexcept;
  texture &set_scale_width(float scale) noexcept;
  texture &set_scale_height(float scale) noexcept;
  texture &set_color(const sweet::color &color) noexcept;
  texture &set_scale_mode(sweet::scale_mode mode) noexcept;
  texture &set_blend_mode(sweet::blend_mode mode) noexcept;
  texture &set_render_v_pos(sweet::vertical pos) noexcept;
  texture &set_render_h_pos(sweet::horizontal pos) noexcept;
  texture &set_rotation_v_pos(sweet::vertical pos) noexcept;
  texture &set_rotation_h_pos(sweet::horizontal pos) noexcept;

  uint64_t get_byte() const noexcept;
  uint32_t get_width() const noexcept;
  uint32_t get_height() const noexcept;

  [[nodiscard]]
  SDL_Texture *get_sdl_texture() const noexcept;

  bool operator ==(const texture &texture) const noexcept;
  bool operator !=(const texture &texture) const noexcept;

  explicit operator bool() const noexcept;

protected:
  std::expected<void, std::string> load_impl() noexcept override;
  std::expected<void, std::string> unload_impl() noexcept override;
  std::expected<void, std::string> release_impl() noexcept override;

private:
  sweet::renderer &_renderer;
  std::filesystem::path _path;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _sdl_texture;

  uint64_t _byte;
  uint32_t _width;
  uint32_t _height;

private:
  static SDL_Rect _s_clip_rect;
  static SDL_FRect _s_render_rect;
  static SDL_FPoint _s_rotation_point;
};
}

#endif

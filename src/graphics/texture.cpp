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

#include "texture.hpp"

namespace sweet {
SDL_Rect texture::_s_clip_rect{ };
SDL_FRect texture::_s_render_rect{ };
SDL_FPoint texture::_s_rotation_point{ };

texture::texture(sweet::renderer &renderer)
  noexcept : _renderer{ renderer },
             _sdl_texture{ nullptr, SDL_DestroyTexture },
             angle{ 0.f },
             scale_width{ 1.f },
             scale_height{ 1.f },
             color{ 255, 255, 255 },
             scale_mode{ sweet::scale_mode::best },
             blend_mode{ sweet::blend_mode::blend },
             render_v_pos{ sweet::vertical::top },
             render_h_pos{ sweet::horizontal::left },
             rotation_v_pos{ sweet::vertical::top },
             rotation_h_pos{ sweet::horizontal::left } {
}

texture::texture(sweet::renderer &renderer, const std::string &path)
  noexcept : texture(renderer) {
  _path = path;
}

texture::texture(sweet::renderer &renderer, const std::filesystem::path &path)
  noexcept : texture(renderer) {
  _path = path;
}

texture::texture(sweet::renderer &renderer, SDL_Texture *sdl_texture)
  noexcept : texture(renderer) {
    if(!sdl_texture)
      return;

    _sdl_texture.reset(sdl_texture);
    _set_info();
}

texture::texture(sweet::renderer &renderer, SDL_Surface *sdl_surface)
  noexcept : texture(renderer) {
    if(!sdl_surface)
      return;

    _sdl_texture.reset(SDL_CreateTextureFromSurface(
      renderer.get_sdl_renderer(),
      sdl_surface
    ));
    _set_info();

    SDL_FreeSurface(sdl_surface);
  }

std::expected<void, std::string> texture::load() noexcept {
  std::lock_guard<std::mutex> lock{ _mutex };

  if(!_renderer) {
    return std::unexpected {
      "The renderer has not been created and cannot be loaded."
    };
  }

  if(_sdl_texture) {
    return std::unexpected {
      "The texture is already loaded."
    };
  }

  SDL_Texture *sdl_texture = IMG_LoadTexture(
    _renderer.get_sdl_renderer(),
    _path.c_str()
  );

  if(!sdl_texture) {
    return std::unexpected {
      "Failed to load texture."
    };
  }
  _sdl_texture.reset(sdl_texture);
  _set_info();

  return{ };
}

std::expected<void, std::string> texture::unload() noexcept {
  std::lock_guard<std::mutex> lock{ _mutex };

  if(!_sdl_texture) {
    return std::unexpected {
      "Cannot be destroyed because the texture to be destroyed does not exist."
    };
  }
  _sdl_texture.reset();
  _clear_info();

  return{ };
}

std::expected<void, std::string> texture::release() noexcept  {
  std::lock_guard<std::mutex> lock{ _mutex };

    if(!_sdl_texture) {
      return std::unexpected {
        "Cannot be destroyed because the texture to be destroyed does not exist."
      };
    }
    _sdl_texture.reset();
    _release_info();

    return{ };
}

void texture::render(
  float x,
  float y,
  const sweet::rect32_t &rect
) noexcept {
  if(!get_sdl_texture())
    return;

  if(rect.x == 0 && rect.y == 0 && rect.width == 0 && rect.height == 0) {
    _s_clip_rect.w = _width;
    _s_clip_rect.h = _height;
  } else {
    _s_clip_rect.w = rect.width;
    _s_clip_rect.h = rect.height;
  }
  _s_clip_rect.x = rect.x;
  _s_clip_rect.y = rect.y;

  _s_render_rect.w = _s_clip_rect.w * scale_width;
  _s_render_rect.h = _s_clip_rect.h * scale_height;

  _s_rotation_point = {
    sweet::get_horizontal_pos(_s_render_rect.w, rotation_h_pos),
    sweet::get_vertical_pos(_s_render_rect.h, rotation_v_pos)
  };

  float r_h_pos = sweet::get_horizontal_pos(_s_render_rect.w, render_h_pos);
  float r_v_pos = sweet::get_vertical_pos(_s_render_rect.h, render_v_pos);

  _s_render_rect.x = x - r_h_pos;
  _s_render_rect.y = y - r_v_pos;

  SDL_SetTextureBlendMode(get_sdl_texture(), static_cast<SDL_BlendMode>(blend_mode));
  SDL_SetTextureScaleMode(get_sdl_texture(), static_cast<SDL_ScaleMode>(scale_mode));
  SDL_SetTextureAlphaMod(get_sdl_texture(), color.a);
  SDL_SetTextureColorMod(get_sdl_texture(), color.r, color.g, color.b);

  SDL_RenderCopyExF(
    _renderer.get_sdl_renderer(),
    get_sdl_texture(),
    &_s_clip_rect,
    &_s_render_rect,
    angle,
    &_s_rotation_point,
    SDL_FLIP_NONE
  );
}

void texture::render(
  float x,
  float y,
  const sweet::point32_t &pos,
  const sweet::size32_t &size
) noexcept {
  render(x, y, pos, size);
}

void texture::render(
  const sweet::fpoint32_t &point,
  const sweet::rect32_t &rect
) noexcept {
  render(point.x, point.y, rect);
}

void texture::render(
  const sweet::fpoint32_t &point,
  const sweet::point32_t &pos,
  const sweet::size32_t &size
) noexcept {
  render(point.x, point.y, pos, size);
}

texture &texture::set_alpha(uint32_t alpha) noexcept {
  color.a = alpha;
  return *this;
}

texture &texture::set_angle(float angle) noexcept {
  angle = angle;
  return *this;
}

texture &texture::set_scale_width(float scale) noexcept {
  scale_width = scale;
  return *this;
}

texture &texture::set_scale_height(float scale) noexcept {
  scale_height = scale;
  return *this;
}

texture &texture::set_color(const sweet::color &color) noexcept {
  this->color = color;
  return *this;
}

texture &texture::set_scale_mode(sweet::scale_mode mode) noexcept {
  scale_mode = mode;
  return *this;
}

texture &texture::set_blend_mode(sweet::blend_mode mode) noexcept {
  blend_mode = mode;
  return *this;
}

texture &texture::set_render_v_pos(sweet::vertical pos) noexcept {
  render_v_pos = pos;
  return *this;
}

texture &texture::set_render_h_pos(sweet::horizontal pos) noexcept {
  render_h_pos = pos;
  return *this;
}

texture &texture::set_rotation_v_pos(sweet::vertical pos) noexcept {
  rotation_v_pos = pos;
  return *this;
}

texture &texture::set_rotation_h_pos(sweet::horizontal pos) noexcept {
  rotation_h_pos = pos;
  return *this;
}

uint64_t texture::get_byte() const noexcept {
  return _byte;
}

uint32_t texture::get_width() const noexcept {
  return _width;
}

uint32_t texture::get_height() const noexcept {
  return _height;
}

SDL_Texture *texture::get_sdl_texture() const noexcept {
  return _sdl_texture.get();
}

bool texture::operator ==(const texture &texture) const noexcept {
  return get_sdl_texture() == texture.get_sdl_texture();
}

bool texture::operator !=(const texture &texture) const noexcept {
  return get_sdl_texture() != texture.get_sdl_texture();
}

texture::operator bool() const noexcept {
  return get_sdl_texture() != nullptr;
}

void texture::_set_info() noexcept {
  uint32_t format;
  SDL_QueryTexture(
    get_sdl_texture(),
    &format,
    nullptr,
    reinterpret_cast<int*>(&_width),
    reinterpret_cast<int*>(&_height)
  );
  _byte = SDL_BYTESPERPIXEL(format) * _width * _height;
}

void texture::_clear_info() noexcept {
  _path.clear();
  _byte = 0;
  _width = 0;
  _height = 0;
}

void texture::_release_info() noexcept {
  _byte = 0;
  _width = 0;
  _height = 0;
}
}

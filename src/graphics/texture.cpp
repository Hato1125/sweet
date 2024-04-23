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
#include <iostream>

namespace sweet {
SDL_Rect texture::_s_clip_rect{ };
SDL_FRect texture::_s_render_rect{ };
SDL_FPoint texture::_s_rotation_point{ };

texture::texture(sweet::renderer &renderer)
  noexcept : _renderer{ renderer },
             _sdl_texture{ nullptr, SDL_DestroyTexture },
             _path{ },
             _width{ 0u },
             _height{ 0u },
             _byte{ 0u },
             angle{ 0.f },
             scale_width{ 1.f },
             scale_height{ 1.f },
             color{ sweet::pallet::white },
             scale_mode{ sweet::scale_mode::best },
             blend_mode{ sweet::blend_mode::blend },
             render_v_pos{ sweet::vertical::top },
             render_h_pos{ sweet::horizontal::left },
             rotation_v_pos{ sweet::vertical::top },
             rotation_h_pos{ sweet::horizontal::left } {
}

texture::texture(sweet::renderer &renderer, const char *path)
  noexcept : texture(renderer) {
  _path = path;
}

texture::texture(sweet::renderer &renderer, const std::string &path)
  noexcept : texture(renderer) {
  _path = path;
}

texture::texture(sweet::renderer &renderer, const std::filesystem::path &path)
  noexcept : texture(renderer) {
  _path = path;
}

texture::texture(sweet::renderer &renderer, SDL_Surface *sdl_surface)
  noexcept : texture(renderer) {
    if(!sdl_surface)
      return;

    _sdl_texture.reset(SDL_CreateTextureFromSurface(
      renderer.get_sdl_renderer(),
      sdl_surface
    ));

    _width = sdl_surface->w;
    _height = sdl_surface->h;
    _byte = SDL_BYTESPERPIXEL(sdl_surface->format->format) * _width * _height;
    SDL_FreeSurface(sdl_surface);
}

void texture::render(
  float x,
  float y,
  int32_t rect_x,
  int32_t rect_y,
  int32_t rect_width,
  int32_t rect_height
) noexcept {
  if(!get_sdl_texture())
    return;

  bool not_clip = rect_x == 0 && rect_y == 0 && rect_width == 0 && rect_height == 0;
  _s_clip_rect.w = not_clip ? _width : rect_width;
  _s_clip_rect.h = not_clip ? _height : rect_height;

  _s_clip_rect.x = rect_x;
  _s_clip_rect.y = rect_y;

  _s_render_rect.w = _s_clip_rect.w * scale_width;
  _s_render_rect.h = _s_clip_rect.h * scale_height;

  _s_rotation_point.x = sweet::get_horizontal_pos(_s_render_rect.w, rotation_h_pos);
  _s_rotation_point.y = sweet::get_vertical_pos(_s_render_rect.h, rotation_v_pos);

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
  const sweet::point<float> &point,
  int32_t rect_x,
  int32_t rect_y,
  int32_t rect_width,
  int32_t rect_height
) noexcept {
  render(
    point.x,
    point.y,
    rect_x,
    rect_y,
    rect_width,
    rect_height
  );
}

void texture::render(
  float x,
  float y,
  const sweet::point<int32_t> &clip_point,
  const sweet::size<int32_t> &clip_size
) noexcept {
  render(
    x,
    y,
    clip_point.x,
    clip_point.y,
    clip_size.width,
    clip_size.height
  );
}

void texture::render(
  const sweet::point<float> &point,
  const sweet::point<int32_t> &clip_point,
  const sweet::size<int32_t> &clip_size
) noexcept {
  render(
    point.x,
    point.y,
    clip_point.x,
    clip_point.y,
    clip_size.width,
    clip_size.height
  );
}

void texture::render(
  float x,
  float y,
  const sweet::rect<int32_t> &clip
) noexcept {
  render(
    x,
    y,
    clip.x,
    clip.y,
    clip.width,
    clip.height
  );
}

void texture::render(
  const sweet::point<float> &point,
  const sweet::rect<int32_t> &clip
) noexcept {
  render(
    point.x,
    point.y,
    clip.x,
    clip.y,
    clip.width,
    clip.height
  );
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

std::expected<void, std::string> texture::load_impl() noexcept {
  if(!_renderer)
    return std::unexpected{ "Renderer has not been created." };

  if(get_sdl_texture())
    return std::unexpected{ "The texture is already loaded." };

  SDL_Surface *sdl_surface = IMG_Load(_path.string().c_str());
  if(!sdl_surface)
    return std::unexpected{ "Failed to load image." };

  SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(
    _renderer.get_sdl_renderer(),
    sdl_surface
  );
  if(!sdl_texture)
    return std::unexpected{ "Failed to convert Surface to Texture." };

  _sdl_texture.reset(sdl_texture);
  _width = sdl_surface->w;
  _height = sdl_surface->h;
  _byte = SDL_BYTESPERPIXEL(sdl_surface->format->format) * _width * _height;
  SDL_FreeSurface(sdl_surface);

  return{ };
}

std::expected<void, std::string> texture::unload_impl() noexcept {
  if(!get_sdl_texture())
    return std::unexpected{ "There are no textures to discard." };

  _sdl_texture.reset();
  _path.clear();
  _width = 0u;
  _height = 0u;
  _byte = 0u;

  return{ };
}

std::expected<void, std::string> texture::release_impl() noexcept  {
  if(!get_sdl_texture())
    return std::unexpected{ "There are no textures to discard." };

  _sdl_texture.reset();
  _width = 0u;
  _height = 0u;
  _byte = 0u;

  return{ };
}
}

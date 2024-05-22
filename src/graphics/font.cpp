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

#include "font.hpp"

namespace sweet {
using unique_texture = std::unique_ptr<sweet::texture>;

font::font(sweet::renderer &renderer)
  noexcept : _renderer{ renderer },
              _sdl_font{ nullptr, TTF_CloseFont } {
}

font::font(sweet::renderer &renderer, const char *path)
  noexcept : font(renderer) {
  _path = path;
}

font::font(sweet::renderer &renderer, const std::string &path)
  noexcept : font(renderer) {
  _path = path.c_str();
}

font::font(sweet::renderer &renderer, const std::filesystem::path &path)
  noexcept : font(renderer) {
  _path = path.c_str();
}

void font::load() {
  if(_sdl_font)
    return;

  _sdl_font.reset(TTF_OpenFont(_path.string().c_str(), 12));
  if(!_sdl_font)
    std::runtime_error("Failed to load font file.");
}

void font::unload() {
  if(!_sdl_font)
    throw std::runtime_error("There are no fonts to discard.");
  _sdl_font.reset();
  _path.clear();
}

void font::release() {
  if(!_sdl_font)
    throw std::runtime_error("There are no fonts to discard.");
  _sdl_font.reset();
}

std::unique_ptr<sweet::texture> font::create_text_font(
  const std::string &text,
  const sweet::font_info &info
) {
  return _create_font_texture<char, TTF_RenderText_Blended>(text, info);
}

std::unique_ptr<sweet::texture> font::create_utf8_text_font(
  const std::string &text,
  const sweet::font_info &info
) {
  return _create_font_texture<char, TTF_RenderUTF8_Blended>(text, info);
}

std::unique_ptr<sweet::texture> font::create_unicode_text_font(
  const std::basic_string<uint16_t> &text,
  const sweet::font_info &info
) {
  return _create_font_texture<uint16_t, TTF_RenderUNICODE_Blended>(text, info);
}

TTF_Font *font::get_sdl_font() const noexcept {
  return _sdl_font.get();
}

bool font::operator ==(const font &font) const noexcept {
  return get_sdl_font() == font.get_sdl_font();
}

bool font::operator !=(const font &font) const noexcept {
  return get_sdl_font() != font.get_sdl_font();
}

font::operator bool() const noexcept {
  return get_sdl_font() != nullptr;
}

template <typename charT, SDL_Surface *create_font_surface_f(TTF_Font*, const charT*, SDL_Color)>
std::unique_ptr<sweet::texture> font::_create_font_texture(
  const std::basic_string<charT> &text,
  const sweet::font_info &info
) {
  if(!_renderer)
    throw std::runtime_error("The renderer has not been created and cannot be loaded.");

  switch(info.direction) {
    using enum sweet::direction;
    case left:
      TTF_SetFontDirection(get_sdl_font(), TTF_DIRECTION_LTR);
      break;
    case right:
      TTF_SetFontDirection(get_sdl_font(), TTF_DIRECTION_RTL);
      break;
    case up:
      TTF_SetFontDirection(get_sdl_font(), TTF_DIRECTION_TTB);
      break;
    case down:
      TTF_SetFontDirection(get_sdl_font(), TTF_DIRECTION_BTT);
      break;
  }

  TTF_SetFontSize(get_sdl_font(), static_cast<int>(info.size));
  TTF_SetFontStyle(get_sdl_font(), static_cast<int>(info.style));
  SDL_Surface *surface = create_font_surface_f(
    get_sdl_font(),
    text.c_str(),
    {
      info.color.r,
      info.color.g,
      info.color.b,
    }
  );

  if(!surface)
    throw std::runtime_error("Failed to create text surface.");
  return std::make_unique<sweet::texture>(_renderer, surface);
}
}

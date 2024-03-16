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

#ifndef _LIBSWEET_GRAPHICS_FONT_HPP
#define _LIBSWEET_GRAPHICS_FONT_HPP

#include <string>
#include <memory>
#include <expected>
#include <filesystem>

#include <SDL_ttf.h>

#include "color.hpp"
#include "direction.hpp"
#include "texture.hpp"
#include "renderer.hpp"
#include "resource.hpp"

namespace sweet {
enum class font_style {
  normal = TTF_STYLE_NORMAL,
  bold = TTF_STYLE_BOLD,
  italic = TTF_STYLE_ITALIC,
  strikethrough = TTF_STYLE_STRIKETHROUGH
};

struct font_info {
  uint32_t size { 12u };
  sweet::color color { sweet::pallet::white };
  sweet::direction direction { sweet::direction::left };
  sweet::font_style style { sweet::font_style::normal };
};

class font : public sweet::resource {
 using unique_texture = std::unique_ptr<sweet::texture>;

public:
  font(sweet::renderer &renderer) noexcept;
  font(sweet::renderer &renderer, const char *path) noexcept;
  font(sweet::renderer &renderer, const std::string &path) noexcept;
  font(sweet::renderer &renderer, const std::filesystem::path &path) noexcept;

  std::expected<unique_texture, std::string> create_text_font(
    const std::string &text,
    const sweet::font_info &info
  ) noexcept;

  std::expected<unique_texture, std::string> create_utf8_text_font(
    const std::string &text,
    const sweet::font_info &info
  ) noexcept;

  std::expected<unique_texture, std::string> create_unicode_text_font(
    const std::basic_string<uint16_t> &text,
    const sweet::font_info &info
  ) noexcept;

  [[nodiscard]]
  TTF_Font *get_sdl_font() const noexcept;

  bool operator ==(const font &font) const noexcept;
  bool operator !=(const font &font) const noexcept;

  explicit operator bool() const noexcept;

protected:
  std::expected<void, std::string> load_impl() noexcept override;
  std::expected<void, std::string> unload_impl() noexcept override;
  std::expected<void, std::string> release_impl() noexcept override;

private:
  sweet::renderer &_renderer;
  std::filesystem::path _path;
  std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> _sdl_font;


  template <typename CharType, SDL_Surface *(TTF_Font*, const CharType*, SDL_Color)>
  std::expected<unique_texture, std::string> _create_font_texture(
    const std::basic_string<CharType> &text,
    const sweet::font_info &info
  ) noexcept;
};
}

#endif

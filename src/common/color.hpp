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

#ifndef _LIBSWEET_COMMON_COLOR_HPP
#define _LIBSWEET_COMMON_COLOR_HPP

#include <cstdint>

namespace sweet {
struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  constexpr color()
    noexcept : r{ 0u }, g{ 0u }, b{ 0u }, a{ 255u } {
  }

  constexpr color(
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a = 255u
  ) noexcept : r{ r }, g{ g }, b{ b }, a{ a } {
  }

  color &set_r(uint8_t r) noexcept;
  color &set_g(uint8_t g) noexcept;
  color &set_b(uint8_t b) noexcept;
  color &set_a(uint8_t a) noexcept;

  color &set_hex_argb(uint32_t color) noexcept;
  color &set_hex_rgba(uint32_t color) noexcept;
};
}

namespace sweet::pallet {
constexpr sweet::color black{ 0u, 0u, 0u };
constexpr sweet::color white{ 255u, 255u, 255u };
constexpr sweet::color red{ 255u, 59u, 48u };
constexpr sweet::color orange{ 255u, 149u, 0u };
constexpr sweet::color yellow{ 255u, 204u, 0u };
constexpr sweet::color green{ 52u, 199u, 89u };
constexpr sweet::color mint{ 0u, 199u, 190u };
constexpr sweet::color teal{ 48u, 176u, 199u };
constexpr sweet::color cyan{ 50u, 173u, 230u };
constexpr sweet::color blur{ 0u, 122u, 255u };
constexpr sweet::color indigo{ 88u, 86u, 214u };
constexpr sweet::color purple{ 175u, 82u, 222u };
constexpr sweet::color pink{ 255u, 45u, 85u };
constexpr sweet::color brown{ 162u, 132u, 94u };
}

#endif

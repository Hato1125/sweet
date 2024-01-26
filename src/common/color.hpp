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

#include <cmath>
#include <cstdint>

namespace sweet {
struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  color()
   noexcept : r{ }, g{ }, b{ }, a{ 255 } {
  }

  color(
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a = 255
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

#endif

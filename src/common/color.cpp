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

#include "color.hpp"

namespace sweet {
color &color::set_r(uint8_t r) noexcept {
  r = r;
  return *this;
}

color &color::set_g(uint8_t g) noexcept {
  g = g;
  return *this;
}

color &color::set_b(uint8_t b) noexcept {
  b = b;
  return *this;
}

color &color::set_a(uint8_t a) noexcept {
  a = a;
  return *this;
}

color &color::set_hex_argb(uint32_t color) noexcept {
  a = static_cast<uint8_t>((color >> 24) & 0xff);
  r = static_cast<uint8_t>((color >> 16) & 0xff);
  g = static_cast<uint8_t>((color >> 8) & 0xff);
  b = static_cast<uint8_t>((color >> 0) & 0xff);
  return *this;
}

color &color::set_hex_rgba(uint32_t color) noexcept {
  r = static_cast<uint8_t>((color >> 24) & 0xff);
  g = static_cast<uint8_t>((color >> 16) & 0xff);
  b = static_cast<uint8_t>((color >> 8) & 0xff);
  a = static_cast<uint8_t>((color >> 0) & 0xff);
  return *this;
}
}

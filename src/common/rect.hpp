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

#ifndef _LIBSWEET_COMMON_RECT_HPP
#define _LIBSWEET_COMMON_RECT_HPP

#include <cstdint>
#include <type_traits>

#include "point.hpp"
#include "size.hpp"

namespace sweet {
template <typename Type>
struct rect {
  static_assert(std::is_arithmetic<Type>::value == true);

  Type x;
  Type y;
  Type width;
  Type height;

  constexpr rect()
    noexcept : x{ }, y{ }, width{ }, height{ } {
  }

  constexpr rect(Type x, Type y, Type width, Type height)
    noexcept : x{ x }, y{ y }, width{ width }, height{ height } {
  }

  bool is_contains(Type x, Type y) const {
    return x >= this->x
      && y >= this->y
      && x <= width
      && y <= height;
  }

  bool is_contains(const sweet::point<Type> &point) const {
    return point.x >= x
      && point.y >= y
      && point.x <= width
      && point.y <= height;
  }

  sweet::point<Type> get_point() const noexcept {
    return { x, y };
  }

  sweet::size<Type> get_size() const noexcept {
    return { width, height };
  }

  bool operator ==(const rect<Type> &rect) const noexcept {
    return rect.x == x
      && rect.y == y
      && rect.width == width
      && rect.height == height;
  }

  bool operator !=(const rect<Type> &rect) const noexcept {
    return rect.x != x
      || rect.y != y
      || rect.width != width
      || rect.height != height;
  }
};

using urect8_t = rect<uint8_t>;
using urect16_t = rect<uint16_t>;
using urect32_t = rect<uint32_t>;
using urect64_t = rect<uint64_t>;

using urect_fast8_t = rect<uint_fast8_t>;
using urect_fast16_t = rect<uint_fast16_t>;
using urect_fast32_t = rect<uint_fast32_t>;
using urect_fast64_t = rect<uint_fast64_t>;

using rect8_t = rect<int8_t>;
using rect16_t = rect<int16_t>;
using rect32_t = rect<int32_t>;
using rect64_t = rect<int64_t>;

using rect_fast8_t = rect<int_fast8_t>;
using rect_fast16_t = rect<int_fast16_t>;
using rect_fast32_t = rect<int_fast32_t>;
using rect_fast64_t = rect<int_fast64_t>;

using frect32_t = rect<float>;
using frect64_t = rect<double>;
}

#endif

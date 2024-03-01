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

#ifndef _LIBSWEET_COMMON_POINT_HPP
#define _LIBSWEET_COMMON_POINT_HPP

#include <cstdint>
#include <type_traits>

namespace sweet {
template <typename Type>
struct point {
  static_assert(std::is_arithmetic<Type>::value == true);

  Type x;
  Type y;

  constexpr point()
    noexcept : x{ }, y{ } {
  }

  constexpr point(Type v)
    noexcept : x{ v }, y{ v } {
  }

  constexpr point(Type x, Type y)
    noexcept : x{ x }, y{ y } {
  }

  bool operator ==(const point<Type> &point) const noexcept {
    return x == point.x && y == point.y;
  }

  bool operator !=(const point<Type> &point) const noexcept {
    return x != point.x || y != point.y;
  }

  point<Type> operator +(const point<Type> &point) const noexcept {
    return { x + point.x, y + point.y };
  }

  point<Type> operator -(const point<Type> &point) const noexcept {
    return { x - point.x, y - point.y };
  }

  point<Type> operator *(const point<Type> &point) const noexcept {
    return { x * point.x, y * point.y };
  }

  point<Type> operator /(const point<Type> &point) const noexcept {
    return { x / point.x, y / point.y };
  }
};

using upoint8_t = point<uint8_t>;
using upoint16_t = point<uint16_t>;
using upoint32_t = point<uint32_t>;
using upoint64_t = point<uint64_t>;

using upoint_fast8_t = point<uint_fast8_t>;
using upoint_fast16_t = point<uint_fast16_t>;
using upoint_fast32_t = point<uint_fast32_t>;
using upoint_fast64_t = point<uint_fast64_t>;

using point8_t = point<int8_t>;
using point16_t = point<int16_t>;
using point32_t = point<int32_t>;
using point64_t = point<int64_t>;

using point_fast8_t = point<int_fast8_t>;
using point_fast16_t = point<int_fast16_t>;
using point_fast32_t = point<int_fast32_t>;
using point_fast64_t = point<int_fast64_t>;

using fpoint32_t = point<float>;
using fpoint64_t = point<double>;
}

#endif

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

#include <iostream>
#include <type_traits>

namespace sweet {
template <typename Type>
struct point {
  static_assert(
    std::is_arithmetic<Type>::value,
    "Cannot contain anything other than arithmetic types."
  );

  Type x;
  Type y;

  constexpr point()
    noexcept : x{}, y{} {
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

template <typename Type>
std::ostream & operator<<(
  std::ostream &os,
  const sweet::point<Type> &point
) {
  os << "{"
     << " x: " << point.x << ","
     << " y: " << point.y << " "
     << "}";
  return os;
}
}

#endif

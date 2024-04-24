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

#include <iostream>
#include <type_traits>

#include "point.hpp"
#include "size.hpp"

namespace sweet {
template <typename Type>
struct rect {
  static_assert(
    std::is_arithmetic<Type>::value,
    "Cannot contain anything other than arithmetic types."
  );

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

  constexpr rect(const sweet::point<Type> &point, const sweet::size<Type> &size)
    noexcept : x{ point.x }, y{ point.y }, width{ size.width }, height{ size.height } {
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

template <typename Type>
std::ostream & operator<<(
  std::ostream &os,
  const sweet::rect<Type> &rect
) {
  os << "{"
     << " x: " << rect.x << ","
     << " y: " << rect.y << ","
     << " width: " << rect.width << ","
     << " height: " << rect.height << " "
     << "}";
  return os;
}
}

#endif

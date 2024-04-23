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

#ifndef _LIBSWEET_COMMON_SIZE_HPP
#define _LIBSWEET_COMMON_SIZE_HPP

#include <cstdint>
#include <type_traits>

namespace sweet {
template <typename Type>
struct size {
  static_assert(std::is_arithmetic<Type>::value == true);

  Type width;
  Type height;

  constexpr size()
    noexcept : width{ }, height{ } {
  }

  constexpr size(Type width, Type height)
    noexcept : width{ width }, height{ height } {
  }

  bool operator ==(const size<Type> &size) const noexcept {
    return width == size.width && height == size.height;
  }

  bool operator !=(const size<Type> &size) const noexcept {
    return width != size.width || height != size.height;
  }

  size<Type> operator +(const size<Type> &size) const noexcept {
    return { width + size.width, height + size.height };
  }

  size<Type> operator -(const size<Type> &size) const noexcept {
    return { width - size.width, height - size.height };
  }

  size<Type> operator *(const size<Type> &size) const noexcept {
    return { width * size.width, height * size.height };
  }

  size<Type> operator /(const size<Type> &size) const noexcept {
    return { width / size.width, height / size.height };
  }
};

using usize8_t = size<uint8_t>;
using usize16_t = size<uint16_t>;
using usize32_t = size<uint32_t>;
using usize64_t = size<uint64_t>;

using usize_fast8_t = size<uint_fast8_t>;
using usize_fast16_t = size<uint_fast16_t>;
using usize_fast32_t = size<uint_fast32_t>;
using usize_fast64_t = size<uint_fast64_t>;

using size8_t = size<int8_t>;
using size16_t = size<int16_t>;
using size32_t = size<int32_t>;
using size64_t = size<int64_t>;

using size_fast8_t = size<int_fast8_t>;
using size_fast16_t = size<int_fast16_t>;
using size_fast32_t = size<int_fast32_t>;
using size_fast64_t = size<int_fast64_t>;

using fsize32_t = size<float>;
using fsize64_t = size<double>;
}

#endif

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

#ifndef _LIBSWEET_COMMON_DIRECTION_HPP
#define _LIBSWEET_COMMON_DIRECTION_HPP

namespace sweet {
enum class horizontal {
  left,
  center,
  right
};

enum class vertical {
  top,
  center,
  bottom
};

enum class direction {
  up,
  right,
  down,
  left
};

inline float get_horizontal_pos(float width, horizontal pos) noexcept {
  switch(pos) {
    case horizontal::left: return 0.f;
    case horizontal::center: return width / 2.f;
    case horizontal::right: return width / 2.f;
    default: return 0.f;
  }
}

inline float get_vertical_pos(float height, vertical pos) noexcept {
  switch(pos) {
    case vertical::top: return 0.f;
    case vertical::center: return height / 2.f;
    case vertical::bottom: return height / 2.f;
    default: return 0.f;
  }
}
}

#endif

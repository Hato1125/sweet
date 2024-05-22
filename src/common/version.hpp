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

#ifndef _LIBSWEET_VERSION_HPP
#define _LIBSWEET_VERSION_HPP

#include <string>

#include <SDL_version.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define SWEET_MAJOR_VERSION 0
#define SWEET_MINOR_VERSION 3
#define SWEET_PATCHLEVEL 0

namespace sweet {
inline std::string get_sdl_version() noexcept {
  return std::to_string(SDL_MAJOR_VERSION) + "."
    + std::to_string(SDL_MINOR_VERSION) + "."
    + std::to_string(SDL_PATCHLEVEL);
}

inline std::string get_sdl_image_version() noexcept {
  return std::to_string(SDL_IMAGE_MAJOR_VERSION) + "."
    + std::to_string(SDL_IMAGE_MINOR_VERSION) + "."
    + std::to_string(SDL_IMAGE_PATCHLEVEL);
}

inline std::string get_sdl_ttf_version() noexcept {
  return std::to_string(SDL_TTF_MAJOR_VERSION) + "."
    + std::to_string(SDL_TTF_MINOR_VERSION) + "."
    + std::to_string(SDL_TTF_PATCHLEVEL);
}

inline std::string get_sweet_version() noexcept {
  return std::to_string(SWEET_MAJOR_VERSION) + "."
    + std::to_string(SWEET_MINOR_VERSION) + "."
    + std::to_string(SWEET_PATCHLEVEL);
}
}

#endif

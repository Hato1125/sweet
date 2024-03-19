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

#ifndef _LIBSWEET_INPUT_KEYBOARD_HPP
#define _LIBSWEET_INPUT_KEYBOARD_HPP

#include <array>
#include <cstdint>

#include <SDL_events.h>
#include <SDL_keyboard.h>

namespace sweet {
class keyboard final {
public:
  keyboard() = delete;
  ~keyboard() = delete;

  static void update() noexcept;
  static void update_event(const SDL_Event& e) noexcept;

  static bool is_pushing(SDL_Scancode key) noexcept;
  static bool is_pushed(SDL_Scancode key) noexcept;
  static bool is_separate(SDL_Scancode key) noexcept;

private:
  static bool _is_key_pressed;
  static bool _is_one_frame_passed;
  static int32_t _last_down_key_code;

  static std::array<int8_t, SDL_NUM_SCANCODES> _key_state;

  static void _update_key_state() noexcept;
};
}

#endif

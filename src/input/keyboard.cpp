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

#include "keyboard.hpp"

namespace sweet {
bool keyboard::_is_key_state_update{ false };
bool keyboard::_is_tick_frame_counter{ false };
uint8_t keyboard::_frame_counter{ 0u };

std::array<int8_t, 256> keyboard::_key_state{ };

void keyboard::update() noexcept {
  if(_is_key_state_update && !_is_tick_frame_counter && _frame_counter < 2) {
    _update_key_state();
    ++_frame_counter;
    return;
  }

  if(_is_tick_frame_counter && _frame_counter < 2) {
    _update_key_state();
    ++_frame_counter;
  }
}

void keyboard::update_event(const SDL_Event &e) noexcept {
  switch(e.type) {
    case SDL_KEYDOWN: {
      _is_key_state_update = true;
      _is_tick_frame_counter = false;
      _frame_counter = 0u;
      break;
    }
    case SDL_KEYUP: {
      _is_key_state_update = false;
      _is_tick_frame_counter = true;
      _frame_counter = 0u;
      break;
    }
  }
}

bool keyboard::is_pushing(SDL_Scancode key) noexcept {
  return _key_state[static_cast<int>(key)] > 0;
}

bool keyboard::is_pushed(SDL_Scancode key) noexcept {
  return _key_state[static_cast<int>(key)] == 2;
}

bool keyboard::is_separate(SDL_Scancode key) noexcept {
  return _key_state[static_cast<int>(key)] == -1;
}

void keyboard::_update_key_state() noexcept {
  const uint8_t *sdl_key_state = SDL_GetKeyboardState(nullptr);
  for(size_t i = 0; i < _key_state.size(); ++i) {
    if(sdl_key_state[i])
      _key_state[i] = is_pushing(static_cast<SDL_Scancode>(i)) ? 1 : 2;
    else
      _key_state[i] = is_pushing(static_cast<SDL_Scancode>(i)) ? -1 : 0;
  }
}
}

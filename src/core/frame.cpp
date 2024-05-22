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

#include <SDL_timer.h>

#include "frame.hpp"

namespace sweet {
frame::frame()
  noexcept: _limmit_sec{ 1000.f / 60.f },
            _update_frame_rate_sec{ 1.f } {
}

void frame::begin() noexcept {
  if(_limmit_sec != -1.f)
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), _ticks_count + _limmit_sec));

  _frame_sec = (SDL_GetTicks() - _ticks_count) / 1000.f;
  _ticks_count = SDL_GetTicks();
}

void frame::end() noexcept {
  _one_sec_timer += _frame_sec;
  _update_sec_timer += _frame_sec;

  _frame_count++;
  if(_one_sec_timer >= 1.f) {
    _frame_rate_buf = _frame_count;
    _frame_count = 0;
    _one_sec_timer = 0.f;
  }

  if(_update_sec_timer >= _update_frame_rate_sec) {
    _frame_rate = _frame_rate_buf;
    _update_sec_timer = 0.f;
  }
}

frame &frame::set_max_frame_rate(float fps) noexcept {
  _limmit_sec = fps <= 0.f ? -1.f : 1000.f / fps;
  return *this;
}

frame &frame::set_update_frame_rate_sec(float sec) noexcept {
  _update_frame_rate_sec = sec <= 0.f ? 1.f : sec;
  return *this;
}

float frame::get_frame_sec() const noexcept {
  return _frame_sec;
}

int32_t frame::get_frame_rate() const noexcept {
  return _frame_rate;
}
}

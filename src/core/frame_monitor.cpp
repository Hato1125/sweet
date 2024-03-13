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

#include "frame_monitor.hpp"

namespace sweet {
void frame_monitor::begin() noexcept {
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), _ticks_count + _limmit_ms));

  _delta_time = (SDL_GetTicks() - _ticks_count) / 1000.;
  _ticks_count = SDL_GetTicks();
}

void frame_monitor::end() noexcept {
  _one_sec_timer += _delta_time;
  ++_frame_count;
  if(_one_sec_timer >= 1.0) {
    _frame_rate = _frame_count;
    _frame_count = 0;
    _one_sec_timer = 0.;
  }
}

void frame_monitor::set_max_frame_rate(double fps) noexcept {
  _limmit_ms = 1000. / fps;
}

float frame_monitor::get_delta_time_f32() const noexcept {
  return static_cast<float>(_delta_time);
}

double frame_monitor::get_delta_time_f64() const noexcept {
  return _delta_time;
}

int32_t frame_monitor::get_frame_rate() const noexcept {
  return _frame_rate;
}
}

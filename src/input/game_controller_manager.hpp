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

#ifndef _LIBSWEET_INPUT_GAME_CONTROLLER_MANAGER_HPP
#define _LIBSWEET_INPUT_GAME_CONTROLLER_MANAGER_HPP

#include <vector>
#include <cstdint>
#include <algorithm>

#include <SDL_events.h>

#include "game_controller.hpp"

namespace sweet {
class game_controller_manager final {
using game_controller_it = std::vector<sweet::game_controller>::iterator;

public:
  static void update() noexcept;
  static void update_event(const SDL_Event &e) noexcept;

  static bool is_pushing(
    int32_t joystic_index,
    SDL_GameControllerButton button
  ) noexcept;

  static bool is_pushed(
    int32_t joystic_index,
    SDL_GameControllerButton button
  ) noexcept;

  static bool is_separate(
    int32_t joystic_index,
    SDL_GameControllerButton button
  ) noexcept;

private:
  static bool _is_key_state_update;
  static bool _is_tick_frame_counter;
  static uint8_t _frame_counter;

  static std::vector<sweet::game_controller> _game_controllers;

  static void _update_game_controller_state() noexcept;
  static void _add_game_controller(int32_t joystic_index) noexcept;
  static void _remove_game_controller(int32_t joystic_index) noexcept;

  static game_controller_it _get_game_controller_iterator(int32_t joystick_index) noexcept;
  static bool _is_contains_game_controller(game_controller_it &it) noexcept;
};
}

#endif

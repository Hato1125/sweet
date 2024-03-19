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

#include <cstdint>
#include <vector>

#include "game_controller.hpp"

namespace sweet {
class game_controller_manager final {
public:
  static void update() noexcept;
  static void update_event(const SDL_Event &e) noexcept;

  static sweet::game_controller &get(int32_t joystick_index) noexcept;

private:
  static sweet::game_controller _empty_controller;
  static std::vector<sweet::game_controller> _controllers;

  static void _add_game_controller(int32_t joystic_index) noexcept;
  static void _remove_game_controller(int32_t joystic_index) noexcept;
  static std::vector<sweet::game_controller>::iterator find_joystick_index(int32_t joystick_index) noexcept;
};
}

#endif

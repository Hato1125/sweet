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

#ifndef _LIBSWEET_INPUT_GAME_CONTROLLER_HPP
#define _LIBSWEET_INPUT_GAME_CONTROLLER_HPP

#include <array>
#include <memory>
#include <string>
#include <cstdint>
#include <expected>

#include <SDL_events.h>
#include <SDL_gamecontroller.h>

namespace sweet {
class game_controller {
public:
  game_controller(int32_t joystick_index) noexcept;

  std::expected<void, std::string> create() noexcept;
  std::expected<void, std::string> destroy() noexcept;

  void update_button_state() noexcept;

  bool is_pushing(SDL_GameControllerButton button) const noexcept;
  bool is_pushed(SDL_GameControllerButton button) const noexcept;
  bool is_separate(SDL_GameControllerButton button) const noexcept;

  [[nodiscard]]
  SDL_GameController *get_sdl_game_controller() const noexcept;

  bool operator ==(const game_controller &controller) const noexcept;
  bool operator !=(const game_controller &controller) const noexcept;

  explicit operator bool() const noexcept;

private:
  bool _is_key_state_update;
  bool _is_tick_frame_counter;
  uint8_t _frame_counter;
  int32_t _joystick_index;

  std::array<int8_t, SDL_CONTROLLER_BUTTON_MAX> _button_state;
  std::unique_ptr<SDL_GameController, decltype(&SDL_GameControllerClose)> _sdl_game_controller;
};
}

#endif

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
class gamecontroller {
public:
  gamecontroller(int32_t joystick_index) noexcept;

  std::expected<void, std::string> create() noexcept;
  std::expected<void, std::string> destroy() noexcept;

  void update() noexcept;
  void update_event(const SDL_Event &e) noexcept;

  bool is_pushing(SDL_GameControllerButton button) const noexcept;
  bool is_pushed(SDL_GameControllerButton button) const noexcept;
  bool is_upped(SDL_GameControllerButton button) const noexcept;

  int32_t get_joystick_index() const noexcept;

  [[nodiscard]]
  SDL_GameController *get_sdl_gamecontroller() const noexcept;

  bool operator ==(const gamecontroller &controller) const noexcept;
  bool operator !=(const gamecontroller &controller) const noexcept;

  explicit operator bool() const noexcept;

private:
  bool _is_button_pressed;
  bool _is_one_frame_passed;
  int32_t _last_down_button;
  int32_t _joystick_index;

  std::array<int8_t, SDL_CONTROLLER_BUTTON_MAX> _button_state;
  std::unique_ptr<SDL_GameController, decltype(&SDL_GameControllerClose)> _sdl_gamecontroller;

  void _update_button_state() noexcept;
};
}

#endif

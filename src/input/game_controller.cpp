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

#include "game_controller.hpp"
#include <iostream>

namespace sweet {
game_controller::game_controller(int32_t joystick_index)
  noexcept : _joystick_index{ joystick_index },
             _sdl_game_controller{ nullptr, SDL_GameControllerClose } {
}

std::expected<void, std::string> game_controller::create() noexcept {
  if(get_sdl_game_controller())
    return std::unexpected{ "The game controller has already been created." };

  SDL_GameController *sdl_game_controller = SDL_GameControllerOpen(_joystick_index);

  if(!sdl_game_controller)
    return std::unexpected{ "Failed to create SDL_GameController." };

  _sdl_game_controller.reset(sdl_game_controller);
  return{ };
}

std::expected<void, std::string> game_controller::destroy() noexcept {
  if(!get_sdl_game_controller())
    return std::unexpected{ "Game controller has not been created yet." };

  _sdl_game_controller.reset();
  return{ };
}

void game_controller::update_button_state() noexcept {
  if(!get_sdl_game_controller())
    return;

  for(size_t i = 0; i < _button_state.size(); ++i) {
    auto button = static_cast<SDL_GameControllerButton>(i);
    bool is_pushing_button = SDL_GameControllerGetButton(
      get_sdl_game_controller(),
      button
    );
    _button_state[i] = is_pushing_button
      ? is_pushing(button) ? 1 : 2
      : is_pushing(button) ? -1 : 0;
  }
}

bool game_controller::is_pushing(SDL_GameControllerButton button) const noexcept {
  return  get_sdl_game_controller() && _button_state[static_cast<int>(button)] > 0;
}

bool game_controller::is_pushed(SDL_GameControllerButton button) const noexcept {
  return get_sdl_game_controller() && _button_state[static_cast<int>(button)] == 2;
}

bool game_controller::is_separate(SDL_GameControllerButton button) const noexcept {
  return get_sdl_game_controller() && _button_state[static_cast<int>(button)] == -1;
}

int32_t game_controller::get_joystick_index() const noexcept {
	return _joystick_index;
}

SDL_GameController *game_controller::get_sdl_game_controller() const noexcept {
  return _sdl_game_controller.get();
}

bool game_controller::operator ==(const game_controller &controller) const noexcept {
  return get_sdl_game_controller() == controller.get_sdl_game_controller();
}

bool game_controller::operator !=(const game_controller &controller) const noexcept {
  return get_sdl_game_controller() != controller.get_sdl_game_controller();
}

game_controller::operator bool() const noexcept {
  return get_sdl_game_controller() != nullptr;
}
}

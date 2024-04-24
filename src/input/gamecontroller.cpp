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

#include "gamecontroller.hpp"

namespace sweet {
gamecontroller::gamecontroller(int32_t joystick_index)
  noexcept : _joystick_index{ joystick_index },
             _is_button_pressed{ false },
             _is_one_frame_passed{ false },
             _last_down_button{ SDL_CONTROLLER_BUTTON_INVALID },
             _button_state{ SDL_CONTROLLER_BUTTON_INVALID },
             _sdl_gamecontroller{ nullptr, SDL_GameControllerClose } {
}

std::expected<void, std::string> gamecontroller::create() noexcept {
  if(get_sdl_gamecontroller())
    return std::unexpected{ "The game controller has already been created." };

  _sdl_gamecontroller.reset(SDL_GameControllerOpen(_joystick_index));
  if(!_sdl_gamecontroller)
    return std::unexpected{ "Failed to create SDL_GameController." };
  return{ };
}

std::expected<void, std::string> gamecontroller::destroy() noexcept {
  if(!get_sdl_gamecontroller())
    return std::unexpected{ "Game controller has not been created yet." };

  _sdl_gamecontroller.reset();
  return{ };
}

void gamecontroller::update() noexcept {
  if(get_sdl_gamecontroller() && _is_button_pressed) {
    if(_is_one_frame_passed) {
      _update_button_state();
      _is_button_pressed = false;
      _is_one_frame_passed = false;
    } else {
      _is_one_frame_passed = true;
    }
  }
}

void gamecontroller::update_event(const SDL_Event &e) noexcept {
  if(!get_sdl_gamecontroller())
    return;

  switch(e.type) {
    case SDL_CONTROLLERBUTTONDOWN: {
      int8_t now_push_button = e.cbutton.button;
      if(_last_down_button == now_push_button)
        return;

      _last_down_button = now_push_button;
      _is_button_pressed = true;
      _update_button_state();
    } break;
    case SDL_CONTROLLERBUTTONUP: {
      _is_button_pressed = true;
      _last_down_button = SDL_CONTROLLER_BUTTON_INVALID;
      _update_button_state();
    } break;
  }
}

bool gamecontroller::is_pushing(SDL_GameControllerButton button) const noexcept {
  return  get_sdl_gamecontroller() && _button_state[static_cast<int>(button)] > 0;
}

bool gamecontroller::is_pushed(SDL_GameControllerButton button) const noexcept {
  return get_sdl_gamecontroller() && _button_state[static_cast<int>(button)] == 2;
}

bool gamecontroller::is_upped(SDL_GameControllerButton button) const noexcept {
  return get_sdl_gamecontroller() && _button_state[static_cast<int>(button)] == -1;
}

int32_t gamecontroller::get_joystick_index() const noexcept {
return _joystick_index;
}

SDL_GameController *gamecontroller::get_sdl_gamecontroller() const noexcept {
  return _sdl_gamecontroller.get();
}

bool gamecontroller::operator ==(const gamecontroller &controller) const noexcept {
  return get_sdl_gamecontroller() == controller.get_sdl_gamecontroller();
}

bool gamecontroller::operator !=(const gamecontroller &controller) const noexcept {
  return get_sdl_gamecontroller() != controller.get_sdl_gamecontroller();
}

gamecontroller::operator bool() const noexcept {
  return get_sdl_gamecontroller() != nullptr;
}

void gamecontroller::_update_button_state() noexcept {
  if(!get_sdl_gamecontroller())
    return;

  for(size_t i = 0; i < _button_state.size(); ++i) {
    SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(i);
    bool push_button = SDL_GameControllerGetButton(
      get_sdl_gamecontroller(),
      button
    );

    _button_state[i] = push_button
      ? _button_state[i] = is_pushing(button) ? 1 : 2
      : _button_state[i] = is_pushing(button) ? -1 : 0;
  }
}
}

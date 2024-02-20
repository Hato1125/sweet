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

#include "game_controller_manager.hpp"

namespace sweet {
using game_controller_it = std::vector<sweet::game_controller>::iterator;

bool game_controller_manager::_is_key_state_update{ false };
bool game_controller_manager::_is_tick_frame_counter{ false };
uint8_t game_controller_manager::_frame_counter{ 0u };

std::vector<sweet::game_controller> game_controller_manager::_game_controllers{ };

void game_controller_manager::update() noexcept {
  if(_is_key_state_update && !_is_tick_frame_counter && _frame_counter < 2) {
    _update_game_controller_state();
    ++_frame_counter;
    return;
  }

  if(_is_tick_frame_counter && _frame_counter < 2) {
    _update_game_controller_state();
    ++_frame_counter;
  }
}

void game_controller_manager::update_event(const SDL_Event &e) noexcept {
  switch(e.type) {
    case SDL_CONTROLLERDEVICEADDED: {
      _add_game_controller(e.cdevice.which);
      break;
    }
    case SDL_CONTROLLERDEVICEREMOVED: {
      _remove_game_controller(e.cdevice.which);
      break;
    }
    case SDL_CONTROLLERBUTTONDOWN: {
      if(_game_controllers.empty())
        return;

      _is_key_state_update = true;
      _is_tick_frame_counter = false;
      _frame_counter = 0u;
      break;
    }
    case SDL_CONTROLLERBUTTONUP: {
      if(_game_controllers.empty())
        return;

      _is_key_state_update = false;
      _is_tick_frame_counter = true;
      _frame_counter = 0u;
      break;
    }
  }
}

bool game_controller_manager::is_pushing(
  int32_t joystic_index,
  SDL_GameControllerButton button
) noexcept {
  auto it = _get_game_controller_iterator(joystic_index);
  return it != _game_controllers.end() && it->is_pushing(button);
}

bool game_controller_manager::is_pushed(
  int32_t joystic_index,
  SDL_GameControllerButton button
) noexcept {
  auto it = _get_game_controller_iterator(joystic_index);
  return it != _game_controllers.end() && it->is_pushed(button);
}

bool game_controller_manager::is_separate(
  int32_t joystic_index,
  SDL_GameControllerButton button
) noexcept {
  auto it = _get_game_controller_iterator(joystic_index);
  return it != _game_controllers.end() && it->is_separate(button);
}

void game_controller_manager::_update_game_controller_state() noexcept {
  for(auto &controller : _game_controllers)
    controller.update_button_state();
}

void game_controller_manager::_add_game_controller(int32_t joystick_index) noexcept {
  sweet::game_controller controller{ joystick_index };
  if(auto result = controller.create(); result) {
    _game_controllers.push_back(std::move(controller));
  }
}

void game_controller_manager::_remove_game_controller(int32_t joystick_index) noexcept {
  auto it = _get_game_controller_iterator(joystick_index);
  if(_is_contains_game_controller(it)) {
    [[maybe_unused]] auto destroy = it->destroy();
    _game_controllers.erase(it);
  }
}

game_controller_it game_controller_manager::_get_game_controller_iterator(int32_t joystick_index) noexcept {
  return std::find_if(
    _game_controllers.begin(),
    _game_controllers.end(),
    [&joystick_index](const sweet::game_controller &controller) {
      return joystick_index == controller.get_joystick_index();
    }
  );
}

bool game_controller_manager::_is_contains_game_controller(game_controller_it &it) noexcept {
  return it != _game_controllers.end();
}
}

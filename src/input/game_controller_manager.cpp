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
sweet::game_controller game_controller_manager::_empty_controller{ -1 };
std::vector<sweet::game_controller> game_controller_manager::_controllers{ };

void game_controller_manager::update() noexcept {
  for(auto &controller : _controllers)
    controller.update();
}

void game_controller_manager::update_event(const SDL_Event &e) noexcept {
  switch(e.type) {
    case SDL_CONTROLLERDEVICEADDED: {
      _add_game_controller(e.cdevice.which);
    } break;
    case SDL_CONTROLLERDEVICEREMOVED: {
      _remove_game_controller(e.cdevice.which);
    } break;
    default: {
      for(auto &controller : _controllers)
        controller.update_event(e);
    } break;
  }
}

sweet::game_controller &sweet::game_controller_manager::get(
  int32_t joystick_index
) noexcept {
  auto it =find_joystick_index(joystick_index);
  if(it != _controllers.end())
    return *it;
  return _empty_controller;
}

void game_controller_manager::_add_game_controller(int32_t joystick_index) noexcept {
  sweet::game_controller controller{ joystick_index };
  if(auto result = controller.create(); result)
    _controllers.push_back(std::move(controller));
}

void game_controller_manager::_remove_game_controller(int32_t joystick_index) noexcept {
  _controllers.erase(find_joystick_index(joystick_index));
}

std::vector<sweet::game_controller>::iterator game_controller_manager::find_joystick_index(
  int32_t joystick_index
) noexcept {
  return std::find_if(
    _controllers.begin(),
    _controllers.end(),
    [&joystick_index](sweet::game_controller &controller){
      return joystick_index == controller.get_joystick_index();
  });
}
}

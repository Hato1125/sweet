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

#include "gamecontroller_manager.hpp"

namespace sweet {
using gamecontroller_it = std::vector<sweet::gamecontroller>::iterator;

sweet::gamecontroller gamecontroller_manager::_empty_controller{ -1 };
std::vector<sweet::gamecontroller> gamecontroller_manager::_controllers{ };

void gamecontroller_manager::update() noexcept {
  for(auto &controller : _controllers)
    controller.update();
}

void gamecontroller_manager::update_event(const SDL_Event &e) noexcept {
  switch(e.type) {
    case SDL_CONTROLLERDEVICEADDED: {
      _add_gamecontroller(e.cdevice.which);
    } break;
    case SDL_CONTROLLERDEVICEREMOVED: {
      _remove_gamecontroller(e.cdevice.which);
    } break;
    default: {
      for(auto &controller : _controllers)
        controller.update_event(e);
    } break;
  }
}

sweet::gamecontroller &sweet::gamecontroller_manager::get(
  int32_t index
) noexcept {
  auto it = _find_joystick_it(index);
  return it != _controllers.end() ? *it : _empty_controller;
}

gamecontroller_it gamecontroller_manager::begin() noexcept {
  return _controllers.begin();
}

gamecontroller_it gamecontroller_manager::end() noexcept {
  return _controllers.end();
}

void gamecontroller_manager::_add_gamecontroller(int32_t index) noexcept {
  sweet::gamecontroller controller{ index };
  if(auto result = controller.create(); result)
    _controllers.push_back(std::move(controller));
}

void gamecontroller_manager::_remove_gamecontroller(int32_t index) noexcept {
  _controllers.erase(_find_joystick_it(index));
}

gamecontroller_it gamecontroller_manager::_find_joystick_it(
  int32_t index 
) noexcept {
  return std::find_if(
    _controllers.begin(),
    _controllers.end(),
    [&index](sweet::gamecontroller &controller){
      return index == controller.get_joystick_index();
  });
}
}

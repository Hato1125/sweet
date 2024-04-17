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

#include "scene_manager.hpp"

namespace sweet {
using shared_scene = std::shared_ptr<sweet::scene>;
using shared_scene_elem = std::shared_ptr<sweet::scene_element>;

std::string scene_manager::_current_scene_name{};
std::map<std::string, shared_scene> scene_manager::_scenes{};

void scene_manager::regist(
  const std::string &name,
  const shared_scene &scene
) noexcept {
  if(_scenes.contains(name) || name.empty())
    return;

  _scenes.insert({ name, scene });
  if(_current_scene_name.empty())
    change(name);
}

void scene_manager::regist(
  const std::map<const std::string, const shared_scene> &scenes
) noexcept {
  for(auto &scene : scenes)
    regist(scene.first, scene.second);
}

void scene_manager::remove(const std::string &name) noexcept {
  if(_scenes.contains(name))
    _scenes.erase(name);
}

void scene_manager::change(const std::string &name) noexcept {
  if(!_scenes.contains(name))
    return;

  if(!_current_scene_name.empty()) {
    _scenes[_current_scene_name]->inactive();
    _scenes[_current_scene_name]->state = sweet::scene_state::inactive;
  }

  _current_scene_name = name;
  _scenes[_current_scene_name]->active();
  _scenes[_current_scene_name]->state = sweet::scene_state::active;
}

void scene_manager::update() {
  if(_current_scene_name.empty())
    return;
  _scenes[_current_scene_name]->update();
}

void scene_manager::render() {
  if(_current_scene_name.empty())
    return;
  _scenes[_current_scene_name]->render();
}
}

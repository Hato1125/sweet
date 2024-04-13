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

#ifndef _LIBSWEET_SCENE_SCENE_MANAGER_HPP
#define _LIBSWEET_SCENE_SCENE_MANAGER_HPP

#include <map>
#include <string>
#include <memory>

#include "scene.hpp"

namespace sweet {
class scene_manager final {
using shared_scene = std::shared_ptr<sweet::scene>;
using shared_scene_elem = std::shared_ptr<sweet::scene_element>;

public:
  scene_manager() = delete;
  ~scene_manager() = delete;

  static void regist(
    const std::string &name,
    const shared_scene &scene
  ) noexcept;

  static void regist(
    const std::map<const std::string, const shared_scene> &scenes
  ) noexcept;

  static void remove(const std::string &name) noexcept;
  static void change(const std::string &name) noexcept;

  static void update();
  static void render();

private:
  static std::string _current_scene_name; 
  static std::map<std::string, shared_scene> _scenes;
};
}

#endif

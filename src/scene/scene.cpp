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

#include "scene.hpp"

namespace sweet {
void scene_element::active() {
}

void scene_element::inactive() {
}

void scene_element::update() {
}

void scene_element::render() {
}

void scene::active() {
  for(auto &element : elements)
    element->active();
}

void scene::inactive() {
  for(auto &element : elements)
    element->inactive();
}

void scene::update() {
  if(state == scene_state::idle
    || state == scene_state::inactive)
    return;

  for(auto &element : elements) {
    if(element->state == scene_state::idle
      || element->state == scene_state::inactive)
      continue;
    element->update();
  }
}

void scene::render() {
  if(state == scene_state::inactive)
    return;

  for(auto &element : elements) {
    if(element->state == scene_state::inactive)
      continue;
    element->render();
  }
}
}

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

#ifndef _LIBSWEET_RESOURCE_RESOURCE_LOADER_HPP
#define _LIBSWEET_RESOURCE_RESOURCE_LOADER_HPP

#include <string>
#include <memory>
#include <vector>
#include <expected>
#include <type_traits>
#include <unordered_map>

#include "resource.hpp"

namespace sweet {
template <typename Type>
class basic_resource_loader {
public:
  basic_resource_loader(
    const std::shared_ptr<Type> &empty,
    const std::unordered_map<std::string, std::shared_ptr<Type>> resources = { }
  ) noexcept : _is_loaded{ false },
    _empty{ empty },
    _resources{ resources } {
  }

  std::expected<void, std::vector<std::string>> load() noexcept {
    if(_is_loaded)
      return{ };

    std::vector<std::string> errors{ };
    for(auto const &[key, value] : _resources) {
      auto result = value->load();
      if(!result)
        errors.push_back(result.error());
    }
    _is_loaded = true;

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }

  std::expected<void, std::vector<std::string>> unload() noexcept {
    if(!_is_loaded)
      return{ };

    std::vector<std::string> errors{ };
    for(auto const &[key, value] : _resources) {
      auto result = value->load();
      if(!result)
        errors.push_back(result.error());
    }

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }

private:
  bool _is_loaded;

  std::shared_ptr<Type> _empty;
  std::unordered_map<std::string, std::shared_ptr<Type>> _resources;
};
}

#endif

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

#ifndef _LIBSWEET_RESOURCE_RESOURCE_BUNDLE_HPP
#define _LIBSWEET_RESOURCE_RESOURCE_BUNDLE_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstdint>
#include <type_traits>
#include <unordered_map>

#include "resource.hpp"
#include "parallel.hpp"

namespace sweet {
template <typename Type, uint32_t Sqlit = 4>
class resource_bundle {
static_assert(std::is_base_of<sweet::resource, Type>::value == true);

using element = std::shared_ptr<Type>;
using element_name = std::string;
using element_map = std::unordered_map<element_name, element>;

public:
  resource_bundle(
    const element &empty_element,
    const element_map &elements
  ) noexcept : _empty_element{ empty_element },
               _elements{ elements },
               _load_element_names{ _sqlit_element_name() } {
  }

  std::expected<void, std::vector<std::string>> load() noexcept {
    if(_is_loaded)
      return{ };

    using return_type = std::expected<void, std::vector<std::string>>;

    std::vector<std::function<return_type()>> functions{ };

    for(const auto &name : _load_element_names) {
      functions.push_back([&name, this]() -> return_type {
        return _load_elements(name);
      });
    }
    sweet::parallel<return_type> parallel{ std::launch::async, functions };

    _is_loaded = true;

    auto errors = _get_errors<return_type>(parallel.stand_by());
    return errors.empty()
      ? return_type{ }
      : std::unexpected{ errors };
  }

  std::expected<void, std::vector<std::string>> unload() noexcept {
    if(!_is_loaded)
      return{ };

    using return_type = std::expected<void, std::vector<std::string>>;

    std::vector<std::function<return_type()>> functions{ };
    for(const auto &name : _load_element_names) {
      functions.push_back([&name, this]() -> return_type {
        return _unload_elements(name);
      });
    }
    sweet::parallel<return_type> parallel{ std::launch::async, functions };

    _is_loaded = false;

    auto errors = _get_errors<return_type>(parallel.stand_by());
    return errors.empty()
      ? return_type{ }
      : std::unexpected{ errors };
  }

  std::expected<void, std::vector<std::string>> release() noexcept {
    using return_type = std::expected<void, std::vector<std::string>>;

    std::vector<std::function<return_type()>> functions{ };
    for(const auto &name : _load_element_names) {
      functions.push_back([&name, this]() -> return_type {
        return _release_elements(name);
      });
    }
    sweet::parallel<return_type> parallel{ std::launch::async, functions };

    auto errors = _get_errors<return_type>(parallel.stand_by());

    return errors.empty()
      ? return_type{ }
      : std::unexpected{ errors };
  }

private:
  bool _is_loaded;

  element _empty_element;
  element_map _elements;

  std::array<std::vector<element_name>, Sqlit> _load_element_names;

  std::array<std::vector<element_name>, Sqlit> _sqlit_element_name() const noexcept {
    auto element_it = _elements.begin();

    size_t element_num = _elements.size();
    size_t sqlit_num = element_num / Sqlit;

    std::array<std::vector<element_name>, Sqlit> sqlit_names{ };
    for(size_t i = 0; i < Sqlit; ++i) {
      for(size_t j = 0; j < sqlit_num; ++j) {
        sqlit_names[i].push_back(element_it->first);
        ++element_it;
      }
    }

    if(size_t rem = element_num % Sqlit; rem != 0) {
      for(size_t i = 0; i < rem; ++i) {
        sqlit_names[i].push_back(element_it->first);
        ++element_it;
      }
    }
    return sqlit_names;
  }

  template <typename RType>
  std::vector<std::string> _get_errors(
    const std::vector<RType> &results
  ) const noexcept {
    std::vector<std::string> errors{ }; 
    for(const auto &result : results) {
      if(!result) {
        for(const auto &error : result.error())
          errors.push_back(error);
      }
    }
    return errors;
  }

  std::expected<void, std::vector<std::string>> _load_elements(
    const std::vector<element_name> &element_names
  ) noexcept {
    std::vector<std::string> _errors{ };
    for(const auto &name : element_names) {
      if(auto result = _elements[name]->load(); !result)
        _errors.push_back(result.error());
    }
    return _errors.empty()
      ? std::expected<void, std::vector<std::string>>{ }
      : std::unexpected{ _errors };
  }

  std::expected<void, std::vector<std::string>> _unload_elements(
    const std::vector<element_name> &element_names
  ) noexcept {
    std::vector<std::string> _errors{ };
    for(const auto &name : element_names) {
      if(auto result = _elements[name]->unload(); !result)
        _errors.push_back(result.error());
    }
    return _errors.empty()
      ? std::expected<void, std::vector<std::string>>{ }
      : std::unexpected{ _errors };
  }

  std::expected<void, std::vector<std::string>> _release_elements(
    const std::vector<element_name> &element_names
  ) noexcept {
    std::vector<std::string> _errors{ };
    for(const auto &name : element_names) {
      if(auto result = _elements[name]->release(); !result)
        _errors.push_back(result.error());
    }
    return _errors.empty()
      ? std::expected<void, std::vector<std::string>>{ }
      : std::unexpected{ _errors };
  }
};
}

#endif

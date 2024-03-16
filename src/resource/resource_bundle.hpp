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
#include <optional>
#include <type_traits>
#include <unordered_map>

#include "resource.hpp"
#include "parallel.hpp"
#include "texture.hpp"
#include "font.hpp"

namespace sweet {
enum class bundle_state {
  none,
  loaded,
  unloaded,
  released
};

template <typename Type>
struct resource_provider {
  const std::shared_ptr<Type> &value;
  resource_provider(const std::shared_ptr<Type> &value)
    noexcept : value{ value } {
  }
};

template <typename Type, uint32_t Split = 4>
class basic_resource_bundle {
static_assert(std::is_base_of<sweet::resource, Type>::value == true);

using resource_elem = std::shared_ptr<Type>;
using resource_name = std::string;
using resource_map = std::unordered_map<resource_name, resource_elem>;

public:
  basic_resource_bundle()
    noexcept : _state{ bundle_state::none },
               _empty_resource{ nullptr },
               _resources{ },
               _procces_names{ } {
  }

  basic_resource_bundle(
    const resource_elem &empty_resource,
    const resource_map &resources
  ) noexcept : _state{ bundle_state::none },
               _empty_resource{ empty_resource },
               _resources{ resources },
               _procces_names{ _split_process_names() } {
  }

  basic_resource_bundle<Type, Split> set_empty_resource(
    const resource_elem &empty_resource
  ) noexcept {
    if(_empty_resource)
      return *this;
    _empty_resource = empty_resource;

    return *this;
  }

  basic_resource_bundle<Type, Split> set_resources(
    const resource_map &resources
  ) noexcept {
    if(!_resources.empty())
      return *this;
    _resources = resources;
    _procces_names = _split_process_names();

    return *this;
  }

  std::expected<void, std::string> load() noexcept {
    if(_resources.empty())
      return std::unexpected{ "Resource is not registered." };

    if(_state == bundle_state::loaded)
      return std::unexpected{ "Already loaded." };

    if(_state == bundle_state::unloaded)
      return std::unexpected{ "Cannot load because it has already been unloaded." };
    _state = bundle_state::loaded;

    return _running_process([this](const resource_name &name){
      return _resources[name]->load();
    });
  }

  std::expected<void, std::string> unload() noexcept {
    if(_state == bundle_state::unloaded || _state == bundle_state::none)
      return std::unexpected{ "It cannot be unloaded because it has not been loaded yet." };
    _state = bundle_state::unloaded;

    auto result = _running_process([this](const resource_name &name){
      return _resources[name]->unload();
    });
    _resources.clear();

    return result;
  }

  std::expected<void, std::string> release() noexcept {
    if(_state == bundle_state::released || _state == bundle_state::none)
      return std::unexpected{ "It cannot be unloaded because it has not been loaded yet." };

    if(_state == bundle_state::unloaded)
      return std::unexpected{ "Cannot load because it has already been unloaded." };
    _state = bundle_state::released;

    return _running_process([this](const resource_name &name){
      return _resources[name]->release();
    });
  }

  std::expected<void, std::string> hot_reload() noexcept {
    if(_state == bundle_state::loaded)
      [[maybe_unused]] auto _ = release();

    if(auto result = load(); !result)
      return std::unexpected{ result.error() };
    return{ };
  }

  std::optional<resource_provider<Type>> get(const resource_name &name) noexcept {
    if(_resources.contains(name))
      return { _resources[name] };

    if(_empty_resource)
      return { _empty_resource };
    return std::nullopt;
  }

  const std::optional<resource_provider<Type>> get(const resource_name &name) const noexcept {
    if(_resources.contains(name))
      return { _resources[name] };

    if(_empty_resource)
      return { _empty_resource };
    return std::nullopt;
  }

  bundle_state state() const noexcept {
    return _state;
  }

  resource_map::size_type size() const noexcept {
    return _resources.size();
  }

  resource_map::iterator begin() noexcept {
    return _resources.begin();
  }

  const resource_map::iterator begin() const noexcept {
    return _resources.begin();
  }

  resource_map::iterator end() noexcept {
    return _resources.end();
  }

  const resource_map::iterator end() const noexcept {
    return _resources.end();
  }

  std::optional<resource_provider<Type>> operator[](const resource_name &name) noexcept {
    return get(name);
  }

  const std::optional<resource_provider<Type>> operator[](const resource_name &name) const noexcept {
    return get(name);
  }

private:
  bundle_state _state;
  resource_elem _empty_resource;
  resource_map _resources;

  std::array<std::vector<resource_name>, Split> _procces_names;

  std::array<std::vector<resource_name>, Split> _split_process_names() const noexcept {
    std::array<std::vector<resource_name>, Split> names{ };

    auto names_it = names.begin();
    auto names_end_it = names.end();
    for(const auto &[key, value] : _resources) {
      names_it->push_back(key);
      if(std::next(names_it) == names_end_it)
        names_it = names.begin();
      else
        std::advance(names_it, 1);
    }

    return names;
  }

  std::vector<std::string> _process_resources(
    const std::vector<resource_name> &process_names,
    const std::function<std::expected<void, resource_name>(const resource_name &name)> &process_func
  ) noexcept {
    std::vector<std::string> process_error{ };
    for(const auto &name : process_names) {
      if(auto result = process_func(name); !result)
        process_error.push_back(result.error());
    }
    return process_error;
  }

  std::expected<void, std::string> _running_process(
    const std::function<std::expected<void, resource_name>(const resource_name &name)> &process_func
  ) noexcept {
    std::vector<std::function<std::vector<std::string>()>> running_functions{ };
    for(const auto &name : _procces_names) {
      running_functions.emplace_back([this, &process_func, &name](){
        return _process_resources(name, process_func);
      });
    }

    sweet::parallel<std::vector<std::string>> parallel {
      std::launch::async,
      running_functions
    };
    auto results = parallel.stand_by();

    std::vector<std::string> errors{ };
    for(const auto &result : results) {
      if(!result.empty())
        errors.insert(errors.end(), result.begin(), result.end());
    }

    if(!errors.empty())
      return std::unexpected{ "Some resources are failing the operation." };
    return{ };
  }
};

template <uint32_t Split = 4>
using texture_bundle = basic_resource_bundle<sweet::texture, Split>;

template <uint32_t Split = 4>
using font_bundle = basic_resource_bundle<sweet::font, Split>;
}

#endif

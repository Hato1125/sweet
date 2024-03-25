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

#ifndef _LIBSWEET_RESOURCE_RESOURCE_MANAGER_HPP
#define _LIBSWEET_RESOURCE_RESOURCE_MANAGER_HPP

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <memory>
#include <type_traits>
#include <unordered_map>

#include "resource.hpp"
#include "parallel.hpp"
#include "font.hpp"
#include "texture.hpp"

namespace sweet {
enum class resource_load_state : int8_t {
  idle,
  loaded,
  unloaded,
  released
};

template <class ResourceType,
          size_t DivisionNum = 4u,
          bool IsNullError = true>
class basic_resource_manager {
static_assert(DivisionNum > 0u,
              "The number of divisions must be 1 or more.");

static_assert(std::is_base_of<sweet::resource, ResourceType>::value,
              "The type ResourceType must inherit sweet::resource.");

using resource_name       = std::string;
using resource_elem       = std::shared_ptr<ResourceType>;
using resource_map        = std::unordered_map<resource_name, resource_elem>;
using resource_array      = std::array<std::vector<resource_name>, DivisionNum>;
using process_return_type = std::expected<void, std::string>;

public:
  basic_resource_manager(
    const resource_elem &empty,
    const resource_map &resources
  ) : _state{ resource_load_state::idle },
      _empty_resource{ empty },
      _resources{ resources } {
    if(!_empty_resource && IsNullError)
      throw std::runtime_error("Empty resource cannot be set to null.");
    _dividing_resources();
  }

  basic_resource_manager(
    resource_elem &&empty,
    resource_map &&resource
  ) : _state{ resource_load_state::idle },
      _empty_resource{ empty },
      _resources{ resource } {
    if(!_empty_resource && IsNullError)
      throw std::runtime_error("Empty resource cannot be set to null.");
    _dividing_resources();
  }

  std::expected<void, std::string> load() noexcept {
    if(_state == resource_load_state::loaded)
      return std::unexpected{ "Already loaded." };
    else if(_state == resource_load_state::unloaded)
      return std::unexpected{ "Already unloaded." };
    _state = resource_load_state::loaded;

    return _running_all_process([this](const resource_name &name){
      return _resources[name]->load();
    });
  }

  std::expected<void, std::string> unload() noexcept {
    if(_state == resource_load_state::unloaded)
      return std::unexpected{ "Already loaded." };
    else if(_state == resource_load_state::idle)
      return std::unexpected{ "Not loaded yet." };
    _state = resource_load_state::unloaded;

    auto rs = _running_all_process([this](const resource_name &name){
      return _resources[name]->unload();
    });
    _resources.clear();

    return rs;
  }

  std::expected<void, std::string> release() noexcept {
    if(_state == resource_load_state::released)
      return std::unexpected{ "Already released." };
    else if(_state == resource_load_state::unloaded)
      return std::unexpected{ "Already unloaded." };
    else if(_state == resource_load_state::idle)
      return std::unexpected{ "Not loaded yet." };
    _state = resource_load_state::released;

    return _running_all_process([this](const resource_name &name){
      return _resources[name]->release();
    });
  }

  std::expected<void, std::string> hot_reload() noexcept {
    if(_state == resource_load_state::loaded)
      [[maybe_unused]] auto _ = release();

    if(auto rs = load(); !rs)
      return std::unexpected{ rs.error() };
    return{ };
  }

  resource_elem get(const resource_name &name) {
    return _get_elem(name);
  }

  const resource_elem &get(const resource_name &name) const {
    return _get_elem(name);
  }

  resource_elem &operator[](const resource_name &name) {
    return _get_elem(name);
  }

  const resource_elem &operator[](const resource_name &name) const {
    return _get_elem(name);
  }

  size_t size() const noexcept {
    return _resources.size();
  }

  resource_load_state state() const noexcept {
    return _state;
  }

  resource_map::iterator begin() noexcept {
    _resources.begin();
  }

  const resource_map::iterator begin() const noexcept {
    _resources.begin();
  }

  resource_map::iterator end() noexcept {
    _resources.end();
  }

  const resource_map::iterator end() const noexcept {
    _resources.end();
  }

private:
  resource_load_state _state;
  resource_elem _empty_resource;
  resource_map _resources;
  resource_array _divided_resources;

  void _dividing_resources() noexcept {
    auto it = _divided_resources.begin();
    for(const auto &rs : _resources) {
      it->push_back(rs.first);
      it = std::next(it) == _divided_resources.end()
        ? _divided_resources.begin()
        : ++it;
    }
  }

  std::string _running_process(
    const std::vector<resource_name> &names,
    const std::function<process_return_type(const resource_name&)> &func
  ) noexcept {
    std::string error_message;
    for(const auto &name : names) {
      if(auto rs = func(name); !rs)
        error_message.append(name + ": " + rs.error() + "\n");
    }
    return error_message;
  }

  std::expected<void, std::string> _running_all_process(
    const std::function<process_return_type(const resource_name&)> &func
  ) noexcept {
    std::vector<std::function<std::string()>> funcs;
    for(const auto &names : _divided_resources) {
      funcs.emplace_back([this, &func, &names](){
        return _running_process(names, func);
      });
    }

    sweet::parallel<std::string> parallel{ std::launch::async, funcs };
    std::vector<std::string> results = parallel.stand_by();
    std::string error_message;
    for(const auto &result : results)
      error_message.append(result);

    return error_message.empty()
      ? std::expected<void, std::string>{ }
      : std::unexpected{ error_message };
  }

  resource_elem &_get_elem(const resource_name &name) {
    if(_resources.contains(name))
      return _resources[name];

    if(!_empty_resource && IsNullError)
      throw std::runtime_error("An empty resource is set to Null.");
    return _empty_resource;
  }
};

// There is a null error.
template <size_t DivisionNum = 4u>
using texture_manager = basic_resource_manager<sweet::texture, DivisionNum, true>;

template <size_t DivisionNum = 4u>
using font_manager = basic_resource_manager<sweet::font, DivisionNum, true>;

// Not null error.
template <size_t DivisionNum = 4u>
using texture_manager_not_null_err = basic_resource_manager<sweet::texture, DivisionNum, false>;

template <size_t DivisionNum = 4u>
using font_manager_not_null_err = basic_resource_manager<sweet::font, DivisionNum, false>;
}

#endif

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

#ifndef _LIBSWEET_RESOURCE_PARALLEL_RESOURCE_CHUNK_HPP
#define _LIBSWEET_RESOURCE_PARALLEL_RESOURCE_CHUNK_HPP

#include <array>
#include <string>
#include <memory>
#include <vector>
#include <cstdint>
#include <expected>
#include <functional>
#include <unordered_map>

#include <iostream>

#include "parallel.hpp"
#include "resource.hpp"

namespace sweet {
template <typename Type, uint32_t SqlitNum = 4>
class basic_parallel_resource_chunk {
public:
  basic_parallel_resource_chunk(
    const std::shared_ptr<Type> &empty,
    const std::unordered_map<std::string, std::shared_ptr<Type>> resources = { }
  ) noexcept : _is_loaded{ false },
    _empty{ empty },
    _resources{ resources } {
  }

  std::expected<void, std::vector<std::string>> load() noexcept {
    if(_is_loaded)
      return{ };

    using return_type = std::expected<void, std::vector<std::string>>;

    auto names = _sqlit_resource();

    std::vector<std::string> errors{ };
    std::vector<std::function<return_type()>> funcs{ };

    for(const auto &name_array : names) {
      funcs.push_back([&name_array, this]() {
        return this->_load_resource(name_array);
      });
    }
    sweet::parallel<return_type> parallel{ std::launch::async, funcs };

    auto results = parallel.stand_by();
    if(!results.empty()) {
      for(const auto &rerrors : results) {
        if(!rerrors) {
          for(const auto &error : rerrors.error())
            errors.push_back(error);
        }
      }
    }

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }

  std::expected<void, std::vector<std::string>> unload() noexcept {
    if(!_is_loaded)
      return{ };

    using return_type = std::expected<void, std::vector<std::string>>;

    auto names = _sqlit_resource();

    std::vector<std::string> errors{ };
    std::vector<std::function<return_type()>> funcs{ };

    for(const auto &name_array : names) {
      funcs.push_back([&name_array, this]() {
        return this->_unload_resource(name_array);
      });
    }
    sweet::parallel<return_type> parallel{ std::launch::async, funcs };

    auto results = parallel.stand_by();
    if(!results.empty()) {
      for(const auto &rerrors : results) {
        if(!rerrors) {
          for(const auto &error : rerrors.error())
            errors.push_back(error);
        }
      }
    }

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }

  std::expected<void, std::vector<std::string>> release() noexcept {
    if(!_is_loaded)
      return{ };

    using return_type = std::expected<void, std::vector<std::string>>;

    auto names = _sqlit_resource();

    std::vector<std::string> errors{ };
    std::vector<std::function<return_type()>> funcs{ };

    for(const auto &name_array : names) {
      funcs.push_back([&name_array, this]() {
        return this->_release_resource(name_array);
      });
    }
    sweet::parallel<return_type> parallel{ std::launch::async, funcs };

    auto results = parallel.stand_by();
    if(!results.empty()) {
      for(const auto &rerrors : results) {
        if(!rerrors) {
          for(const auto &error : rerrors.error())
            errors.push_back(error);
        }
      }
    }

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }

  std::shared_ptr<Type> get(const std::string &name) noexcept {
    if(_resources.contains(name))
      return _resources[name];
    return _empty;
  }

  bool is_loaded() const noexcept {
    return _is_loaded;
  }

private:
  bool _is_loaded;

  std::shared_ptr<Type> _empty;
  std::unordered_map<std::string, std::shared_ptr<Type>> _resources;

  std::array<std::vector<std::string>, SqlitNum> _sqlit_resource() noexcept {
    const size_t resource_num = _resources.size();
    const uint32_t elem_num = resource_num / SqlitNum;

    auto resource_it = _resources.begin();

    std::array<std::vector<std::string>, SqlitNum> result{ };
    for(uint32_t i = 0; i < SqlitNum; ++i) {
      for(uint32_t j = 0; j < elem_num; ++j) {
        result[i].push_back(resource_it->first);
        ++resource_it;
      }
    }

    if(resource_num % SqlitNum != 0) {
      uint32_t rem =  resource_num % SqlitNum;
      uint32_t index = resource_num - rem;

      for(uint32_t i = 0; i < rem; ++i) {
        result[i].push_back(resource_it->first);
        ++resource_it;
      }
    }

    return result;
  }

  std::expected<void, std::vector<std::string>> _load_resource(
    const std::vector<std::string> &names
  ) noexcept {
    std::vector<std::string> errors{ };
    for(const auto &name : names) {
      auto lresult = _resources[name]->load();
      if(!lresult)
        errors.push_back(lresult.error());
    }

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }

  std::expected<void, std::vector<std::string>> _unload_resource(
    const std::vector<std::string> &names
  ) noexcept {
    std::vector<std::string> errors{ };
    for(const auto &name : names) {
      auto lresult = _resources[name]->unload();
      if(!lresult)
        errors.push_back(lresult.error());
    }

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }

  std::expected<void, std::vector<std::string>> _release_resource(
    const std::vector<std::string> &names
  ) noexcept {
    std::vector<std::string> errors{ };
    for(const auto &name : names) {
      auto lresult = _resources[name]->unload();
      if(!lresult)
        errors.push_back(lresult.error());
    }

    if(!errors.empty())
      return std::unexpected{ errors };
    return{ };
  }
};
}

#endif

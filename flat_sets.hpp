#pragma once
#include <boost/unordered/unordered_flat_set.hpp>

namespace boost {

      template <typename T>
      class unordered_flat_multiset {

          public:
            void insert(const T &value) {
                  ++data[value];
            }

            void erase(const T &value) {
                  auto it = this->data.find(value);
                  if (it != this->data.end()) {
                        if (!(--it->second)) {
                              this->data.erase(it);
                        }
                  }
                  return;
            }

            std::size_t count(const T &value) const {
                  const auto it = this->data.find(value);
                  return it != this->data.end() ? it->second : 0u;
            }

            std::size_t size() const {
                  std::size_t total = 0u;
                  for (const auto &[key, count] : this->data) {
                        total += count;
                  }
                  return total;
            }

            auto reserve(const std::size_t amt) {
                  this->data.reserve(amt);
                  return;
            } 
            auto empty() const {
                  return this->data.empty();
            }
            auto clear() {
                  this->data.clear();
                  return;
            }

            auto begin() {
                  return flattened_iterator(data.begin(), data.end());
            }
            auto end() {
                  return flattened_iterator(data.end(), data.end());
            }
            auto begin() const {
                  return flattened_iterator(data.begin(), data.end());
            }
            auto end() const {
                  return flattened_iterator(data.end(), data.end());
            }

          private:

            boost::unordered_flat_map<T, std::size_t> data;
            struct flattened_iterator {

                  boost::unordered_flat_map<T, std::size_t>::const_iterator map_it;
                  boost::unordered_flat_map<T, std::size_t>::const_iterator map_end;
                  std::size_t repeat_count;

                  flattened_iterator(boost::unordered_flat_map<T, std::size_t>::const_iterator it, boost::unordered_flat_map<T, std::size_t>::const_iterator end)
                      : map_it(it), map_end(end), repeat_count(it != end ? it->second : 0) {
                  }

                  auto operator*() const {
                        return this->map_it->first;
                  }
                  auto operator->() const {
                        return &this->map_it->first;
                  }

                  flattened_iterator &operator++() {
                        if (this->map_it == this->map_end) {
                              return *this;
                        }
                        if (!(--this->repeat_count)) {
                              ++this->map_it;
                              this->repeat_count = this->map_it != this->map_end ? this->map_it->second : 0u;
                        }
                        return *this;
                  }

                  flattened_iterator operator++(int) {
                        auto tmp = *this;
                        ++(*this);
                        return tmp;
                  }

                  bool operator==(const flattened_iterator &other) const {
                        return this->map_it == other.map_it && this->repeat_count == other.repeat_count;
                  }
                  bool operator!=(const flattened_iterator &other) const {
                        return !(*this == other);
                  }
            };
      };
} // namespace boost

#include <array>
#include <cstdint>
#include <stdexcept>

namespace boost {

      template <typename T, std::size_t N>
      class fixed_vector {
          public:
            constexpr fixed_vector()
                : size_(0) {
            }

            constexpr fixed_vector(std::initializer_list<T> init_list)
                : size_(init_list.size()) {

                  static_assert(init_list.size() <= N, "Initializer list exceeds maximum size");
                  if (init_list.size() > N) {
                        throw std::out_of_range("Initializer list exceeds maximum size");
                  }
                  std::copy_n(init_list.begin(), this->size_, this->data.begin());
                  return;
            }

            using iterator = typename std::array<T, N>::iterator;
            using const_iterator = typename std::array<T, N>::const_iterator;

            constexpr std::size_t max_size() const {
                  return N;
            }
            constexpr std::size_t size() const {
                  return this->size_;
            }
            constexpr bool empty() const {
                  return !this->size();
            }
            constexpr void push_back(const T &value) {
                  if (this->size_ >= N) {
                        throw std::out_of_range("Overflow");
                  }
                  this->data[this->size_++] = value;
                  return;
            }
            constexpr void push_back(T &&value) {
                  if (this->size_ >= N) {
                        throw std::out_of_range("Overflow");
                  }
                  this->data[this->size_++] = std::move(value);
                  return;
            }
            constexpr void pop_back() {
                  if (!this->size_) {
                        throw std::out_of_range("Underflow");
                  }
                  --this->size_;
                  return;
            }
            constexpr T &at(const std::size_t idx) {
                  if (idx >= this->size_) {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->data[idx];
            }
            constexpr const T &at(const std::size_t idx) const {
                  if (idx >= size_) {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->data[idx];
            }
            constexpr void clear() {
                  this->size_ = 0u;
                  return;
            }
            constexpr void erase(const T &data) {
                  std::size_t result = 0u;
                  for (auto i = 0u; i < this->size_ - 1u; ++i) {
                        const auto &val = this->data[i];
                        if (val != data) {
                              this->data[result++] = val;
                        }
                  }
                  this->size_ = result;
                  return;
            }
            constexpr std::size_t count(const T &data) const {
                  std::size_t result = 0u;
                  for (auto i = 0u; i < this->size_; ++i) {
                        result += this->data[i] == data;
                  }
                  return result;
            }
            constexpr auto find(const T &value) {
                  for (auto i = 0u; i < this->size_; ++i) {
                        if (this->data[i] == value) {
                              return this->data.begin() + i;
                        }
                  }
                  return this->data.begin() + this->size_;
            }
            constexpr auto find(const T &value) const {
                  for (auto i = 0u; i < this->size_; ++i) {
                        if (this->data[i] == value) {
                              return this->data.begin() + i;
                        }
                  }
                  return this->data.begin() + this->size_;
            }
            constexpr T &operator[](const std::size_t idx) {
                  return this->data[idx];
            }
            constexpr const T &operator[](const std::size_t idx) const {
                  return this->data[idx];
            }
            constexpr auto front() {
                  return this->data[0u];
            }
            constexpr auto back() {
                  auto idx = this->size_;
                  if (idx) {
                        --idx;
                  }
                  return this->data[idx];
            }
            constexpr auto front() const {
                  return this->data[0u];
            }
            constexpr auto back() const {
                  auto idx = this->size_;
                  if (idx) {
                        --idx;
                  }
                  return this->data[idx];
            }

            constexpr auto begin() {
                  return this->data.begin();
            }
            constexpr auto end() {
                  return this->data.begin() + this->size_;
            }
            constexpr auto rbegin() {
                  return this->data.rbegin();
            }
            constexpr auto rend() {
                  return this->data.rend();
            }
            constexpr auto begin() const {
                  return this->data.begin();
            }
            constexpr auto end() const {
                  return this->data.begin() + this->size_;
            }
            constexpr auto rbegin() const {
                  return this->data.rbegin();
            }
            constexpr auto rend() const {
                  return this->data.rend();
            }
            constexpr auto contains_idx(const std::size_t idx) const {
                  return idx < this->size_;
            }

          private:
            std::array<T, N> data;
            std::size_t size_ = 0u;
      };

} // namespace boost

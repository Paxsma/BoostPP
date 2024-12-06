#include <array>
#include <cstdint>

namespace boost {

      template <typename T, std::size_t N>
      class fixed_vector {

          public:
            fixed_vector()
                : size_(0u) {
            }
            using iterator = typename std::array<T, N>::iterator;
            using const_iterator = typename std::array<T, N>::const_iterator;

            constexpr std::size_t max_size() const {
                  return N;
            }

            inline std::size_t size() const {
                  return this->size_;
            }
            inline bool empty() const {
                  return !this->size();
            }
            inline void push_back(const T &value) {
                  if (this->size_ >= N) {
                        throw std::out_of_range("Overflow");
                  }
                  this->data[this->size_++] = value;
                  return;
            }
            inline void push_back(T &&value) {
                  if (this->size_ >= N) {
                        throw std::out_of_range("Overflow");
                  }
                  this->data[this->size_++] = std::move(value);
                  return;
            }
            inline std::pair<std::size_t, bool> find(const T &value) {
                  for (auto i = 0u; i < this->size_; ++i) {
                        if (this->data[i] == value) {
                              return std::make_pair(i, true);
                        }
                  }
                  return std::make_pair(0u, false);
            }
            inline void pop_back() {
                  if (!this->size_) {
                        throw std::out_of_range("Underflow");
                  }
                  --this->size_;
                  return;
            }
            inline T &at(const std::size_t idx) {
                  if (idx >= this->size_) {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->data[idx];
            }
            inline const T &at(const std::size_t idx) const {
                  if (idx >= size_) {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->data[idx];
            }
            inline void clear() {
                  this->size_ = 0u;
                  return;
            }
            inline void erase(const T &data) {
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
            inline std::size_t count(const T &data) const {
                  std::size_t result = 0u;
                  for (const auto &i : this->data) {
                        result += (i == data);
                  }
                  return result;
            }
            inline T &operator[](const std::size_t idx) {
                  return this->data[idx];
            }
            inline const T &operator[](const std::size_t idx) const {
                  return this->data[idx];
            }

            inline auto begin() {
                  return this->data.begin();
            }
            inline auto end() {
                  return this->data.begin() + this->size_;
            }
            inline auto begin() const {
                  return this->data.begin();
            }
            inline auto end() const {
                  return this->data.begin() + this->size_;
            }

          private:
            std::array<T, N> data;
            std::size_t size_ = 0u;
      };

} // namespace boost

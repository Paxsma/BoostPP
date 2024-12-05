#include <array>
#include <cstdint>

namespace boost {

      template <typename T, std::size_t N>
      class fixed_vector {

          public:

            fixed_vector()
                : size_(0u) {
            }

            constexpr std::size_t max_size() const {
                  return N;
            }

            inline std::size_t size() const {
                  return size_;
            }
            inline bool empty() const {
                  return !this->size();
            }
            inline void push_back(const T &value) {
                  if (this->size_ >= N) {
                        throw std::out_of_range("Overflow");
                  }
                  this->data[this->size_++] = value;
            }
            inline void push_back(T &&value) {
                  if (this->size_ >= N) {
                        throw std::out_of_range("Overflow");
                  }
                  this->data[this->size_++] = std::move(value);
            }
            inline void pop_back() {
                  if (!this->size_) {
                        throw std::out_of_range("Underflow");
                  }
                  --this->size_;
            }
            T &at(const std::size_t idx) {
                  if (idx >= this->size_) {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->data[idx];
            }
            const T &at(const std::size_t idx) const {
                  if (idx >= size_) {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->data[idx];
            }
            inline void clear() {
                  this->size_ = 0u;
                  return;
            }

            T &operator[](const std::size_t idx) {
                  return this->data[idx];
            }
            const T &operator[](const std::size_t idx) const {
                  return this->data[idx];
            }

            auto begin() {
                  return this->data.begin();
            }
            auto end() {
                  return this->data.begin() + this->size_;
            }
            auto begin() const {
                  return this->data.begin();
            }
            auto end() const {
                  return this->data.begin() + this->size_;
            }

         private:
           std::array<T, N> data;
           std::size_t size_ = 0u;
      };

} // namespace vector

#ifndef MATRIX_ITERATOR_
#define MATRIX_ITERATOR_

#include <iterator>

namespace yLAB {

template<typename T>
class MatrixIterator final {
public:
    using iterator_category = std::contiguous_iterator_tag;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using const_pointer     = const T*;
    using const_reference   = const T&;
    using difference_type   = int;

    MatrixIterator(pointer ptr = nullptr) noexcept
        : ptr_ {ptr} {}

    MatrixIterator(const MatrixIterator& rhs) = default;

    ~MatrixIterator() = default;

    const_pointer get_pointer() const noexcept { return ptr_; }

    MatrixIterator& operator+=(difference_type n) noexcept {
        ptr_ += n;
        return *this;
    }

    MatrixIterator& operator-=(difference_type n) noexcept {
        ptr_ -= n;
        return *this;
    }

    MatrixIterator operator+(difference_type n) const noexcept { return {ptr_ + n}; }
    MatrixIterator operator-(difference_type n) const noexcept { return {ptr_ - n}; }

    MatrixIterator operator++(int n) noexcept{ ptr_++; return *this; }
    MatrixIterator operator--(int n) noexcept { ptr_--; return *this; }
    MatrixIterator& operator++() noexcept { ++ptr_; return *this; }
    MatrixIterator& operator--() noexcept { --ptr_; return *this; }

    const_reference operator*() const noexcept { return *ptr_; }
    const_pointer operator->() const noexcept { return ptr_; }
    reference operator*() noexcept { return *ptr_; }
    pointer operator->() noexcept { return ptr_; }
private:
    pointer ptr_;
}; // <--- class MatrixIterator

template<typename T>
bool operator==(MatrixIterator<T> lhs, MatrixIterator<T> rhs) noexcept {
    return lhs.get_pointer() == rhs.get_pointer();
}

template<typename T>
MatrixIterator<T> operator+(typename MatrixIterator<T>::difference_type n, MatrixIterator<T> iter) noexcept {
    return iter + n;
}

template<typename T>
MatrixIterator<T>::difference_type operator-(MatrixIterator<T> lhs, MatrixIterator<T> rhs) noexcept {
    return lhs.get_pointer() - rhs.get_pointer();
};

} // <--- namespace yLAB

#endif


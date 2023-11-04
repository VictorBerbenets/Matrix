#ifndef MATRIX_ITERATOR_
#define MATRIX_ITERATOR_

#include <iterator>

#include "my_concepts.hpp"

namespace yLAB {

template <typename T>
class MatrixIterator final {
public:
    using iterator_category = std::contiguous_iterator_tag;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using const_pointer     = const T*;
    using const_reference   = const T&;
    using difference_type   = int;

    MatrixIterator() = default;

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


    MatrixIterator& operator++() noexcept { ++ptr_; return *this; }
    MatrixIterator& operator--() noexcept { --ptr_; return *this; }

    MatrixIterator operator++(int n) noexcept{
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
    MatrixIterator operator--(int n) noexcept {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    const_reference operator*() const noexcept { return *ptr_; }
    const_pointer operator->() const noexcept { return ptr_; }
    reference operator*() noexcept { return *ptr_; }
    pointer operator->() noexcept { return ptr_; }

    bool operator==(MatrixIterator rhs) noexcept {
        return ptr_ == rhs.ptr_;
    }

    bool operator!=(MatrixIterator rhs) noexcept {
        return !(*this == rhs);
    }

    difference_type operator-(MatrixIterator rhs) noexcept {
        return ptr_ - rhs.ptr_;
    }

    template <my_concepts::numeric_type> friend class Matrix;
private:
    pointer ptr_;

    MatrixIterator(pointer ptr)
    : ptr_ {ptr} {}
}; // <--- class MatrixIterator


template <typename T>
MatrixIterator<T> operator+(typename MatrixIterator<T>::difference_type n, MatrixIterator<T> iter) noexcept {
    return iter + n;
}

} // <--- namespace yLAB

#endif


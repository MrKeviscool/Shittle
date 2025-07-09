#pragma once

#include <forward_list>

template <typename T>
class SizedForwardList : public std::forward_list<T> {
public:

    using iterator = std::forward_list<T>::iterator;
    using const_iterator = std::forward_list<T>::const_iterator;

    operator std::forward_list<T>() = delete;
    operator const std::forward_list<T>&() const;

    std::size_t size() const;

    void assign(size_t count, const T& value);
    template <typename InputIt>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> iList);

    void clear();

    iterator insert_after(const_iterator pos, std::initializer_list<T> il);
    template <typename InputIterator>
    iterator insert_after(const_iterator pos, InputIterator first, InputIterator last);

    template <typename... Args>
    iterator emplace_after(const_iterator pos, Args&&... args);

    //need erase_after

    void push_front(const T& t);
    void push_front(T&& t);

    template <typename... Args>
    void emplace_front(Args&&... args);

    void pop_front();

    void resize(std::size_t count);
    void resize(std::size_t count, const T& value);

    void swap(SizedForwardList<T>& other);
    void swap(std::forward_list<T>& other);

private:
    std::size_t m_size = 0;
    std::forward_list<T>* baseCast();
    const std::forward_list<T>* baseCast() const;
};

template <typename T>
std::forward_list<T>* SizedForwardList<T>::baseCast() {
    return static_cast<std::forward_list<T>*>(this);
}

template <typename T>
const std::forward_list<T>* SizedForwardList<T>::baseCast() const {
    return static_cast<const std::forward_list<T>*>(this);
}

template <typename T>
inline SizedForwardList<T>::operator const std::forward_list<T>& () const {
    return *baseCast();
}

template <typename T>
void SizedForwardList<T>::clear() {
    m_size = 0;
    baseCast()->clear();
}

template <typename T>
template <typename ...Args>
void SizedForwardList<T>::emplace_front(Args&&... args) {
    m_size++;
    baseCast()->emplace_front(std::forward<T>(args)...);
}

template <typename T>
void SizedForwardList<T>::push_front(const T& t) {
    m_size++;
    baseCast()->push_front(t);
}

template <typename T>
void SizedForwardList<T>::push_front(T&& t) {
    m_size++;
    baseCast()->push_front(std::move(t));
}

template <typename T>
typename SizedForwardList<T>::iterator SizedForwardList<T>::insert_after(SizedForwardList<T>::const_iterator pos, std::initializer_list<T> il) {
    m_size += il.size();
    return baseCast()->insert_after(pos, il.begin(), il.end());
}

template <typename T>
template <typename InputIterator>
typename SizedForwardList<T>::iterator SizedForwardList<T>::insert_after(SizedForwardList<T>::const_iterator pos, InputIterator first, InputIterator last) {
    m_size += std::distance(first, last);
    return baseCast()->insert_after(pos, first, last);
}

template <typename T>
template <typename... Args>
typename SizedForwardList<T>::iterator SizedForwardList<T>::emplace_after(SizedForwardList<T>::const_iterator pos, Args&&... args) {
    m_size++;
    return baseCast()->emplace_after(pos, std::forward<T>(args)...);
}

template <typename T>
void SizedForwardList<T>::assign(const std::size_t count, const T& value) {
    m_size = count;
    baseCast()->assign(count, value);
}

template <typename T>
template <typename InputIt>
void SizedForwardList<T>::assign(InputIt first, InputIt last) {
    m_size = std::distance(first, last);
    baseCast()->assign(first, last);
}

template <typename T>
void SizedForwardList<T>::assign(std::initializer_list<T> iList){
    m_size = iList.size();
    baseCast()->assign(iList);
}

template <typename T>
std::size_t SizedForwardList<T>::size() const {
    return m_size;
}

template <typename T>
void SizedForwardList<T>::pop_front() {
    m_size--;
    baseCast()->pop_front();
}


template <typename T>
void SizedForwardList<T>::resize(std::size_t count) {
    m_size = count;
    baseCast()->resize(count);
}

template <typename T>
void SizedForwardList<T>::resize(std::size_t count, const T& value) {
    m_size = count;
    baseCast()->resize(count, value);
}

template <typename T>
void SizedForwardList<T>::swap(SizedForwardList<T>& other) {
    const size_t temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    baseCast()->swap(*other.baseCast());
}

template <typename T>
void SizedForwardList<T>::swap(std::forward_list<T>& other) {
    baseCast()->swap(other);
    m_size = std::distance(this->cbegin(), this->cend());
}

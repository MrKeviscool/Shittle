#pragma once

#include <forward_list>

template <typename T>
class SizedForwardList : public std::forward_list<T> {
public:

    using iterator = std::forward_list<T>::iterator;
    using const_iterator = std::forward_list<T>::const_iterator;

    operator std::forward_list<T>() = delete;
    operator const std::forward_list<T>&() const;

    void clear();

    template<typename ...Args>
    void emplace_front(Args&&... args);

    void push_front(const T& t);
    void push_front(T&& t);

    iterator insert_after(const_iterator pos, std::initializer_list<T> il);

    template<typename InputIterator>
    iterator insert_after(const_iterator pos, InputIterator first, InputIterator last);

    std::size_t size() const;
private:
    std::size_t m_size = 0;
    std::forward_list<T>* baseCast();
    const std::forward_list<T>* baseCast() const;
};

template<typename T>
std::forward_list<T>* SizedForwardList<T>::baseCast() {
    return static_cast<std::forward_list<T>*>(this);
}

template<typename T>
const std::forward_list<T>* SizedForwardList<T>::baseCast() const {
    return static_cast<const std::forward_list<T>*>(this);
}

template<typename T>
inline SizedForwardList<T>::operator const std::forward_list<T>& () const {
    return *this;
}

template<typename T>
void SizedForwardList<T>::clear() {
    m_size = 0;
    baseCast()->clear();
}

template <typename T>
template<typename ...Args>
void SizedForwardList<T>::emplace_front(Args&&... args){
    m_size++;
    baseCast()->emplace_front(std::forward<T>(args)...);
}

template <typename T>
void SizedForwardList<T>::push_front(const T& t){
    m_size++;
    baseCast()->push_front(t);
}

template <typename T>
void SizedForwardList<T>::push_front(T&& t){
    m_size++;
    baseCast()->push_front(std::move(t));
}

template <typename T>
typename SizedForwardList<T>::iterator SizedForwardList<T>::insert_after(SizedForwardList<T>::const_iterator pos, std::initializer_list<T> il){
    m_size += il.size();
    return baseCast()->insert_after(pos, il.begin(), il.end());
}

template <typename T>
template<typename InputIterator>
typename SizedForwardList<T>::iterator SizedForwardList<T>::insert_after(SizedForwardList<T>::const_iterator pos, InputIterator first, InputIterator last){
    m_size += std::distance(first, last);
    return baseCast()->insert_after(pos, first, last);
}

template <typename T>
std::size_t SizedForwardList<T>::size() const {
    return m_size;
}

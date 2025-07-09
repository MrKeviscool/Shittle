#pragma once

#include <forward_list>

template <typename T>
class SizedForwardList : public std::forward_list<T> {
private:
    using iterator = std::_Fwd_list_iterator<T>;
    using const_iterator = std::_Fwd_list_const_iterator<T>;
public:

    template<typename ...Args>
    void emplace_front(Args&&... args);

    void push_front(const T& t);
    void push_front(T&& t);

    iterator insert_after(const_iterator pos, std::initializer_list<T> il);

    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    iterator insert_after(const_iterator pos, InputIterator first, InputIterator last);

    std::size_t size() const;
private:
    std::size_t m_size = 0;
};

template <typename T>
template<typename ...Args>
void SizedForwardList<T>::emplace_front(Args&&... args){
    m_size++;
    static_cast<std::forward_list<T>*>(this)->emplace_front(std::forward<T>(args)...);
}

template <typename T>
void SizedForwardList<T>::push_front(const T& t){
    static_cast<std::forward_list<T>*>(this)->push_front(t);
}

template <typename T>
void SizedForwardList<T>::push_front(T&& t){
    static_cast<std::forward_list<T>*>(this)->push_front(std::move(t));
}

template <typename T>
typename SizedForwardList<T>::iterator SizedForwardList<T>::insert_after(SizedForwardList<T>::const_iterator pos, std::initializer_list<T> il){
    m_size += il.size();
    return static_cast<std::forward_list<T>*>(this)->insert_after(pos, il.begin(), il.end());
}

template <typename T>
template<typename InputIterator, typename>
typename SizedForwardList<T>::iterator SizedForwardList<T>::insert_after(SizedForwardList<T>::const_iterator pos, InputIterator first, InputIterator last){
    m_size += std::distance(first, last);
    return static_cast<std::forward_list<T>*>(this)->insert_after(pos, first, last);
}

template <typename T>
std::size_t SizedForwardList<T>::size() const {
    return m_size;
}

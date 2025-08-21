#pragma once
template <typename A, typename B, bool aBigger = (sizeof(A) > sizeof(B))>
struct Bigger {
    using type = B;
};

template <typename A, typename B>
struct Bigger<A, B, true> {
    using type = A;
};

template <typename A, typename B, bool aSmaller = (sizeof(A) < sizeof(B))>
struct Smaller {
    using type = B;
};

template<typename A, typename B>
struct Smaller<A, B, true> {
    using type = A;
};

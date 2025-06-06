#pragma once
template <typename A, typename B, bool aBigger = (sizeof(A) > sizeof(B))>
struct Bigger {
    using type = B;
};

template <typename A, typename B>
struct Bigger<A, B, true> {
    using type = A;
};
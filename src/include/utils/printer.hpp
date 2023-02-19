#pragma once
#include <iostream>

template<typename T>
concept Printable = requires(T t) {
  std::cout << t;
};

void print() {}

template <Printable T, Printable... Tail>
void print(T head, Tail... tail) {
  std::cout << head << ' ';
  print(tail...);
}

template<Printable ...T>
void foldprint(T&&... args) {
  (std::cout << ... << args) << '\n';
}

template <size_t N = 0, typename... Ts>
constexpr void print(std::tuple<Ts...> tup)
{
        if constexpr (N<sizeof...(Ts)) {         // not yet at the end?
               std::cout << get<N>(tup) << ' ';         // print the Nth element
               print<N+1>(tup);                        // print the next element
        }
}

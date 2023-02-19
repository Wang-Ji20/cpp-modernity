#include <iterator>
#include <concepts>
#include <stdexcept>
#include <string>
#include <variant>
#include <map>
#include <iostream>
#include <chrono>

#include "datastructure/Vector.hh"
#include "datastructure/Container.hh"

using std::cout, std::endl;

// variant type
void stdvariant(void) {
  std::variant<int, char> mm;
  mm = 4;
  if (std::holds_alternative<int>(mm))
    cout << get<int>(mm) << endl;
  return;
}

// structured binding
// more verbose return type using arrows ->
auto structbind(void) -> void {
  std::map<std::string, int> m;
  m["hello"] = 1;
  m["world"] = 2;
  for (const auto& [key, value] : m) {
    cout << "key is " << key << " value is " << value << endl;
  }
}

// try-catch clause
auto visitFourOfVector(Vector<double>& v) -> double {
  double val = 0;
  try {
    val = v[3];
  } catch (const std::out_of_range& err) {
    std::cerr << err.what() << '\n';
  }
  cout << val << '\n';
  return val;
}

// if throw, terminate
void alwaysokayfunc() noexcept {
  return;
}

// use abstract class
// don't know anything about
// the implenment of c
void use (Container& c) {
  const int sz = c.size();

  for (int i = 0; i != sz; i++) {
    cout << c[i] << '\n';
  }
}

// Concept Sequence Number
template <typename B>
concept Boolean =
        requires(B x, B y) {
          {x = true};
          {x = false};
          {x = (x == y)};
          {x = (x != y)};
          {x  = !x};
          {x  = (x = y)};
        };

template<typename T, typename T2 =T>
concept Equality_comparable =
        requires (T a, T2 b) {
                { a == b } -> Boolean;        // compare a T to a T2 with ==
                { a != b } -> Boolean;         // compare a T to a T2 with !=
                { b == a } -> Boolean;        // compare a T2 to a T with ==
                { b != a } -> Boolean;        // compare a T2 to a T with !=
        };

template <typename T, typename U  = T>
concept Number =
        requires (T x, T y) {
          x+y; x-y; x*y; x/y;
          x+=y; x-=y; x*=y; x/=y;
          x=x;
          x=0;
        };

template <typename T, typename U = T>
concept Arithmetic = Number<T, U> && Number <U, T>;

template<typename S>
concept Sequence = requires (S a) {
  typename std::ranges::range_value_t<S>;
  typename std::ranges::iterator_t<S>;

  { a.begin() } -> std::same_as<std::ranges::iterator_t<S>>;
  { a.end() } -> std::same_as<std::ranges::iterator_t<S>>;

  requires std::input_iterator<std::ranges::iterator_t<S>>;
  requires std::same_as<std::ranges::range_value_t<S>, std::iter_value_t<S>>;
};

template<Sequence Seq, Number Num>
Num sum(Seq s, Num v) {
  for (const auto& x : s)
    v += x;
  return v;
}

template <std::random_access_iterator Iter>
void advance(Iter p, int n) {
  p += n;
  
}

int main(void) {
  // auto d = std::chrono::May/1/2020;
  printf("hello, world\n");
  stdvariant();
  structbind();
  return 0;
}
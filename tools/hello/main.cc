#include <stdexcept>
#include <string>
#include <variant>
#include <map>
#include <iostream>
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
void alwaysokfunc() noexcept {
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

int main(void) {
  printf("hello, world\n");
  stdvariant();
  structbind();
  return 0;
}
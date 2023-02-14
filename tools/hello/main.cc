#include <string>
#include <variant>
#include <map>
#include <iostream>
#include "datastructure/Vector.hh"

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
auto structbind(void) -> void {
  std::map<std::string, int> m;
  m["hello"] = 1;
  m["world"] = 2;
  for (const auto& [key, value] : m) {
    cout << "key is " << key << " value is " << value << endl;
  }
}

int main(void) {
  printf("hello, world\n");
  stdvariant();
  structbind();
  return 0;
}
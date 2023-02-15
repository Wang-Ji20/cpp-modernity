#include "datastructure/Vector.hh"
#include "utils/err.hpp"
#include <cassert>
#include <stdexcept>

Vector::Vector(int s) {
  if (s < 0)
    throw std::length_error{"Vector constructor: neg size"};

  elem = new double[s];
  sz = s;
}

Vector::Vector(std::initializer_list<double> lst)
    : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
  std::copy(lst.begin(), lst.end(), elem);
}

// copy

Vector::Vector(const Vector &a) : elem{new double[a.sz]}, sz{a.sz} {
  for (int i = 0; i != sz; i++) {
    elem[i] = a.elem[i];
  }
}

Vector& Vector::operator=(const Vector &a) {
  double* p = new double[a.sz];
  for (int i = 0; i != a.sz; i++) {
    p[i] = a.elem[i];
  }
  delete[] elem;
  elem = p;
  sz = a.sz;
  return *this;
}

// move
Vector::Vector (Vector&& a) : elem{a.elem}, sz{a.sz} {
  a.elem = nullptr;
  a.sz = 0;
}

Vector& Vector::operator=(Vector&& a) {
  sz = a.sz;
  a.sz = 0;
  double *p = elem;
  elem = a.elem;
  a.elem = nullptr;
  delete[] p;
  return *this;
}



double &Vector::operator[](int i) {
  if (!(0 < i && i < size()))
    // Google C++ Style discourage throw...
    // They use error code & assert instead.
    throw std::out_of_range{"Vector out of range []"};
  return elem[i];
}

double Vector::operator[](int i) const {
  expect([i, this] { return 0 <= i && i < size(); }, Error_code::range_error);
  assert(0 <= i);
  return elem[i];
}

int Vector::size() const { return sz; }

bool operator==(const Vector &v1, const Vector &v2) {
  if (v1.size() != v2.size())
    return false;
  for (int i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i])
      return false;
  }
  return true;
}

Vector operator+(const Vector& a, const Vector& b) {
  if (a.size() != b.size())
    throw;
  
  Vector res(a.size());

  for (int i =0 ; i != a.size(); i++){
    res[i] = a[i] + b[i];
  }
  // costly
  return res;
}

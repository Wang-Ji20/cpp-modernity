#include "datastructure/Vector.hh"
#include "utils/err.hpp"
#include <cassert>
#include <stdexcept>


template<typename T>
Vector<T>::Vector(int s) {
  if (s < 0)
    throw std::length_error{"Vector constructor: neg size"};

  elem = new double[s];
  sz = s;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> lst)
    : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
  std::copy(lst.begin(), lst.end(), elem);
}

// copy

template<typename T>
Vector<T>::Vector(const Vector &a) : elem{new double[a.sz]}, sz{a.sz} {
  for (int i = 0; i != sz; i++) {
    elem[i] = a.elem[i];
  }
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector &a) {
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
template<typename T>
Vector<T>::Vector (Vector&& a) : elem{a.elem}, sz{a.sz} {
  a.elem = nullptr;
  a.sz = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& a) {
  sz = a.sz;
  a.sz = 0;
  double *p = elem;
  elem = a.elem;
  a.elem = nullptr;
  delete[] p;
  return *this;
}


template<typename T>
T &Vector<T>::operator[](int i) {
  if (!(0 < i && i < size()))
    // Google C++ Style discourage throw...
    // They use error code & assert instead.
    throw std::out_of_range{"Vector out of range []"};
  return elem[i];
}

template<typename T>
T Vector<T>::operator[](int i) const {
  expect([i, this] { return 0 <= i && i < size(); }, Error_code::range_error);
  assert(0 <= i);
  return elem[i];
}

template<typename T>
int Vector<T>::size() const { return sz; }

template<typename T>
bool operator==(const Vector<T> &v1, const Vector<T> &v2) {
  if (v1.size() != v2.size())
    return false;
  for (int i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i])
      return false;
  }
  return true;
}

template<typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
  if (a.size() != b.size())
    throw;
  
  Vector res(a.size());

  for (int i =0 ; i != a.size(); i++){
    res[i] = a[i] + b[i];
  }
  // costly
  return res;
}

// iterators
template<typename T>
T* begin(Vector<T>& x) { return &x[0]; }

template<typename T>
T* end(Vector<T>& x) { return &x[0] + x.size(); }


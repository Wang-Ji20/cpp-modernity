#pragma once

#include "datastructure/Container.hh"
#include <initializer_list>

template <typename T = double>
class Vector : public Container {
public:
  // constructors
  Vector(int s);
  // default is bad... no allocated space
  Vector() = delete;
  Vector(std::initializer_list<T>);

  // copy operators
  Vector(const Vector &a);
  Vector &operator=(const Vector &a);

  // move operators
  Vector(Vector &&a);
  Vector &operator=(Vector &&a);

  T &operator[](int i) override;
  T operator[](int i) const;
  int size() const override;

  ~Vector() { delete[] elem; }

private:
  T *elem;
  int sz;
};

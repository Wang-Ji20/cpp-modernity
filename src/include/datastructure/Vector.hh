#pragma once

#include "datastructure/Container.hh"
#include <initializer_list>

class Vector : public Container{
public:
  // constructors
  Vector(int s);
  // default is bad... no allocated space
  Vector() = delete;
  Vector(std::initializer_list<double>);
  
  // copy operators
  Vector(const Vector& a);
  Vector& operator=(const Vector& a);

  // move operators
  Vector(Vector&& a);
  Vector& operator=(Vector&& a);

  double &operator[](int i) override;
  double operator[](int i) const;
  int size() const override;

  ~Vector() { delete [] elem;}

private:
  double *elem;
  int sz;
};

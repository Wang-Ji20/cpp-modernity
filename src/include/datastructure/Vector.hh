#pragma once

class Vector {
public:
  Vector(int s);
  double &operator[](int i);
  double operator[](int i) const;
  int size() const;

private:
  double *elem;
  int sz;
};

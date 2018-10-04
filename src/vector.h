#ifndef _vector_h
#define _vector_h
#include "macros.h"

typedef struct Vector {
  double x;
  double y;
  double z;
} Vector;

Vector vector(Point p1, Point p2) {
  Vector vec = {
    .x = p2.x - p1.x,
    .y = p2.y - p1.y,
    .z = p2.z - p1.z
  };
  return vec;
}

double length(Vector vec) {
  double x = vec.x;
  double y = vec.y;
  double z = vec.z;
  return sqrt(sqr(x) + sqr(y) + sqr(z));
}

Vector multiply(Vector v, double n) {
  Vector vec = {
    .x = v.x * n,
    .y = v.y * n,
    .z = v.z * n
  };
  return vec;
}

Vector normalize(Vector v) {
  double len = length(v);
  return multiply(v, 1 / len);
}

Vector sum(Vector v1, Vector v2) {
  Vector vec = {
    .x = v1.x + v2.x,
    .y = v1.y + v2.y,
    .z = v1.z + v2.z
  };
  return vec;
}

double dot(Vector v1, Vector v2) {
  double x = v1.x * v2.x;
  double y = v1.y * v2.y;
  double z = v1.z * v2.z;
  return x + y + z;
}

Vector cross(Vector v1, Vector v2) {
  double x = v1.y * v2.z - v1.z * v2.y;
  double y = v1.z * v2.x - v1.x * v2.z;
  double z = v1.x * v2.y - v1.y * v2.x;
  Vector vec = { .x = x, .y = y, .z = z };
  return vec;
}

void print_vector(Vector v) {
  printf("Vector (%f, %f, %f)\n", v.x, v.y, v.z);
}

#endif

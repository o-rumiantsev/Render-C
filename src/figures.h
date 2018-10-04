#ifndef _figures_h
#define _figures_h

typedef struct Point {
  double x;
  double y;
  double z;
} Point;

Point point(double x, double y, double z) {
  Point p = { .x = x, .y = y, .z = z };
  return p;
}

void print_point(Point p) {
  printf("Point (%f, %f, %f)\n", p.x, p.y, p.z);
}

typedef struct Triangle {
  Point p1;
  Point p2;
  Point p3;
} Triangle;

Triangle triangle(Point p1, Point p2, Point p3) {
  Triangle t = { .p1 = p1, .p2 = p2, .p3 = p3 };
  return t;
}

typedef struct Box {
  Point p1;
  Point p2;
} Box;

Box box(Point p1, Point p2) {
  Box b = { .p1 = p1, .p2 = p2 };
  return b;
}

#endif

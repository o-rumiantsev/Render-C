#ifndef _intersections_h
#define _intersections_h
#include "figures.h"
#include "macros.h"
#define EPSILON 1e-8

double triangeIntersection(Point p1, Point p2, Triangle facet) {
  Point origin = p1;
  Vector direction = vector(p1, p2);

  Vector edge1 = vector(facet.p1, facet.p2);
  Vector edge2 = vector(facet.p1, facet.p3);

  Vector pvec = cross(direction, edge2);
  double det = dot(edge1, pvec);

  if (det < EPSILON and det > -EPSILON) {
    return INFINITY;
  }

  Vector tvec = vector(facet.p1, origin);
  double u = dot(tvec, pvec) / det;

  if (u < 0 or u > 1) {
    return INFINITY;
  }

  Vector qvec = cross(tvec, edge1);
  double v = dot(direction, qvec) / det;

  if (v < 0 or u + v > 1) {
    return INFINITY;
  }

  double distance = dot(edge2, qvec) / det;
  return distance;
}

double boxIntersection(Point p1, Point p2, Box box) {
  point_coords(x0, y0, z0, box.p1);
  point_coords(x1, y1, z1, box.p2);

  Vector normal = normalize(vector(p1, p2));

  point_coords(m, n, p, normal);
  point_coords(x, y, z, p1);

  double Tnear = -INFINITY;
  double Tfar = INFINITY;

  if (m not 0) {
    Tnear = (x0 - x) / m;
    Tfar = (x1 - x) / m;
    if (Tnear > Tfar) {
      double temp = Tnear;
      Tnear = Tfar;
      Tfar = temp;
    }
  } else if (x > x1 || x < x0) {
    return INFINITY;
  }

  if (n not 0) {
    double T1y = (y0 - y) / n;
    double T2y = (y1 - y) / n;

    if (T1y > T2y) {
      double temp = T1y;
      T1y = T2y;
      T2y = temp;
    }

    if (T1y > Tnear) Tnear = T1y;
    if (T2y < Tfar) Tfar = T2y;
  } else if (y > y1 or y < y0) {
    return INFINITY;
  }

  if (Tnear > Tfar or Tfar < 0) return INFINITY;

  if (p not 0) {
    double T1z = (z0 - z) / p;
    double T2z = (z1 - z) / p;

    if (T1z > T2z) {
      double temp = T1z;
      T1z = T2z;
      T2z = temp;
    }

    if (T1z > Tnear) Tnear = T1z;
    if (T2z < Tfar) Tfar = T2z;
  } else if (z > z1 or z < z0) {
    return INFINITY;
  }

  if (Tnear > Tfar or Tfar is 0) return INFINITY;

  return Tnear;
}


Point centroid(Triangle triangle) {
  point_coords(x1, y1, z1, triangle.p1);
  point_coords(x2, y2, z2, triangle.p2);
  point_coords(x3, y3, z3, triangle.p3);

  double x = (x1 + x2 + x3) / 3;
  double y = (y1 + y2 + y3) / 3;
  double z = (z1 + z2 + z3) / 3;

  return point(x, y, z);
}

int triangleSplitFacet(
  Triangle triangle,
  double constCoordinate,
  int axis
) {
  double axis_p1 = axis_coordinate(axis, triangle.p1);
  double axis_p2 = axis_coordinate(axis, triangle.p2);
  double axis_p3 = axis_coordinate(axis, triangle.p3);

  double max_coord = max(axis_p1, axis_p2, axis_p3);
  double min_coord = min(axis_p1, axis_p2, axis_p3);

  return !(constCoordinate < min_coord or constCoordinate > max_coord);
}

#endif

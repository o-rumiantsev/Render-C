#ifndef _macros_h
#define _macros_h
#include <math.h>

#define is ==
#define not !=
#define and &&
#define or ||

#define true 1
#define false 0

#define sqr(x) pow(x, 2)
#define point_coords(coord1, coord2, coord3, point) \
  double coord1 = point.x, coord2 = point.y, coord3 = point.z

#define _max(a, b) a > b ? a : b
#define _min(a, b) a < b ? a : b

#define max(a, b, c) _max(a, b) == a ? _max(a, c) : _max(b, c)
#define min(a, b, c) _min(a, b) == a ? _min(a, c) : _min(b, c)

#define axis_coordinate(axis, point) \
  axis == 0 ? point.x : \
  axis == 1 ? point.y : point.z

#endif

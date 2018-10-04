#ifndef _render_h
#define _render_h

#include <stdlib.h>
#include "geometry.h"

struct RenderOpts {
  int width;
  int height;
  Point camera;
  double distance;
  Vector direction;
};

Point *canvas(struct RenderOpts render_options, int *resolution) {
  int count = render_options.width * render_options.height;
  Point *points = (Point *)malloc(count * sizeof(Point));

  Vector view = sum(
    render_options.direction,
    vector(point(0., 0., 0.), render_options.camera)
  );

  Point center = point(view.x, view.y, view.z);

  double dx = 1. / render_options.width;
  double dz = 1. / render_options.height;
  int index = 0;

  for (double z = 0.5; z > -0.5; z -= dz) {
    for (double x = -0.5; x < 0.5; x += dx) {
      points[index++] = point(x, -1, z);
    }
  }

  (*resolution) = count;
  return points;
}

#endif

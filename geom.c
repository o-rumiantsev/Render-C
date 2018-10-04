#include <stdio.h>
#include <time.h>
#include "src/geometry.h"
#include "src/parser.h"
#include "src/render.h"

int main() {
  int facets_count;
  Facet *facets = parse_obj("objects/cow.obj", &facets_count);
  printf("Got %d facets\n", facets_count);

  struct RenderOpts render_options = {
    .width = 8,
    .height = 8,
    .camera = point(0., -2., 0.),
    .distance = 1.,
    .direction = vector(point(0., 0., 0.), point(0., 1., 0.))
  };

  int resolution;
  Point *points = canvas(render_options, &resolution);
  int iterations = resolution * facets_count;

  printf("Resolution: %d\nNumber of iterations: %d\n", resolution, iterations);

  for (int i = 0; i < resolution; ++i) {
    for (int j = 0; j < facets_count; ++j) {
      triangeIntersection(render_options.camera, points[i], facets[j].triangle);
    }
  }

  return 0;
}

// Facet f = facet(
  //   point(0.1, -0.25, -0.3),
  //   point(0.1, 0.25, -0.3),
  //   point(0.1, 0, 0.3)
  // );
  //
  // Point p1 = point(-0.5, 0, 0);
  // Point p2 = point(0, 0, 0);
  //
  // clock_t start = clock();
  //
  // for (int i = 0; i < 300000000; ++i) { // 300 million intersection - 24 seconds
    //   triangeIntersection(p1, p2, f.triangle);
    // }
    //
    // clock_t end = clock();
    // float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    //
    // printf("%f\n", seconds);

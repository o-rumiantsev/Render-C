#ifndef _parser_h
#define _parser_h
#include <stdlib.h>
#include "string.h"
#include "geometry.h"

#define is_vertex(line) line[0] is 'v' and line[1] is ' '
#define is_facet(line) line[0] is 'f'

typedef struct Facet {
  Triangle triangle;
  Vector normal;
  Point centroid;
} Facet;

Facet facet(Point p1, Point p2, Point p3) {
  Triangle trigon = triangle(p1, p2, p3);
  Vector edge1 = vector(p1, p2);
  Vector edge2 = vector(p1, p3);
  Vector normal = normalize(cross(edge1, edge2));
  Point center = centroid(trigon);
  Facet facet = { .triangle = trigon, .normal = normal, .centroid = center };
  return facet;
}

int count_lines(const char *filename, int *vertices_count, int *facets_count) {
  FILE *fp = fopen(filename, "r");
  int count = 0;

  while (!feof(fp)) {
    char line[80];
    fgets(line, 80, fp);
    if (is_vertex(line)) ++(*vertices_count);
    if (is_facet(line)) ++(*facets_count);
  }

  fclose(fp);
  return count;
}

Point process_vertex(char *line) {
  String s = string(line);

  int count;
  String *words = string_split(s, ' ', &count);

  double x = atof(words[1].str);
  double y = atof(words[2].str);
  double z = atof(words[3].str);

  Point vertex = { .x = x, .y = y, .z = z };
  return vertex;
}

Facet process_facet(char *line, Point *vertices) {
  String s = string(line);

  int count;
  String *words = string_split(s, ' ', &count);

  int index_p1 = atoi(string_split(words[1], '/', &count)[0].str);
  int index_p2 = atoi(string_split(words[2], '/', &count)[0].str);
  int index_p3 = atoi(string_split(words[3], '/', &count)[0].str);

  Point p1 = vertices[index_p1];
  Point p2 = vertices[index_p2];
  Point p3 = vertices[index_p3];

  Facet f = facet(p1, p2, p3);
  return f;
}

Facet *parse_obj(const char *filename, int *count) {
  int vertices_count = 0;
  int facets_count = 0;
  count_lines(filename, &vertices_count, &facets_count);

  Point *vertices = (Point *)malloc(vertices_count * sizeof(Point));
  Facet *facets = (Facet *)malloc(facets_count * sizeof(Facet));

  FILE *file = fopen(filename, "r");
  int i = 0;
  int j = 0;

  while (!feof(file)) {
    char line[80];
    fgets(line, 80, file);

    if (is_vertex(line)) {
      Point vertex = process_vertex(line);
      vertices[i++] = vertex;
    };

    if (is_facet(line)) {
      Facet facet = process_facet(line, vertices);
      facets[j++] = facet;
    };
  }

  (*count) = facets_count;
  return facets;
}

#endif

#include "figures.h"
#include "macros.h"
#include "intersection.h"
#define DIMENSIONS 3

typedef struct Node {
  Point min;
  Point max;
  Split split;
  Node left;
  Node right;
  Node suspect;
} Node;

// Node build() {}
